/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef MAP_TRANSPORT_IEEE1905_TRANSPORT_H_
#define MAP_TRANSPORT_IEEE1905_TRANSPORT_H_

#include <mapf/common/logger.h>
#include <mapf/transport/ieee1905_transport_messages.h>

#include <bcl/beerocks_event_loop.h>
#include <bcl/network/bridge_state_manager.h>
#include <bcl/network/interface_state_manager.h>

#include "ieee1905_transport_broker.h"

#include <tlvf/tlvftypes.h>

#include <arpa/inet.h>
#include <chrono>
#include <map>
#include <net/if.h>

// Address is a multicast address if the most significant byte in the address is 0x01
#ifndef ETHER_IS_MULTICAST
#define ETHER_IS_MULTICAST(addr) (*(addr)&0x01) // is address multicast or broadcast
#endif

//
// Notes:
//
// Setting ebtables rules:
// -----------------------
// IEEE1905 multicast packets should not be bridge-fludded by default (only "relayed multicast" packets should be fludded)
// In order to prevent bridge fludding of IEEE1905 multicast packets the following ebtables configuration should be applied:
//
//      ebtables -t filter -I FORWARD 1 -p 0x893a --destination 01:80:c2:00:00:13 -j DROP
//
// Relayed multicast will be implemented by the IEEE1905 protocol handler (in the Ieee1905Transport class)
//
// TODO: need to set ebtables rule at the platform level
//
//
// Modifying GRX350 GSWIP-L configuration:
// --------------------------------------
// The GSWIP-L ethernet switch hardware of the GRX350 is configured by default to always forward/flood multicast packets. Flooding all multicast
// packets between the four Ethernet ports of the GRX350 will break the non-relayed multicast behaviour expected
// from IEEE1905 devices. In order to avoid this the following command should be issued:
//
//      switch_cli dev=0 GSW_REGISTER_SET nRegAddr=0x454 nData=1
//
// TODO: this could be considered a platform bug that should be solved at the platform level - see https://jira-chd.intel.com/browse/UGW_SW-25961
//

namespace beerocks {
namespace transport {

class Ieee1905Transport {
public:
    /**
     * Class constructor
     *
     * @param interface_state_manager Interface state manager.
     * @param interface_state_manager Bridge state manager.
     * @param broker Message broker.
     * @param event_loop Event loop to wait for I/O events.
     */
    Ieee1905Transport(std::shared_ptr<beerocks::net::InterfaceStateManager> interface_state_manager,
                      std::shared_ptr<beerocks::net::BridgeStateManager> bridge_state_manager,
                      std::shared_ptr<broker::BrokerServer> broker,
                      std::shared_ptr<EventLoop> event_loop);

    /**
     * @brief Starts the transport process.
     *
     * @return True on success and false otherwise.
     */
    bool start();

    /**
     * @brief Stops the transport process.
     *
     * @return True on success and false otherwise.
     */
    bool stop();

private:
    /**
     * Interface state manager to read and detect changes (transitions to and from the
     * up-and-running state) in the state of the network interfaces.
     */
    std::shared_ptr<beerocks::net::InterfaceStateManager> m_interface_state_manager;

    /**
     * Bridge state manager to read and detect changes in the bridge (i.e. when an interface is added or removed to the bridge).
     */
    std::shared_ptr<beerocks::net::BridgeStateManager> m_bridge_state_manager;

    /**
     * Message broker implementing the publish/subscribe design pattern.
     */
    std::shared_ptr<broker::BrokerServer> m_broker;

    /**
     * Application event loop used by the process to wait for I/O events.
     */
    std::shared_ptr<EventLoop> m_event_loop;

    std::string if_index2name(unsigned int index)
    {
        char ifname[IF_NAMESIZE] = {0};
        if (if_indextoname(index, ifname)) {
            return std::string(ifname);
        }
        return std::string();
    }

    struct NetworkInterface {
        /// the file descriptor of the socket bound to this interface (or -1 if inactive)
        std::shared_ptr<Socket> fd;
        /// mac address of the interface
        uint8_t addr[ETH_ALEN] = {0};
        /// interface name
        std::string ifname;
        /// the bridge's interface name (if this interface is in a bridge)
        std::string bridge_name;
        /// is this interface a bridge interface
        bool is_bridge = false;
    };
    // network interface status table
    // this table holds all the network interfaces that are to be used by
    // the transport.
    //
    // interface name (ifname) is used as Key to the table
    std::map<std::string, NetworkInterface> network_interfaces_;

    // Pending Network interface table
    // This table holds the network interfaces that transport fails to create a raw socket for it.
    std::list<std::string> pending_network_interfaces_;

