///////////////////////////////////////
// AUTO GENERATED FILE - DO NOT EDIT //
///////////////////////////////////////

/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef _TLVF_WFA_MAP_TLVUNASSOCIATEDSTALINKMETRICSRESPONSE_H_
#define _TLVF_WFA_MAP_TLVUNASSOCIATEDSTALINKMETRICSRESPONSE_H_

#include <cstddef>
#include <stdint.h>
#include <tlvf/swap.h>
#include <string.h>
#include <memory>
#include <tlvf/BaseClass.h>
#include <tlvf/ClassList.h>
#include "tlvf/wfa_map/eTlvTypeMap.h"
#include <tuple>
#include "tlvf/common/sMacAddr.h"

namespace wfa_map {


class tlvUnassociatedStaLinkMetricsResponse : public BaseClass
{
    public:
        tlvUnassociatedStaLinkMetricsResponse(uint8_t* buff, size_t buff_len, bool parse = false);
        explicit tlvUnassociatedStaLinkMetricsResponse(std::shared_ptr<BaseClass> base, bool parse = false);
        ~tlvUnassociatedStaLinkMetricsResponse();

        typedef struct sStaMetrics {
            sMacAddr sta_mac;
            uint8_t channel_number;
            uint32_t measurement_to_report_delta_msec;
            uint8_t uplink_rcpi_dbm_enc;
            void struct_swap(){
                sta_mac.struct_swap();
                tlvf_swap(32, reinterpret_cast<uint8_t*>(&measurement_to_report_delta_msec));
            }
            void struct_init(){
                sta_mac.struct_init();
            }
        } __attribute__((packed)) sStaMetrics;
        
        const eTlvTypeMap& type();
        const uint16_t& length();
        uint8_t& operating_class_of_channel_list();
        uint8_t& sta_list_length();
        std::tuple<bool, sStaMetrics&> sta_list(size_t idx);
        bool alloc_sta_list(size_t count = 1);
        void class_swap() override;
        bool finalize() override;
        static size_t get_initial_size();

    private:
        bool init();
        eTlvTypeMap* m_type = nullptr;
        uint16_t* m_length = nullptr;
        uint8_t* m_operating_class_of_channel_list = nullptr;
        uint8_t* m_sta_list_length = nullptr;
        sStaMetrics* m_sta_list = nullptr;
        size_t m_sta_list_idx__ = 0;
        int m_lock_order_counter__ = 0;
};

}; // close namespace: wfa_map

#endif //_TLVF/WFA_MAP_TLVUNASSOCIATEDSTALINKMETRICSRESPONSE_H_
