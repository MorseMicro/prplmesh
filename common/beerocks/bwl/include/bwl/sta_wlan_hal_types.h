/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef _BWL_STA_WLAN_HAL_TYPES_H_
#define _BWL_STA_WLAN_HAL_TYPES_H_

#include <stdint.h>

#include <bcl/network/net_struct.h>

namespace bwl {

// 16 Octets + 4 dashes + null terminator RFC 4122
#define UUID_STR_SIZE (16 * 2 + 4 + 4)

struct sScanResult {
    sScanResult()
        : bssid({0}), channel(0), freq_type(beerocks::eFreqType::FREQ_UNKNOWN),
          rssi(UINT8_MAX){}; //used UINT8_MAX to initialise it with non-valid value
    sMacAddr bssid;
    uint8_t channel;
    beerocks::eFreqType freq_type;
    int8_t rssi;
};

constexpr int invalid_network_id = -1;

} // namespace bwl

#endif // _BWL_STA_WLAN_HAL_TYPES_H_
