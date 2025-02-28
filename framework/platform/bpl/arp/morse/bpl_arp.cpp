/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2019-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#include <bpl/bpl_arp.h>
#include <mapf/common/logger.h>

namespace beerocks {
namespace bpl {

int arp_mon_start(BPL_ARP_MON_CTX *ctx, const char *iface)
{
    MORSE_NOT_IMPLEMENTED;
    return -2;
}

int arp_mon_stop(BPL_ARP_MON_CTX ctx)
{
    MORSE_NOT_IMPLEMENTED;
    return 0;
}

int arp_mon_get_fd(BPL_ARP_MON_CTX ctx)
{
    MORSE_NOT_IMPLEMENTED;
    return -1;
}

int arp_mon_get_raw_arp_fd(BPL_ARP_MON_CTX ctx)
{
    MORSE_NOT_IMPLEMENTED;
    return -1;
}

int arp_mon_process(BPL_ARP_MON_CTX ctx, struct BPL_ARP_MON_ENTRY *entry)
{
    MORSE_NOT_IMPLEMENTED;
    return 0;
}

int arp_mon_process_raw_arp(BPL_ARP_MON_CTX ctx, struct BPL_ARP_MON_ENTRY *entry)
{
    MORSE_NOT_IMPLEMENTED;
    return 0;
}

int arp_mon_probe(BPL_ARP_MON_CTX ctx, const uint8_t mac[BPL_ARP_MON_MAC_LEN],
                  const uint8_t ip[BPL_ARP_MON_IP_LEN], int task_id)
{
    MORSE_NOT_IMPLEMENTED;
    return 0;
}

int arp_mon_get_mac_for_ip(BPL_ARP_MON_CTX ctx, const uint8_t ip[BPL_ARP_MON_IP_LEN],
                           uint8_t mac[BPL_ARP_MON_MAC_LEN])
{
    MORSE_NOT_IMPLEMENTED;
    return -1;
}

int arp_mon_get_ip_for_mac(BPL_ARP_MON_CTX ctx, const uint8_t mac[BPL_ARP_MON_MAC_LEN],
                           uint8_t ip[BPL_ARP_MON_IP_LEN])
{
    MORSE_NOT_IMPLEMENTED;
    return -1;
}

int arp_get_bridge_iface(const char bridge[BPL_ARP_IFACE_NAME_LEN],
                         const uint8_t mac[BPL_ARP_MON_MAC_LEN], char iface[BPL_ARP_IFACE_NAME_LEN])
{
    MORSE_NOT_IMPLEMENTED;
    return -1;
}

} // namespace bpl
} // namespace beerocks
