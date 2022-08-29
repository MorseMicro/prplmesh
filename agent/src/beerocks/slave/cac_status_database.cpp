/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2022 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#include "cac_status_database.h"
#include "agent_db.h"
#include "cac_capabilities_database.h"

namespace beerocks {

CacAvailableChannels CacStatusDatabase::get_available_channels(const sMacAddr &radio_mac) const
{
    CacAvailableChannels ret;

    auto db = AgentDB::get();

    const auto radio = db->get_radio_by_mac(radio_mac);
    if (!radio) {
        LOG(ERROR) << "Failed to find the Radio with mac: " << radio_mac;
        return ret;
    }

    for (const auto &channel_channel_info : radio->channels_list) {
        uint8_t channel    = channel_channel_info.first;
        auto &channel_info = channel_channel_info.second;

        if (channel_info.dfs_state == beerocks_message::eDfsState::USABLE ||
            channel_info.dfs_state == beerocks_message::eDfsState::AVAILABLE) {

            for (auto &bw_info : channel_info.supported_bw_list) {
                beerocks::message::sWifiChannel wifi_ch(channel, bw_info.bandwidth);
                sCacStatus cac_status;
                cac_status.channel = channel;
                cac_status.operating_class =
                    son::wireless_utils::get_operating_class_by_channel(wifi_ch);

                // Todo: https://jira.prplfoundation.org/browse/PPM-1088
                cac_status.duration = std::chrono::seconds(0);
                ret.push_back(cac_status);
            }
        }
    }
    return ret;
}

bool CacStatusDatabase::add_cac_status_report_tlv(
    const AgentDB::sRadio *radio,
    const std::shared_ptr<wfa_map::tlvProfile2CacStatusReport> cac_status_report_tlv)
{
    if (!radio) {
        return false;
    }

    auto available_channels = get_available_channels(radio->front.iface_mac);
    if (!available_channels.empty() &&
        !cac_status_report_tlv->alloc_available_channels(available_channels.size())) {
        LOG(ERROR) << "Failed to allocate " << available_channels.size()
                   << " structures for available channels";
    }

    for (unsigned int i = 0; i < available_channels.size(); ++i) {
        auto &available_ref           = std::get<1>(cac_status_report_tlv->available_channels(i));
        available_ref.operating_class = available_channels[i].operating_class;
        available_ref.channel         = available_channels[i].channel;
        if (son::wireless_utils::is_dfs_channel(available_channels[i].channel)) {
            available_ref.minutes_since_cac_completion = static_cast<uint16_t>(
                std::chrono::duration_cast<std::chrono::minutes>(available_channels[i].duration)
                    .count());
        } else {
            // Set to zero for non-DFS channels
            available_ref.minutes_since_cac_completion = 0;
        }
    }

    return true;
}

sCacCompletionStatus CacStatusDatabase::get_completion_status(const AgentDB::sRadio *radio) const
{
    sCacCompletionStatus ret;

    if (!radio) {
        return ret;
    }

    // TODO: Below condition should not be reached (PPM-1833).
    if (!radio->last_switch_channel_request) {
        LOG(WARNING) << "No switch channel request to relate to, thus completion status is empty"
                     << " for radio " << radio->front.iface_mac;
        return ret;
    }
    uint8_t main_channel = radio->last_switch_channel_request->channel;

    auto channel_info = radio->channels_list.find(main_channel);
    if (channel_info == radio->channels_list.end()) {
        LOG(ERROR) << "Can't find channel info for " << main_channel
                   << " thus completion status is empty";
        return ret;
    }

    // main operating class and channel
    message::sWifiChannel wifi_ch(main_channel, radio->last_switch_channel_request->bandwidth);
    ret.channel         = main_channel;
    ret.operating_class = son::wireless_utils::get_operating_class_by_channel(wifi_ch);

    // fill the detected operating class and channels.
    if (channel_info->second.dfs_state == beerocks_message::eDfsState::UNAVAILABLE) {
        ret.completion_status     = sCacCompletionStatus::eCacCompletionStatus::RADAR_DETECTED;
        auto overlapping_channels = son::wireless_utils::get_overlapping_channels(
            radio->last_switch_channel_request->channel);
        // TODO: Add missing values. See PPM-1089.
        for (auto &overlap_ch : overlapping_channels) {
            message::sWifiChannel overlap_wifi_ch(overlap_ch.first, overlap_ch.second);
            ret.overlapping_channels.emplace_back(
                son::wireless_utils::get_operating_class_by_channel(overlap_wifi_ch),
                overlap_ch.first);
        }
    } else {
        ret.completion_status = sCacCompletionStatus::eCacCompletionStatus::SUCCESSFUL;
    }

    return ret;
}

bool CacStatusDatabase::add_cac_completion_report_tlv(
    const AgentDB::sRadio *radio,
    const std::shared_ptr<wfa_map::tlvProfile2CacCompletionReport> cac_completion_report_tlv)
{
    if (!radio) {
        return false;
    }

    const auto &cac_radio = cac_completion_report_tlv->create_cac_radios();
    if (!cac_radio) {
        LOG(ERROR) << "Failed to create cac radio for " << radio->front.iface_mac;
        return false;
    }

    cac_radio->radio_uid()             = radio->front.iface_mac;
    const auto &cac_completion         = get_completion_status(radio);
    cac_radio->operating_class()       = cac_completion.operating_class;
    cac_radio->channel()               = cac_completion.channel;
    cac_radio->cac_completion_status() = cac_completion.completion_status;

    if (!cac_completion.overlapping_channels.empty()) {
        cac_radio->alloc_detected_pairs(cac_completion.overlapping_channels.size());
        for (unsigned int i = 0; i < cac_completion.overlapping_channels.size(); ++i) {
            if (std::get<0>(cac_radio->detected_pairs(i))) {
                auto &cac_detected_pair = std::get<1>(cac_radio->detected_pairs(i));
                cac_detected_pair.operating_class_detected =
                    cac_completion.overlapping_channels[i].first;
                cac_detected_pair.channel_detected = cac_completion.overlapping_channels[i].second;
            }
        }
    }
    cac_completion_report_tlv->add_cac_radios(cac_radio);
    return true;
}

} // namespace beerocks
