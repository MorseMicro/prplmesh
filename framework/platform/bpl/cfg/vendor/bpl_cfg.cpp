/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2021 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#include <bpl/bpl_cfg.h>
#include <mapf/common/utils.h>

using namespace mapf;

namespace beerocks {
namespace bpl {

bool get_serial_number(std::string &serial_number)
{
#if !defined(MORSE_MICRO)
    serial_number.assign("prplmesh12345");
#else
    serial_number.assign("MM6108-123456");
#endif
    return true;
}

bool get_ruid_chipset_vendor(const sMacAddr &ruid, std::string &chipset_vendor)
{
#if !defined(MORSE_MICRO)
    chipset_vendor = "prplmesh";
#else
    chipset_vendor = "MorseMicro";
#endif
    return true;
}

bool get_max_prioritization_rules(uint32_t &max_prioritization_rules)
{
    // On EasyMesh standard 9.1 it is said that a Multi-AP Agent that implements Profile-3, need to:
    // "Set Max Total Number Service Prioritization Rules to one".
    // This requirement will probably change on future version of the standard.
    max_prioritization_rules = 1;
    return true;
}

} // namespace bpl
} // namespace beerocks
