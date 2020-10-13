/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#include "ambiorix_dummy.h"

namespace beerocks {
namespace nbapi {

AmbiorixDummy::~AmbiorixDummy() {}
bool AmbiorixDummy::set(const std::string &relative_path, const std::string &parameter,
                        const std::string &value)
{
    return true;
}
bool AmbiorixDummy::set(const std::string &relative_path, const std::string &parameter,
                        const int32_t &value)
{
    return true;
}
bool AmbiorixDummy::set(const std::string &relative_path, const std::string &parameter,
                        const int64_t &value)
{
    return true;
}
bool AmbiorixDummy::set(const std::string &relative_path, const std::string &parameter,
                        const uint32_t &value)
{
    return true;
}
bool AmbiorixDummy::set(const std::string &relative_path, const std::string &parameter,
                        const uint64_t &value)
{
    return true;
}
bool AmbiorixDummy::set(const std::string &relative_path, const std::string &parameter,
                        const bool &value)
{
    return true;
}
bool AmbiorixDummy::set(const std::string &relative_path, const std::string &parameter,
                        const double &value)
{
    return true;
}
uint32_t AmbiorixDummy::add_instance(const std::string &relative_path) { return true; }
bool AmbiorixDummy::remove_instance(const std::string &relative_path, uint32_t index)
{
    return true;
}
uint32_t AmbiorixDummy::get_instance_index(const std::string &specific_path, const std::string &key)
{
    // Return false (0) because method can be used for checking instance present in Data Model or not
    return 0;
}
std::string AmbiorixDummy::get_datamodel_time_format() { return ""; }

} // namespace nbapi
} // namespace beerocks