    uint16_t message_id_           = 0;
    uint8_t al_mac_addr_[ETH_ALEN] = {0};

    // Primary VLAN Identifier to be added for IEEE 1905 Multicast packets
    uint16_t primary_vlan_id_        = 0;
    bool traffic_separation_enabled_ = false;

    // Bridge name that the transport monitors
    std::string bridge_name_;

    // IEEE 802.1Q Protocol Identifier
    static constexpr uint16_t ieee_8021q_protocol_id = 0x8100;

    // Ethernet Header with 802.1Q VLAN Information
    struct ether_header_vlan {
        uint8_t ether_dhost[ETH_ALEN]; /* destination eth addr  */
        uint8_t ether_shost[ETH_ALEN]; /* source ether addr */
        uint16_t tpid;                 /* 802.1Q header TPID */
        struct TCI {
            uint16_t vid : 12; /* VLAN Identifier */
            uint16_t dei : 1;  /* Drop eligible indicator */
            uint16_t pcp : 3;  /* Priority code point */
        } __attribute__((__packed__)) tci;
        uint16_t ether_type; /* packet type ID field    */
    } __attribute__((__packed__));

// IEEE1905 CMDU header in packed format
#pragma pack(push, 1)
    struct Ieee1905CmduHeader {
        uint8_t messageVersion;
        uint8_t _reservedField0;
        uint16_t messageType;
        uint16_t messageId;
        uint8_t fragmentId;
        uint8_t flags;
        void SetLastFragmentIndicator(bool value)
        {
            flags = (flags & ~0x80) | (value ? 0x80 : 0x00);
        };
        bool GetLastFragmentIndicator() { return (flags & 0x80); };
        void SetRelayIndicator(bool value) { flags = (flags & ~0x40) | (value ? 0x40 : 0x00); };
        bool GetRelayIndicator() { return (flags & 0x40); };
    };
#pragma pack(pop)

    // packed TLV struct to help in the parsing of the packet
#pragma pack(push, 1)
    struct Tlv {
    protected:
        uint8_t tlvType;
        uint16_t tlvLength;

    public:
        uint8_t &type() { return tlvType; }

        Tlv *next() { return (Tlv *)((uint8_t *)this + size()); }

        size_t size() { return sizeof(Tlv) + ntohs(tlvLength); }
    };
#pragma pack(pop)

    // internal statistics counters
    enum CounterId {
        MESSAGE_ID_WRAPAROUND,
        INCOMMING_NETWORK_PACKETS,
        OUTGOING_NETWORK_PACKETS,
        INCOMMING_LOCAL_BUS_PACKETS,
        OUTGOING_LOCAL_BUS_PACKETS,
        DUPLICATE_PACKETS,
        DEFRAGMENTATION_FAILURE,
    };
    // Enum AutoPrint generated code snippet begining- DON'T EDIT!
    // clang-format off
    static const char *CounterId_str(CounterId enum_value) {
        switch (enum_value) {
        case MESSAGE_ID_WRAPAROUND:       return "MESSAGE_ID_WRAPAROUND";
        case INCOMMING_NETWORK_PACKETS:   return "INCOMMING_NETWORK_PACKETS";
        case OUTGOING_NETWORK_PACKETS:    return "OUTGOING_NETWORK_PACKETS";
        case INCOMMING_LOCAL_BUS_PACKETS: return "INCOMMING_LOCAL_BUS_PACKETS";
        case OUTGOING_LOCAL_BUS_PACKETS:  return "OUTGOING_LOCAL_BUS_PACKETS";
        case DUPLICATE_PACKETS:           return "DUPLICATE_PACKETS";
        case DEFRAGMENTATION_FAILURE:     return "DEFRAGMENTATION_FAILURE";
        }
        static std::string out_str = std::to_string(int(enum_value));
        return out_str.c_str();
    }
    friend inline std::ostream &operator<<(std::ostream &out, CounterId value) { return out << CounterId_str(value); }
    // clang-format on
    // Enum AutoPrint generated code snippet end
    std::map<CounterId, unsigned long> counters_;

    // an internal data structure used for manipulating packets (CMDUs, LLDP, etc.)
    class Packet {
    public:
        uint8_t dst_if_type       = messages::CmduRxMessage::IF_TYPE_NONE;
        unsigned int dst_if_index = 0;
        uint8_t src_if_type       = messages::CmduRxMessage::IF_TYPE_NONE;
        unsigned int src_if_index = 0;
        sMacAddr dst              = {.oct = {0}}; // destination mac address
        sMacAddr src              = {.oct = {0}}; // source mac address
        uint16_t ether_type       = 0x0000;
        struct iovec header       = {.iov_base = NULL, .iov_len = 0};
        struct iovec payload      = {.iov_base = NULL, .iov_len = 0};

