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

#include <tlvf/ieee_1905_1/tlvWsc.h>
#include <tlvf/tlvflogging.h>

using namespace ieee1905_1;

tlvWsc::tlvWsc(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
tlvWsc::tlvWsc(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
tlvWsc::~tlvWsc() {
}
const eTlvType& tlvWsc::type() {
    return (const eTlvType&)(*m_type);
}

const uint16_t& tlvWsc::length() {
    return (const uint16_t&)(*m_length);
}

uint8_t* tlvWsc::payload(size_t idx) {
    if ( (m_payload_idx__ == 0) || (m_payload_idx__ <= idx) ) {
        TLVF_LOG(ERROR) << "Requested index is greater than the number of available entries";
        return nullptr;
    }
    return &(m_payload[idx]);
}

bool tlvWsc::set_payload(const void* buffer, size_t size) {
    if (buffer == nullptr) {
        TLVF_LOG(WARNING) << "set_payload received a null pointer.";
        return false;
    }
    if (m_payload_idx__ != 0) {
        TLVF_LOG(ERROR) << "set_payload was already allocated!";
        return false;
    }
    if (!alloc_payload(size)) { return false; }
    std::copy_n(reinterpret_cast<const uint8_t *>(buffer), size, m_payload);
    return true;
}
bool tlvWsc::alloc_payload(size_t count) {
    if (m_lock_order_counter__ > 0) {;
        TLVF_LOG(ERROR) << "Out of order allocation for variable length list payload, abort!";
        return false;
    }
    size_t len = sizeof(uint8_t) * count;
    if(getBuffRemainingBytes() < len )  {
        TLVF_LOG(ERROR) << "Not enough available space on buffer - can't allocate";
        return false;
    }
    m_lock_order_counter__ = 0;
    uint8_t *src = (uint8_t *)&m_payload[m_payload_idx__];
    uint8_t *dst = src + len;
    if (!m_parse__) {
        size_t move_length = getBuffRemainingBytes(src) - len;
        std::copy_n(src, move_length, dst);
    }
    m_payload_idx__ += count;
    if (!buffPtrIncrementSafe(len)) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << len << ") Failed!";
        return false;
    }
    if(m_length){ (*m_length) += len; }
    return true;
}

void tlvWsc::class_swap()
{
    tlvf_swap(16, reinterpret_cast<uint8_t*>(m_length));
}

bool tlvWsc::finalize()
{
    if (m_parse__) {
        TLVF_LOG(DEBUG) << "finalize() called but m_parse__ is set";
        return true;
    }
    if (m_finalized__) {
        TLVF_LOG(DEBUG) << "finalize() called for already finalized class";
        return true;
    }
    if (!isPostInitSucceeded()) {
        TLVF_LOG(ERROR) << "post init check failed";
        return false;
    }
    if (m_inner__) {
        if (!m_inner__->finalize()) {
            TLVF_LOG(ERROR) << "m_inner__->finalize() failed";
            return false;
        }
        auto tailroom = m_inner__->getMessageBuffLength() - m_inner__->getMessageLength();
        m_buff_ptr__ -= tailroom;
        *m_length -= tailroom;
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t tlvWsc::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(eTlvType); // type
    class_size += sizeof(uint16_t); // length
    return class_size;
}

bool tlvWsc::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_type = reinterpret_cast<eTlvType*>(m_buff_ptr__);
    if (!m_parse__) *m_type = eTlvType::TLV_WSC;
    if (!buffPtrIncrementSafe(sizeof(eTlvType))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(eTlvType) << ") Failed!";
        return false;
    }
    m_length = reinterpret_cast<uint16_t*>(m_buff_ptr__);
    if (!m_parse__) *m_length = 0;
    if (!buffPtrIncrementSafe(sizeof(uint16_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint16_t) << ") Failed!";
        return false;
    }
    m_payload = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (m_length && m_parse__) {
        auto swap_len = *m_length;
        tlvf_swap((sizeof(swap_len) * 8), reinterpret_cast<uint8_t*>(&swap_len));
        size_t len = swap_len;
        len -= (m_buff_ptr__ - sizeof(*m_type) - sizeof(*m_length) - m_buff__);
        m_payload_idx__ = len/sizeof(uint8_t);
        if (!buffPtrIncrementSafe(len)) {
            LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << len << ") Failed!";
            return false;
        }
    }
    if (m_parse__) { class_swap(); }
    if (m_parse__) {
        if (*m_type != eTlvType::TLV_WSC) {
            TLVF_LOG(ERROR) << "TLV type mismatch. Expected value: " << int(eTlvType::TLV_WSC) << ", received value: " << int(*m_type);
            return false;
        }
    }
    return true;
}


