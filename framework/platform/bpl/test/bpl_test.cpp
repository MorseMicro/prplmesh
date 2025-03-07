/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#include <bpl/bpl_cfg.h>
#include <dlfcn.h>
#include <mapf/common/logger.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace mapf;

void getString(char *s, int size)
{
    if (!fgets(s, size, stdin)) {
        fprintf(stderr, "No input.\n");
        exit(1);
    }
}

int main()
{
    char inputInterface[32], userInputS[10];
    struct beerocks::bpl::BPL_WLAN_PARAMS wlan_params;

    while (1) {
        memset(inputInterface, 0, sizeof(inputInterface));
        printf("\n1. Query WLAN ready\n2. AP start\n3. AP stop\n4. STA start\n5. STA stop\n6. "
               "Restore at interface level\n7. Restore at full scope\n8. Set WiFI credentials\n9. "
               "Get WiFi credentials\n10. AP post init handling\n11. Exit\n");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getString(userInputS, 3);
        switch (atoi(userInputS)) {
        case 9:
            memset(&wlan_params, 0, sizeof(wlan_params));
            printf("Interface : ");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getString(inputInterface, sizeof(inputInterface));
            if (beerocks::bpl::cfg_get_wifi_params(inputInterface, &wlan_params) != 0) {
                MAPF_ERR("Failed to retrieve WiFi params for " << inputInterface << "\n");
            } else {
                MAPF_INFO("enabled " << wlan_params.enabled << " channel " << wlan_params.channel
                                     << "\n");
            }
            break;
        case 11:
            return 0;
        default:
            printf("Invalid selection\n");
            break;
        }
    }
    return 0;
}