        virtual std::ostream &print(std::ostream &os) const;

        static const std::set<uint16_t> reliable_multicast_msg_types;
        bool is_reliable_multicast()
        {
            return reliable_multicast_msg_types.find(
                       ntohs(static_cast<Ieee1905CmduHeader *>(payload.iov_base)->messageType)) !=
                   reliable_multicast_msg_types.end();
        }
    };
    friend std::ostream &operator<<(std::ostream &os, const Packet &m);

    // reliable multicast neighbours map
    struct ieee1905_neighbor {
        sMacAddr al_mac;
        unsigned int if_index;
        std::chrono::steady_clock::time_point last_seen;
    };

    std::unordered_map<sMacAddr, ieee1905_neighbor> neighbors_map_;

    std::chrono::steady_clock::time_point removed_aged_neighbors_timeout_ =
        std::chrono::steady_clock::now();

    // According to the ieee1905.1 specification section 8.2.1.1, a 1905.1 management entity shall
    // transmit a topology discovery message *at least* once every 60 seconds. Since any message from
    // the neighbor will update it's last_seen, in practice it should be safe to consider it dead and
    // delete it if 70 seconds have passed.
    const std::chrono::seconds kMaximumNeighbourAge = std::chrono::seconds(70);

    // de-duplication internal data structures

    static constexpr sMacAddr ieee1905_multicast_addr = {
        .oct = {0x01, 0x80, 0xc2, 0x00, 0x00, 0x13}};
    // two IEE1905 packets received from the same src address and with the same messageId
    // will be considered as duplicate iff they are received within a kMaximumDeDuplicationAge duration.
    // This duration should be long enough to allow for any buffered/in-transit duplicate packets to be flushed; and
    // should be short enough to handle the case when a device reboots (and reuses the same messageId).
    const std::chrono::milliseconds kMaximumDeDuplicationAge = std::chrono::milliseconds(1000);

    // limit the size of the de-duplication map (to prevent memory exhaustion attack)
    const int kMaximumDeDuplicationThreads = 1024;

    struct DeDuplicationKey {
        sMacAddr src;
        sMacAddr dst;
        uint16_t
            messageType; // required to distinguish the case of Request / Reply (when the reply carries an out of sync MID)
        uint16_t messageId;
        uint8_t fragmentId;
    };
    struct DeDuplicationKeyCompare {
        // implement Compare for the std::map template
        bool operator()(const DeDuplicationKey &lhs, const DeDuplicationKey &rhs) const
        {
            // compare based on src and dst address first then messageId, then fragmentId
            int srccmp = memcmp(lhs.src.oct, rhs.src.oct, ETH_ALEN);
            if (srccmp)
                return srccmp < 0;
            int dstcmp = memcmp(lhs.dst.oct, rhs.dst.oct, ETH_ALEN);
            if (dstcmp)
                return dstcmp < 0;
            else if (lhs.messageType != rhs.messageType)
                return lhs.messageType < rhs.messageType;
            else if (lhs.messageId != rhs.messageId)
                return lhs.messageId < rhs.messageId;
            else
                return lhs.fragmentId < rhs.fragmentId;
        }
    };
    struct DeDuplicationValue {
        std::chrono::steady_clock::time_point time;
    };
    std::map<DeDuplicationKey, DeDuplicationValue, DeDuplicationKeyCompare> de_duplication_map_;

    // de-fragmentation internal data structures

    // two IEE1905 packet fragments received from the same src address and with the same messageId
    // will be considered as belonging to the same PDU iff they are received within a kMaximumDeFragmentionAge duration.
    // This duration should be long enough to allow for any buffered/in-transit fragments to arrive; and
    // should be short enough to handle the case when a device reboots (and reuses the same messageId).
    const std::chrono::milliseconds kMaximumDeFragmentationAge = std::chrono::milliseconds(1000);

    // limit the size of the de-fragmentation map (to prevent memory exhaustion attack)
    const int kMaximumDeFragmentationThreads = 16;

    static const size_t kMaximumDeFragmentionSize = (64 * 1024);

