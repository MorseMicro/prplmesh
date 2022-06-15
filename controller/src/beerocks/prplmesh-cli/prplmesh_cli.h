/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2022 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef _PRPLMESH_CLI_H
#define _PRPLMESH_CLI_H

#ifndef AMBIORIX_BACKEND_PATH
#define AMBIORIX_BACKEND_PATH "/usr/bin/mods/amxb/mod-amxb-ubus.so"
#endif // AMBIORIX_BACKEND_PATH

#ifndef AMBIORIX_BUS_URI
#define AMBIORIX_BUS_URI "ubus:"
#endif // AMBIORIX_BUS_URI

#include <map>
#include <string>
#include <vector>

#include "prplmesh_amx_client.h"

namespace beerocks {
namespace prplmesh_api {

class prplmesh_cli {
public:
    prplmesh_cli();
    bool get_ip_from_iface(const std::string &iface, std::string &ip);
    bool prpl_conn_map(void);
    bool print_device_info(std::string agent_mac, std::string skip_mac);
    bool print_radio(std::string device_path);
    float get_freq_from_class(uint32_t oper_class);

    std::shared_ptr<beerocks::prplmesh_amx::AmxClient> m_amx_client;

    typedef struct conn_map_t {
        std::string device_ht_path = "Device.WiFi.DataElements.Network.Device.*.";
        uint32_t device_number;
        std::string controller_id;
        std::string bridge_ip_v4;
        std::string radio_id;
        std::string bss_id;
        std::string ssid;
        uint32_t channel;
        uint32_t oper_class;
    } conn_map_t;

private:
};

} // namespace prplmesh_api
} // namespace beerocks

#endif // _PRPLMESH_CLI_H
