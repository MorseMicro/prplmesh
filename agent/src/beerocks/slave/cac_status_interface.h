/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2022 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef _CAC_STATUS_H_
#define _CAC_STATUS_H_

#include <chrono>
#include <vector>

#include "agent_db.h"
#include "tlvf/wfa_map/tlvProfile2CacCompletionReport.h"
#include "tlvf/wfa_map/tlvProfile2CacStatusReport.h"

namespace beerocks {

struct sCacStatus {
    uint8_t operating_class = 0;
    uint8_t channel         = 0;
    // duration is used based on the context
    std::chrono::seconds duration = std::chrono::seconds(0);

    bool operator<(const sCacStatus &status) const
    {
        return std::tie(operating_class, channel) <
               std::tie(status.operating_class, status.channel);
    }
};

using CacAvailableChannels    = std::vector<sCacStatus>;
using CacNonOccupancyChannels = std::vector<sCacStatus>;
using CacActiveChannels       = std::vector<sCacStatus>;

/**
 * Completion status is:
 * operating class + channel + completion status (duration has no meaning)
 * a vector of operating class + channel that are overlapping with the first pair of operating
 * class and channel
 */
struct sCacCompletionStatus : public sCacStatus {
    using eCacCompletionStatus             = wfa_map::cCacCompletionReportRadio::eCompletionStatus;
    eCacCompletionStatus completion_status = eCacCompletionStatus::NOT_PERFORMED;
    /** Operating class + channel that are overlapping with the sCacStatus operating class / channel. */
    std::vector<std::pair<uint8_t, uint8_t>> overlapping_channels;
};

class CacStatusInterface {
public:
    virtual ~CacStatusInterface() = default;

    /**
     * @brief Update all collected channel information by given radio.
     * 
     * @param radio Pointer to the AgentDB's radio element.
     * @return True on success, false otherwise.
     */
    virtual bool update_cac_status_db(const AgentDB::sRadio *radio) = 0;

    /**
     * @brief Get a list of all CAC-able channels (Available of Usable) of a given radio mac.
     * 
     * @param radio_mac MAC address of radio for which channel list is requested.
     * @return CacAvailableChannels List of channels.
     */
    virtual CacAvailableChannels get_available_channels(const sMacAddr &radio_mac) const = 0;

    /**
     * @brief Get a list of all channels that cannot be occupied (radar was detected) of a given radio mac.
     * 
     * @param radio_mac MAC address of radio for which channel list is requested.
     * @return CacNonOccupancyChannels List of channels.
     */
    virtual CacNonOccupancyChannels get_non_occupancy_channels(const sMacAddr &radio_mac) const = 0;

    /**
     * @brief Get a list of all channels that have an active CAC ongoing of a given radio mac.
     * 
     * @param radio_mac MAC address of radio for which channel list is requested.
     * @return CacActiveChannels List of channels.
     */
    virtual CacActiveChannels get_active_channels(const sMacAddr &radio_mac) const = 0;

    /**
     * @brief Get the completion status object of a given radio.
     * 
     * @param radio Pointer to the AgentDB's radio element.
     * @return sCacCompletionStatus struct of the channel.
     */
    virtual sCacCompletionStatus get_completion_status(const AgentDB::sRadio *radio) const = 0;
};

// utilities based on CacCapabilities interface

} // namespace beerocks

#endif
