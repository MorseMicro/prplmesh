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

#ifndef _TLVF_WFA_MAP_TLVPROFILE2CACREQUEST_H_
#define _TLVF_WFA_MAP_TLVPROFILE2CACREQUEST_H_

#include <cstddef>
#include <stdint.h>
#include <tlvf/swap.h>
#include <string.h>
#include <memory>
#include <tlvf/BaseClass.h>
#include <tlvf/ClassList.h>
#include "tlvf/wfa_map/eTlvTypeMap.h"
#include <tuple>
#include <asm/byteorder.h>
#include "tlvf/common/sMacAddr.h"

namespace wfa_map {


class tlvProfile2CacRequest : public BaseClass
{
    public:
        tlvProfile2CacRequest(uint8_t* buff, size_t buff_len, bool parse = false);
        explicit tlvProfile2CacRequest(std::shared_ptr<BaseClass> base, bool parse = false);
        ~tlvProfile2CacRequest();

        typedef struct sCacMethod {
            #if defined(__LITTLE_ENDIAN_BITFIELD)
            uint8_t rserved : 3;
            uint8_t cac_completion_action : 2;
            uint8_t cac_method : 3;
            #elif defined(__BIG_ENDIAN_BITFIELD)
            uint8_t cac_method : 3;
            uint8_t cac_completion_action : 2;
            uint8_t rserved : 3;
            #else
            #error "Bitfield macros are not defined"
            #endif
            void struct_swap(){
            }
            void struct_init(){
            }
        } __attribute__((packed)) sCacMethod;
        
        typedef struct sCacRadio {
            sMacAddr radio_uid;
            uint8_t operating_class;
            uint8_t channel;
            sCacMethod cac_method_bit_field;
            void struct_swap(){
                radio_uid.struct_swap();
                cac_method_bit_field.struct_swap();
            }
            void struct_init(){
                radio_uid.struct_init();
            }
        } __attribute__((packed)) sCacRadio;
        
        const eTlvTypeMap& type();
        const uint16_t& length();
        uint8_t& number_of_cac_radios();
        std::tuple<bool, sCacRadio&> cac_radios(size_t idx);
        bool alloc_cac_radios(size_t count = 1);
        void class_swap() override;
        bool finalize() override;
        static size_t get_initial_size();

    private:
        bool init();
        eTlvTypeMap* m_type = nullptr;
        uint16_t* m_length = nullptr;
        uint8_t* m_number_of_cac_radios = nullptr;
        sCacRadio* m_cac_radios = nullptr;
        size_t m_cac_radios_idx__ = 0;
        int m_lock_order_counter__ = 0;
};

}; // close namespace: wfa_map

#endif //_TLVF/WFA_MAP_TLVPROFILE2CACREQUEST_H_
