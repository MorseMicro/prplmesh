/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#include <mapf/common/utils.h>

#include "ieee1905_transport.h"

#include <arpa/inet.h>
#include <net/if.h>

namespace beerocks {
namespace transport {

// Use transport messaging classes
using namespace beerocks::transport::messages;

void Ieee1905Transport::handle_broker_pollin_event(std::unique_ptr<messages::Message> &msg)
{
    if (auto *cmdu_tx_msg = dynamic_cast<CmduTxMessage *>(msg.get())) {
        MAPF_DBG("received CmduTxMessage message:" << std::endl << *cmdu_tx_msg);
        handle_broker_cmdu_tx_message(*cmdu_tx_msg);
    } else if (auto *interface_configuration_request_msg =
                   dynamic_cast<InterfaceConfigurationRequestMessage *>(msg.get())) {
        MAPF_DBG("received InterfaceConfigurationRequestMessage message:"
                 << std::endl
                 << *interface_configuration_request_msg);
        handle_broker_interface_configuration_request_message(*interface_configuration_request_msg);
    } else if (auto *al_mac_addr_configuration_msg =
                   dynamic_cast<AlMacAddressConfigurationMessage *>(msg.get())) {
        MAPF_DBG("received AlMacAddressConfigurationMessage message:"
                 << std::endl
                 << *al_mac_addr_configuration_msg);
        handle_al_mac_addr_configuration_message(*al_mac_addr_configuration_msg);
    } else {
        // should never receive messages which we are not subscribed to
        MAPF_WARN("received un-expected message:" << std::endl << *msg);
    }
}

void Ieee1905Transport::handle_broker_cmdu_tx_message(CmduTxMessage &msg)
{
    // parse CmduTxMessage message
    struct Packet packet;
    packet.dst_if_type  = msg.metadata()->if_type;
    packet.dst_if_index = msg.metadata()->if_index;
    packet.src_if_type  = CmduTxMessage::IF_TYPE_LOCAL_BUS;
    packet.src_if_index = 0;
    std::copy_n(msg.metadata()->dst, ETH_ALEN, packet.dst.oct);
    std::copy_n(msg.metadata()->src, ETH_ALEN, packet.src.oct);
    packet.ether_type       = msg.metadata()->ether_type;
    packet.header.iov_base  = 0;
    packet.header.iov_len   = 0;
    packet.payload.iov_base = msg.data();
    packet.payload.iov_len  = msg.metadata()->length;

    if (packet.ether_type == ETH_P_1905_1) {
        mapf_assert(packet.payload.iov_len >= sizeof(Ieee1905CmduHeader));

        Ieee1905CmduHeader *ch = (Ieee1905CmduHeader *)packet.payload.iov_base;

        // update messageId field (a.k.a "MID") unless is was pre-set by the originator
        if (!msg.metadata()->preset_message_id) {
            uint16_t messageId = get_next_message_id();
            ch->messageId      = htons(messageId);
        }

        // send confirmation (with messageId value)
        if (msg.metadata()->cookie != 0) {
            CmduTxConfirmationMessage confMsg;

            confMsg.metadata()->cookie     = msg.metadata()->cookie;
            confMsg.metadata()->ether_type = msg.metadata()->ether_type;
            confMsg.metadata()->msg_type   = msg.metadata()->msg_type;
            confMsg.metadata()->msg_id     = ntohs(ch->messageId);

            MAPF_DBG("publishing CmduTxConfirmationMessage:" << std::endl << confMsg);
            if (!m_broker->publish(confMsg)) {
                MAPF_ERR("cannot publish message to broker.");
            }
        }

        if (msg.metadata()->msg_type != ntohs(ch->messageType)) {
            MAPF_WARN("CmduTxMessage messageType mismatch: cmdu: "
                      << std::hex << msg.metadata()->msg_type
                      << " packet: " << ntohs(ch->messageType));
        }
    }

    counters_[CounterId::OUTGOING_LOCAL_BUS_PACKETS]++;
    handle_packet(packet);
}

void Ieee1905Transport::handle_broker_interface_configuration_request_message(
    InterfaceConfigurationRequestMessage &msg)
{
    std::map<std::string, NetworkInterface> updated_network_interfaces;
    // fill a set with the interfaces that are part of the bridge:
    std::set<std::string> bridge_state{};

    auto bridge_name = msg.metadata()->bridge_name;
    LOG_IF(!m_bridge_state_manager->read_state(bridge_name, bridge_state), ERROR)
        << "Failed reading the bridge state!";
    updated_network_interfaces[bridge_name].ifname      = bridge_name;
    updated_network_interfaces[bridge_name].bridge_name = std::string();
    updated_network_interfaces[bridge_name].is_bridge   = true;

    for (const auto &ifname : bridge_state) {
        MAPF_INFO("bridge state iface: " << ifname);
        updated_network_interfaces[ifname].ifname      = ifname;
        updated_network_interfaces[ifname].bridge_name = bridge_name;
    }

    update_network_interfaces(updated_network_interfaces);
}

void Ieee1905Transport::handle_al_mac_addr_configuration_message(
    AlMacAddressConfigurationMessage &msg)
{
    auto al_mac = msg.metadata()->al_mac;

    set_al_mac_addr(al_mac.oct);
}

bool Ieee1905Transport::send_packet_to_broker(Packet &packet)
{
    // Create and fill an CmduRxMessage to be sent to the broker
    CmduRxMessage msg;

    std::copy_n(packet.src.oct, ETH_ALEN, msg.metadata()->src);
    std::copy_n(packet.dst.oct, ETH_ALEN, msg.metadata()->dst);

    msg.metadata()->ether_type = packet.ether_type;
    msg.metadata()->if_type    = packet.src_if_type;
    msg.metadata()->if_index   = packet.src_if_index;
    msg.metadata()->length     = packet.payload.iov_len;
    std::copy_n((uint8_t *)packet.payload.iov_base, packet.payload.iov_len, msg.data());

    if (packet.ether_type == ETH_P_1905_1) {
        Ieee1905CmduHeader *ch   = reinterpret_cast<Ieee1905CmduHeader *>(packet.payload.iov_base);
        msg.metadata()->msg_type = ntohs(ch->messageType);
        msg.metadata()->relay    = ch->GetRelayIndicator() ? 1 : 0;
    } else {
        msg.metadata()->msg_type = 0;
        msg.metadata()->relay    = 0;
    }

    counters_[CounterId::INCOMMING_LOCAL_BUS_PACKETS]++;

    MAPF_DBG("publishing CmduRxMessage:" << std::endl << msg);
    if (!m_broker->publish(msg)) {
        MAPF_ERR("failed to publish message to broker.");
        return false;
    }

    return true;
}

uint16_t Ieee1905Transport::get_next_message_id()
{
    message_id_++;

    if (message_id_ == 0) {
        MAPF_DBG("messageId wrap-around occurred.");
        counters_[CounterId::MESSAGE_ID_WRAPAROUND]++;
    }

    return message_id_;
}

} // namespace transport
} // namespace beerocks
