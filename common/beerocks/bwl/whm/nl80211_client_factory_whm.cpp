/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2022 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#include <bwl/nl80211_client_factory.h>

#include "nl80211_client_whm.h"

#include <bcl/beerocks_backport.h>

namespace bwl {

std::unique_ptr<nl80211_client> nl80211_client_factory::create_instance()
{
    return std::make_unique<nl80211_client_whm>();
}

} // namespace bwl