    struct DeFragmentationKey {
        sMacAddr src;
        uint16_t
            messageType; // required to distinguish the case of Request / Reply (when the reply carries an out of sync MID)
        uint16_t messageId;
    };
    struct DeFragmentationKeyCompare {
        // implement Compare for the std::map template
        bool operator()(const DeFragmentationKey &lhs, const DeFragmentationKey &rhs) const
        {
            // compare based on src address first then messageId
            int srccmp = memcmp(lhs.src.oct, rhs.src.oct, ETH_ALEN);
            if (srccmp)
                return srccmp < 0;
            else if (lhs.messageType != rhs.messageType)
                return lhs.messageType < rhs.messageType;
            else
                return lhs.messageId < rhs.messageId;
        }
    };
    struct DeFragmentationValue {
        std::chrono::steady_clock::time_point time;
        uint8_t numFragments                   = 0;
        uint8_t buf[kMaximumDeFragmentionSize] = {0};
        int bufIndex                           = 0;
        bool complete                          = false;
    };
    std::map<DeFragmentationKey, DeFragmentationValue, DeFragmentationKeyCompare>
        de_fragmentation_map_;

    static const int kIeee1905FragmentationThreashold = tlvf::
        MAX_TLV_SIZE; // IEEE1905 packets (CMDU) should be fragmented if larger than this threashold

    // When fragmenting a message it is expected that only the last fragment will have an END OF MESSAGE TLV.
    // However, when sending a TLV smaller than then the minimum ethernet frame, a padding is added to the frame.
    // This padding might cause us having unwanted EOM TLV.
    static const int kIeee1905FragmentationMinimum = 64 - 2 * 6 /* src, dest MAC */ - 2 /* Type */;

    //
    // NETWORK INTERFACE STUFF
    //
    void update_network_interfaces(
        const std::map<std::string, NetworkInterface> &added_updated_network_interfaces,
        const std::map<std::string, NetworkInterface> &removed_network_interfaces);
    /**
     * @brief Add or remove an interface to/from the transport.
     *
     * @param[in] bridge_name The bridge the interface is part of.
     * @param[in] ifname The name of the interface that was added/removed.
     * @param[in] iface_added true if the interface was added to the bridge, false otherwise.
     * @param[in] is_bridge Shall be true if the interface is a bridge.
     * @return true on success and false otherwise.
     **/
    bool update_network_interface(const std::string &bridge_name, const std::string &ifname,
                                  bool iface_added, bool is_bridge = false);
    /**
     * @brief Removes an interface from the transport.
     *
     * @param[in] ifname The name of the interface that was removed.
     * @return true on success and false otherwise.
     **/
    bool remove_network_interface(const std::string &ifname);
    bool open_interface_socket(NetworkInterface &interface);
    bool attach_interface_socket_filter(NetworkInterface &iface_name);
    void activate_interface(NetworkInterface &interface);
    void deactivate_interface(NetworkInterface &interface, bool remove_handlers = true);
    void handle_interface_state_change(const std::string &iface_name, bool is_active);
    void handle_bridge_state_change(const std::string &bridge_name, const std::string &iface_name,
                                    bool iface_added);
    void handle_interface_pollin_event(int fd);
    bool get_interface_mac_addr(unsigned int if_index, uint8_t *addr);
    bool send_packet_to_network_interface(unsigned int if_index, Packet &packet);
    void set_al_mac_addr(const uint8_t *addr);
    void set_primary_vlan_id(const uint16_t primary_vlan_id, bool add);

    //
    // BROKER STUFF
    //
    void handle_broker_pollin_event(std::unique_ptr<messages::Message> &msg);
    void handle_broker_cmdu_tx_message(messages::CmduTxMessage &msg);
    void handle_broker_interface_configuration_request_message(
        messages::InterfaceConfigurationRequestMessage &msg);
    void handle_al_mac_addr_configuration_message(messages::AlMacAddressConfigurationMessage &msg);
    void handle_vlan_configuration_request_message(messages::VlanConfigurationRequestMessage &msg);
    bool send_packet_to_broker(Packet &packet);
    uint16_t get_next_message_id();

    //
    // PACKET PROCESSING STUFF
    //
    void handle_packet(Packet &packet);
    void update_neighbours(const Packet &packet);
    bool verify_packet(const Packet &packet);
    bool de_duplicate_packet(Packet &packet);
    void remove_packet_from_de_duplication_map(const Packet &packet);
    bool de_fragment_packet(Packet &packet);
    bool fragment_and_send_packet_to_network_interface(unsigned int if_index, Packet &packet);
    bool forward_packet_single(Packet &packet);
    bool forward_packet(Packet &Packet);
};

inline std::ostream &operator<<(std::ostream &os, const Ieee1905Transport::Packet &m)
{
    return m.print(os);
}

} // namespace transport
} // namespace beerocks

#endif // MAP_TRANSPORT_IEEE1905_TRANSPORT_H_
