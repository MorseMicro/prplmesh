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

#include <beerocks/tlvf/beerocks_message_monitor.h>
#include <tlvf/tlvflogging.h>

using namespace beerocks_message;

cACTION_MONITOR_HOSTAP_AP_DISABLED_NOTIFICATION::cACTION_MONITOR_HOSTAP_AP_DISABLED_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_HOSTAP_AP_DISABLED_NOTIFICATION::cACTION_MONITOR_HOSTAP_AP_DISABLED_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_HOSTAP_AP_DISABLED_NOTIFICATION::~cACTION_MONITOR_HOSTAP_AP_DISABLED_NOTIFICATION() {
}
int8_t& cACTION_MONITOR_HOSTAP_AP_DISABLED_NOTIFICATION::vap_id() {
    return (int8_t&)(*m_vap_id);
}

void cACTION_MONITOR_HOSTAP_AP_DISABLED_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
}

bool cACTION_MONITOR_HOSTAP_AP_DISABLED_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_HOSTAP_AP_DISABLED_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(int8_t); // vap_id
    return class_size;
}

bool cACTION_MONITOR_HOSTAP_AP_DISABLED_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_vap_id = reinterpret_cast<int8_t*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(int8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(int8_t) << ") Failed!";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_JOINED_NOTIFICATION::cACTION_MONITOR_JOINED_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_JOINED_NOTIFICATION::cACTION_MONITOR_JOINED_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_JOINED_NOTIFICATION::~cACTION_MONITOR_JOINED_NOTIFICATION() {
}
uint8_t& cACTION_MONITOR_JOINED_NOTIFICATION::iface_name_length() {
    return (uint8_t&)(*m_iface_name_length);
}

std::string cACTION_MONITOR_JOINED_NOTIFICATION::iface_name_str() {
    char *iface_name_ = iface_name();
    if (!iface_name_) { return std::string(); }
    auto str = std::string(iface_name_, m_iface_name_idx__);
    auto pos = str.find_first_of('\0');
    if (pos != std::string::npos) {
        str.erase(pos);
    }
    return str;
}

char* cACTION_MONITOR_JOINED_NOTIFICATION::iface_name(size_t length) {
    if( (m_iface_name_idx__ == 0) || (m_iface_name_idx__ < length) ) {
        TLVF_LOG(ERROR) << "iface_name length is smaller than requested length";
        return nullptr;
    }
    return ((char*)m_iface_name);
}

bool cACTION_MONITOR_JOINED_NOTIFICATION::set_iface_name(const std::string& str) { return set_iface_name(str.c_str(), str.size()); }
bool cACTION_MONITOR_JOINED_NOTIFICATION::set_iface_name(const char str[], size_t size) {
    if (str == nullptr) {
        TLVF_LOG(WARNING) << "set_iface_name received a null pointer.";
        return false;
    }
    if (m_iface_name_idx__ != 0) {
        TLVF_LOG(ERROR) << "set_iface_name was already allocated!";
        return false;
    }
    if (!alloc_iface_name(size)) { return false; }
    std::copy(str, str + size, m_iface_name);
    return true;
}
bool cACTION_MONITOR_JOINED_NOTIFICATION::alloc_iface_name(size_t count) {
    if (m_lock_order_counter__ > 0) {;
        TLVF_LOG(ERROR) << "Out of order allocation for variable length list iface_name, abort!";
        return false;
    }
    size_t len = sizeof(char) * count;
    if(getBuffRemainingBytes() < len )  {
        TLVF_LOG(ERROR) << "Not enough available space on buffer - can't allocate";
        return false;
    }
    m_lock_order_counter__ = 0;
    uint8_t *src = (uint8_t *)&m_iface_name[*m_iface_name_length];
    uint8_t *dst = src + len;
    if (!m_parse__) {
        size_t move_length = getBuffRemainingBytes(src) - len;
        std::copy_n(src, move_length, dst);
    }
    m_iface_name_idx__ += count;
    *m_iface_name_length += count;
    if (!buffPtrIncrementSafe(len)) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << len << ") Failed!";
        return false;
    }
    return true;
}

void cACTION_MONITOR_JOINED_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
}

bool cACTION_MONITOR_JOINED_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_JOINED_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(uint8_t); // iface_name_length
    return class_size;
}

bool cACTION_MONITOR_JOINED_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_iface_name_length = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!m_parse__) *m_iface_name_length = 0;
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    m_iface_name = reinterpret_cast<char*>(m_buff_ptr__);
    uint8_t iface_name_length = *m_iface_name_length;
    m_iface_name_idx__ = iface_name_length;
    if (!buffPtrIncrementSafe(sizeof(char) * (iface_name_length))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(char) * (iface_name_length) << ") Failed!";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_SON_CONFIG_UPDATE::cACTION_MONITOR_SON_CONFIG_UPDATE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_SON_CONFIG_UPDATE::cACTION_MONITOR_SON_CONFIG_UPDATE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_SON_CONFIG_UPDATE::~cACTION_MONITOR_SON_CONFIG_UPDATE() {
}
sSonConfig& cACTION_MONITOR_SON_CONFIG_UPDATE::config() {
    return (sSonConfig&)(*m_config);
}

void cACTION_MONITOR_SON_CONFIG_UPDATE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_config->struct_swap();
}

bool cACTION_MONITOR_SON_CONFIG_UPDATE::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_SON_CONFIG_UPDATE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sSonConfig); // config
    return class_size;
}

bool cACTION_MONITOR_SON_CONFIG_UPDATE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_config = reinterpret_cast<sSonConfig*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sSonConfig))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sSonConfig) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_config->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CHANGE_MODULE_LOGGING_LEVEL::cACTION_MONITOR_CHANGE_MODULE_LOGGING_LEVEL(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANGE_MODULE_LOGGING_LEVEL::cACTION_MONITOR_CHANGE_MODULE_LOGGING_LEVEL(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANGE_MODULE_LOGGING_LEVEL::~cACTION_MONITOR_CHANGE_MODULE_LOGGING_LEVEL() {
}
sLoggingLevelChange& cACTION_MONITOR_CHANGE_MODULE_LOGGING_LEVEL::params() {
    return (sLoggingLevelChange&)(*m_params);
}

void cACTION_MONITOR_CHANGE_MODULE_LOGGING_LEVEL::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_CHANGE_MODULE_LOGGING_LEVEL::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CHANGE_MODULE_LOGGING_LEVEL::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sLoggingLevelChange); // params
    return class_size;
}

bool cACTION_MONITOR_CHANGE_MODULE_LOGGING_LEVEL::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sLoggingLevelChange*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sLoggingLevelChange))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sLoggingLevelChange) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_HEARTBEAT_NOTIFICATION::cACTION_MONITOR_HEARTBEAT_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_HEARTBEAT_NOTIFICATION::cACTION_MONITOR_HEARTBEAT_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_HEARTBEAT_NOTIFICATION::~cACTION_MONITOR_HEARTBEAT_NOTIFICATION() {
}
void cACTION_MONITOR_HEARTBEAT_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
}

bool cACTION_MONITOR_HEARTBEAT_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_HEARTBEAT_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    return class_size;
}

bool cACTION_MONITOR_HEARTBEAT_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_START_MONITORING_REQUEST::cACTION_MONITOR_CLIENT_START_MONITORING_REQUEST(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_START_MONITORING_REQUEST::cACTION_MONITOR_CLIENT_START_MONITORING_REQUEST(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_START_MONITORING_REQUEST::~cACTION_MONITOR_CLIENT_START_MONITORING_REQUEST() {
}
sClientMonitoringParams& cACTION_MONITOR_CLIENT_START_MONITORING_REQUEST::params() {
    return (sClientMonitoringParams&)(*m_params);
}

void cACTION_MONITOR_CLIENT_START_MONITORING_REQUEST::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_CLIENT_START_MONITORING_REQUEST::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_START_MONITORING_REQUEST::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sClientMonitoringParams); // params
    return class_size;
}

bool cACTION_MONITOR_CLIENT_START_MONITORING_REQUEST::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sClientMonitoringParams*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sClientMonitoringParams))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sClientMonitoringParams) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_START_MONITORING_RESPONSE::cACTION_MONITOR_CLIENT_START_MONITORING_RESPONSE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_START_MONITORING_RESPONSE::cACTION_MONITOR_CLIENT_START_MONITORING_RESPONSE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_START_MONITORING_RESPONSE::~cACTION_MONITOR_CLIENT_START_MONITORING_RESPONSE() {
}
uint8_t& cACTION_MONITOR_CLIENT_START_MONITORING_RESPONSE::success() {
    return (uint8_t&)(*m_success);
}

void cACTION_MONITOR_CLIENT_START_MONITORING_RESPONSE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
}

bool cACTION_MONITOR_CLIENT_START_MONITORING_RESPONSE::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_START_MONITORING_RESPONSE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(uint8_t); // success
    return class_size;
}

bool cACTION_MONITOR_CLIENT_START_MONITORING_RESPONSE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_success = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_REQUEST::cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_REQUEST(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_REQUEST::cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_REQUEST(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_REQUEST::~cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_REQUEST() {
}
sNodeRssiMeasurementRequest& cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_REQUEST::params() {
    return (sNodeRssiMeasurementRequest&)(*m_params);
}

void cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_REQUEST::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_REQUEST::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_REQUEST::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sNodeRssiMeasurementRequest); // params
    return class_size;
}

bool cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_REQUEST::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sNodeRssiMeasurementRequest*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sNodeRssiMeasurementRequest))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sNodeRssiMeasurementRequest) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_NOTIFICATION::cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_NOTIFICATION::cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_NOTIFICATION::~cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_NOTIFICATION() {
}
sNodeRssiMeasurement& cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_NOTIFICATION::params() {
    return (sNodeRssiMeasurement&)(*m_params);
}

void cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sNodeRssiMeasurement); // params
    return class_size;
}

bool cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sNodeRssiMeasurement*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sNodeRssiMeasurement))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sNodeRssiMeasurement) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_RESPONSE::cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_RESPONSE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_RESPONSE::cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_RESPONSE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_RESPONSE::~cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_RESPONSE() {
}
sNodeRssiMeasurement& cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_RESPONSE::params() {
    return (sNodeRssiMeasurement&)(*m_params);
}

void cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_RESPONSE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_RESPONSE::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_RESPONSE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sNodeRssiMeasurement); // params
    return class_size;
}

bool cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_RESPONSE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sNodeRssiMeasurement*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sNodeRssiMeasurement))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sNodeRssiMeasurement) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_NO_RESPONSE_NOTIFICATION::cACTION_MONITOR_CLIENT_NO_RESPONSE_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_NO_RESPONSE_NOTIFICATION::cACTION_MONITOR_CLIENT_NO_RESPONSE_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_NO_RESPONSE_NOTIFICATION::~cACTION_MONITOR_CLIENT_NO_RESPONSE_NOTIFICATION() {
}
sMacAddr& cACTION_MONITOR_CLIENT_NO_RESPONSE_NOTIFICATION::mac() {
    return (sMacAddr&)(*m_mac);
}

void cACTION_MONITOR_CLIENT_NO_RESPONSE_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_mac->struct_swap();
}

bool cACTION_MONITOR_CLIENT_NO_RESPONSE_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_NO_RESPONSE_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sMacAddr); // mac
    return class_size;
}

bool cACTION_MONITOR_CLIENT_NO_RESPONSE_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_mac = reinterpret_cast<sMacAddr*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sMacAddr))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sMacAddr) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_mac->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_START_NOTIFICATION::cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_START_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_START_NOTIFICATION::cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_START_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_START_NOTIFICATION::~cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_START_NOTIFICATION() {
}
sMacAddr& cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_START_NOTIFICATION::mac() {
    return (sMacAddr&)(*m_mac);
}

void cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_START_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_mac->struct_swap();
}

bool cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_START_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_START_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sMacAddr); // mac
    return class_size;
}

bool cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_START_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_mac = reinterpret_cast<sMacAddr*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sMacAddr))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sMacAddr) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_mac->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_CMD_RESPONSE::cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_CMD_RESPONSE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_CMD_RESPONSE::cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_CMD_RESPONSE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_CMD_RESPONSE::~cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_CMD_RESPONSE() {
}
sMacAddr& cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_CMD_RESPONSE::mac() {
    return (sMacAddr&)(*m_mac);
}

void cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_CMD_RESPONSE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_mac->struct_swap();
}

bool cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_CMD_RESPONSE::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_CMD_RESPONSE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sMacAddr); // mac
    return class_size;
}

bool cACTION_MONITOR_CLIENT_RX_RSSI_MEASUREMENT_CMD_RESPONSE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_mac = reinterpret_cast<sMacAddr*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sMacAddr))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sMacAddr) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_mac->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_NO_ACTIVITY_NOTIFICATION::cACTION_MONITOR_CLIENT_NO_ACTIVITY_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_NO_ACTIVITY_NOTIFICATION::cACTION_MONITOR_CLIENT_NO_ACTIVITY_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_NO_ACTIVITY_NOTIFICATION::~cACTION_MONITOR_CLIENT_NO_ACTIVITY_NOTIFICATION() {
}
sMacAddr& cACTION_MONITOR_CLIENT_NO_ACTIVITY_NOTIFICATION::mac() {
    return (sMacAddr&)(*m_mac);
}

void cACTION_MONITOR_CLIENT_NO_ACTIVITY_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_mac->struct_swap();
}

bool cACTION_MONITOR_CLIENT_NO_ACTIVITY_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_NO_ACTIVITY_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sMacAddr); // mac
    return class_size;
}

bool cACTION_MONITOR_CLIENT_NO_ACTIVITY_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_mac = reinterpret_cast<sMacAddr*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sMacAddr))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sMacAddr) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_mac->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_HOSTAP_ACTIVITY_NOTIFICATION::cACTION_MONITOR_HOSTAP_ACTIVITY_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_HOSTAP_ACTIVITY_NOTIFICATION::cACTION_MONITOR_HOSTAP_ACTIVITY_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_HOSTAP_ACTIVITY_NOTIFICATION::~cACTION_MONITOR_HOSTAP_ACTIVITY_NOTIFICATION() {
}
sApActivityNotificationParams& cACTION_MONITOR_HOSTAP_ACTIVITY_NOTIFICATION::params() {
    return (sApActivityNotificationParams&)(*m_params);
}

void cACTION_MONITOR_HOSTAP_ACTIVITY_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_HOSTAP_ACTIVITY_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_HOSTAP_ACTIVITY_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sApActivityNotificationParams); // params
    return class_size;
}

bool cACTION_MONITOR_HOSTAP_ACTIVITY_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sApActivityNotificationParams*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sApActivityNotificationParams))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sApActivityNotificationParams) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_REQUEST::cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_REQUEST(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_REQUEST::cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_REQUEST(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_REQUEST::~cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_REQUEST() {
}
sMacAddr& cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_REQUEST::sta_mac() {
    return (sMacAddr&)(*m_sta_mac);
}

void cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_REQUEST::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_sta_mac->struct_swap();
}

bool cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_REQUEST::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_REQUEST::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sMacAddr); // sta_mac
    return class_size;
}

bool cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_REQUEST::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_sta_mac = reinterpret_cast<sMacAddr*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sMacAddr))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sMacAddr) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_sta_mac->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE::cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE::cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE::~cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE() {
}
const uint16_t& cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE::length() {
    return (const uint16_t&)(*m_length);
}

sMacAddr& cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE::sta_mac() {
    return (sMacAddr&)(*m_sta_mac);
}

uint8_t& cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE::bssid_info_list_length() {
    return (uint8_t&)(*m_bssid_info_list_length);
}

std::tuple<bool, sBssidInfo&> cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE::bssid_info_list(size_t idx) {
    bool ret_success = ( (m_bssid_info_list_idx__ > 0) && (m_bssid_info_list_idx__ > idx) );
    size_t ret_idx = ret_success ? idx : 0;
    if (!ret_success) {
        TLVF_LOG(ERROR) << "Requested index is greater than the number of available entries";
    }
    return std::forward_as_tuple(ret_success, m_bssid_info_list[ret_idx]);
}

bool cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE::alloc_bssid_info_list(size_t count) {
    if (m_lock_order_counter__ > 0) {;
        TLVF_LOG(ERROR) << "Out of order allocation for variable length list bssid_info_list, abort!";
        return false;
    }
    size_t len = sizeof(sBssidInfo) * count;
    if(getBuffRemainingBytes() < len )  {
        TLVF_LOG(ERROR) << "Not enough available space on buffer - can't allocate";
        return false;
    }
    m_lock_order_counter__ = 0;
    uint8_t *src = (uint8_t *)&m_bssid_info_list[*m_bssid_info_list_length];
    uint8_t *dst = src + len;
    if (!m_parse__) {
        size_t move_length = getBuffRemainingBytes(src) - len;
        std::copy_n(src, move_length, dst);
    }
    m_bssid_info_list_idx__ += count;
    *m_bssid_info_list_length += count;
    if (!buffPtrIncrementSafe(len)) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << len << ") Failed!";
        return false;
    }
    if(m_length){ (*m_length) += len; }
    if (!m_parse__) { 
        for (size_t i = m_bssid_info_list_idx__ - count; i < m_bssid_info_list_idx__; i++) { m_bssid_info_list[i].struct_init(); }
    }
    return true;
}

void cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    tlvf_swap(16, reinterpret_cast<uint8_t*>(m_length));
    m_sta_mac->struct_swap();
    for (size_t i = 0; i < m_bssid_info_list_idx__; i++){
        m_bssid_info_list[i].struct_swap();
    }
}

bool cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE::finalize()
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

size_t cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(uint16_t); // length
    class_size += sizeof(sMacAddr); // sta_mac
    class_size += sizeof(uint8_t); // bssid_info_list_length
    return class_size;
}

bool cACTION_MONITOR_CLIENT_ASSOCIATED_STA_LINK_METRIC_RESPONSE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_length = reinterpret_cast<uint16_t*>(m_buff_ptr__);
    if (!m_parse__) *m_length = 0;
    if (!buffPtrIncrementSafe(sizeof(uint16_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint16_t) << ") Failed!";
        return false;
    }
    m_sta_mac = reinterpret_cast<sMacAddr*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sMacAddr))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sMacAddr) << ") Failed!";
        return false;
    }
    if(m_length && !m_parse__){ (*m_length) += sizeof(sMacAddr); }
    if (!m_parse__) { m_sta_mac->struct_init(); }
    m_bssid_info_list_length = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!m_parse__) *m_bssid_info_list_length = 0;
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    if(m_length && !m_parse__){ (*m_length) += sizeof(uint8_t); }
    m_bssid_info_list = reinterpret_cast<sBssidInfo*>(m_buff_ptr__);
    uint8_t bssid_info_list_length = *m_bssid_info_list_length;
    m_bssid_info_list_idx__ = bssid_info_list_length;
    if (!buffPtrIncrementSafe(sizeof(sBssidInfo) * (bssid_info_list_length))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sBssidInfo) * (bssid_info_list_length) << ") Failed!";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST::cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST::cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST::~cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST() {
}
const uint16_t& cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST::length() {
    return (const uint16_t&)(*m_length);
}

uint8_t& cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST::stations_list_length() {
    return (uint8_t&)(*m_stations_list_length);
}

std::tuple<bool, sUnassociatedStationInfo&> cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST::stations_list(size_t idx) {
    bool ret_success = ( (m_stations_list_idx__ > 0) && (m_stations_list_idx__ > idx) );
    size_t ret_idx = ret_success ? idx : 0;
    if (!ret_success) {
        TLVF_LOG(ERROR) << "Requested index is greater than the number of available entries";
    }
    return std::forward_as_tuple(ret_success, m_stations_list[ret_idx]);
}

bool cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST::alloc_stations_list(size_t count) {
    if (m_lock_order_counter__ > 0) {;
        TLVF_LOG(ERROR) << "Out of order allocation for variable length list stations_list, abort!";
        return false;
    }
    size_t len = sizeof(sUnassociatedStationInfo) * count;
    if(getBuffRemainingBytes() < len )  {
        TLVF_LOG(ERROR) << "Not enough available space on buffer - can't allocate";
        return false;
    }
    m_lock_order_counter__ = 0;
    uint8_t *src = (uint8_t *)&m_stations_list[*m_stations_list_length];
    uint8_t *dst = src + len;
    if (!m_parse__) {
        size_t move_length = getBuffRemainingBytes(src) - len;
        std::copy_n(src, move_length, dst);
    }
    m_stations_list_idx__ += count;
    *m_stations_list_length += count;
    if (!buffPtrIncrementSafe(len)) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << len << ") Failed!";
        return false;
    }
    if(m_length){ (*m_length) += len; }
    if (!m_parse__) { 
        for (size_t i = m_stations_list_idx__ - count; i < m_stations_list_idx__; i++) { m_stations_list[i].struct_init(); }
    }
    return true;
}

void cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    tlvf_swap(16, reinterpret_cast<uint8_t*>(m_length));
    for (size_t i = 0; i < m_stations_list_idx__; i++){
        m_stations_list[i].struct_swap();
    }
}

bool cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST::finalize()
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

size_t cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(uint16_t); // length
    class_size += sizeof(uint8_t); // stations_list_length
    return class_size;
}

bool cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_REQUEST::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_length = reinterpret_cast<uint16_t*>(m_buff_ptr__);
    if (!m_parse__) *m_length = 0;
    if (!buffPtrIncrementSafe(sizeof(uint16_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint16_t) << ") Failed!";
        return false;
    }
    m_stations_list_length = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!m_parse__) *m_stations_list_length = 0;
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    if(m_length && !m_parse__){ (*m_length) += sizeof(uint8_t); }
    m_stations_list = reinterpret_cast<sUnassociatedStationInfo*>(m_buff_ptr__);
    uint8_t stations_list_length = *m_stations_list_length;
    m_stations_list_idx__ = stations_list_length;
    if (!buffPtrIncrementSafe(sizeof(sUnassociatedStationInfo) * (stations_list_length))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sUnassociatedStationInfo) * (stations_list_length) << ") Failed!";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE::cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE::cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE::~cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE() {
}
const uint16_t& cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE::length() {
    return (const uint16_t&)(*m_length);
}

uint8_t& cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE::stations_list_length() {
    return (uint8_t&)(*m_stations_list_length);
}

std::tuple<bool, sUnassociatedStationStats&> cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE::stations_list(size_t idx) {
    bool ret_success = ( (m_stations_list_idx__ > 0) && (m_stations_list_idx__ > idx) );
    size_t ret_idx = ret_success ? idx : 0;
    if (!ret_success) {
        TLVF_LOG(ERROR) << "Requested index is greater than the number of available entries";
    }
    return std::forward_as_tuple(ret_success, m_stations_list[ret_idx]);
}

bool cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE::alloc_stations_list(size_t count) {
    if (m_lock_order_counter__ > 0) {;
        TLVF_LOG(ERROR) << "Out of order allocation for variable length list stations_list, abort!";
        return false;
    }
    size_t len = sizeof(sUnassociatedStationStats) * count;
    if(getBuffRemainingBytes() < len )  {
        TLVF_LOG(ERROR) << "Not enough available space on buffer - can't allocate";
        return false;
    }
    m_lock_order_counter__ = 0;
    uint8_t *src = (uint8_t *)&m_stations_list[*m_stations_list_length];
    uint8_t *dst = src + len;
    if (!m_parse__) {
        size_t move_length = getBuffRemainingBytes(src) - len;
        std::copy_n(src, move_length, dst);
    }
    m_stations_list_idx__ += count;
    *m_stations_list_length += count;
    if (!buffPtrIncrementSafe(len)) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << len << ") Failed!";
        return false;
    }
    if(m_length){ (*m_length) += len; }
    if (!m_parse__) { 
        for (size_t i = m_stations_list_idx__ - count; i < m_stations_list_idx__; i++) { m_stations_list[i].struct_init(); }
    }
    return true;
}

void cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    tlvf_swap(16, reinterpret_cast<uint8_t*>(m_length));
    for (size_t i = 0; i < m_stations_list_idx__; i++){
        m_stations_list[i].struct_swap();
    }
}

bool cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE::finalize()
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

size_t cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(uint16_t); // length
    class_size += sizeof(uint8_t); // stations_list_length
    return class_size;
}

bool cACTION_MONITOR_CLIENT_UNASSOCIATED_STA_LINK_METRIC_RESPONSE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_length = reinterpret_cast<uint16_t*>(m_buff_ptr__);
    if (!m_parse__) *m_length = 0;
    if (!buffPtrIncrementSafe(sizeof(uint16_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint16_t) << ") Failed!";
        return false;
    }
    m_stations_list_length = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!m_parse__) *m_stations_list_length = 0;
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    if(m_length && !m_parse__){ (*m_length) += sizeof(uint8_t); }
    m_stations_list = reinterpret_cast<sUnassociatedStationStats*>(m_buff_ptr__);
    uint8_t stations_list_length = *m_stations_list_length;
    m_stations_list_idx__ = stations_list_length;
    if (!buffPtrIncrementSafe(sizeof(sUnassociatedStationStats) * (stations_list_length))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sUnassociatedStationStats) * (stations_list_length) << ") Failed!";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_REQUEST::cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_REQUEST(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_REQUEST::cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_REQUEST(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_REQUEST::~cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_REQUEST() {
}
uint8_t& cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_REQUEST::sync() {
    return (uint8_t&)(*m_sync);
}

void cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_REQUEST::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
}

bool cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_REQUEST::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_REQUEST::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(uint8_t); // sync
    return class_size;
}

bool cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_REQUEST::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_sync = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE::cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE::cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE::~cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE() {
}
uint8_t& cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE::ap_stats_size() {
    return (uint8_t&)(*m_ap_stats_size);
}

std::tuple<bool, sApStatsParams&> cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE::ap_stats(size_t idx) {
    bool ret_success = ( (m_ap_stats_idx__ > 0) && (m_ap_stats_idx__ > idx) );
    size_t ret_idx = ret_success ? idx : 0;
    if (!ret_success) {
        TLVF_LOG(ERROR) << "Requested index is greater than the number of available entries";
    }
    return std::forward_as_tuple(ret_success, m_ap_stats[ret_idx]);
}

bool cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE::alloc_ap_stats(size_t count) {
    if (m_lock_order_counter__ > 0) {;
        TLVF_LOG(ERROR) << "Out of order allocation for variable length list ap_stats, abort!";
        return false;
    }
    size_t len = sizeof(sApStatsParams) * count;
    if(getBuffRemainingBytes() < len )  {
        TLVF_LOG(ERROR) << "Not enough available space on buffer - can't allocate";
        return false;
    }
    m_lock_order_counter__ = 0;
    uint8_t *src = (uint8_t *)&m_ap_stats[*m_ap_stats_size];
    uint8_t *dst = src + len;
    if (!m_parse__) {
        size_t move_length = getBuffRemainingBytes(src) - len;
        std::copy_n(src, move_length, dst);
    }
    m_sta_stats_size = (uint8_t *)((uint8_t *)(m_sta_stats_size) + len);
    m_sta_stats = (sStaStatsParams *)((uint8_t *)(m_sta_stats) + len);
    m_ap_stats_idx__ += count;
    *m_ap_stats_size += count;
    if (!buffPtrIncrementSafe(len)) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << len << ") Failed!";
        return false;
    }
    if (!m_parse__) { 
        for (size_t i = m_ap_stats_idx__ - count; i < m_ap_stats_idx__; i++) { m_ap_stats[i].struct_init(); }
    }
    return true;
}

uint8_t& cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE::sta_stats_size() {
    return (uint8_t&)(*m_sta_stats_size);
}

std::tuple<bool, sStaStatsParams&> cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE::sta_stats(size_t idx) {
    bool ret_success = ( (m_sta_stats_idx__ > 0) && (m_sta_stats_idx__ > idx) );
    size_t ret_idx = ret_success ? idx : 0;
    if (!ret_success) {
        TLVF_LOG(ERROR) << "Requested index is greater than the number of available entries";
    }
    return std::forward_as_tuple(ret_success, m_sta_stats[ret_idx]);
}

bool cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE::alloc_sta_stats(size_t count) {
    if (m_lock_order_counter__ > 1) {;
        TLVF_LOG(ERROR) << "Out of order allocation for variable length list sta_stats, abort!";
        return false;
    }
    size_t len = sizeof(sStaStatsParams) * count;
    if(getBuffRemainingBytes() < len )  {
        TLVF_LOG(ERROR) << "Not enough available space on buffer - can't allocate";
        return false;
    }
    m_lock_order_counter__ = 1;
    uint8_t *src = (uint8_t *)&m_sta_stats[*m_sta_stats_size];
    uint8_t *dst = src + len;
    if (!m_parse__) {
        size_t move_length = getBuffRemainingBytes(src) - len;
        std::copy_n(src, move_length, dst);
    }
    m_sta_stats_idx__ += count;
    *m_sta_stats_size += count;
    if (!buffPtrIncrementSafe(len)) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << len << ") Failed!";
        return false;
    }
    if (!m_parse__) { 
        for (size_t i = m_sta_stats_idx__ - count; i < m_sta_stats_idx__; i++) { m_sta_stats[i].struct_init(); }
    }
    return true;
}

void cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    for (size_t i = 0; i < m_ap_stats_idx__; i++){
        m_ap_stats[i].struct_swap();
    }
    for (size_t i = 0; i < m_sta_stats_idx__; i++){
        m_sta_stats[i].struct_swap();
    }
}

bool cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(uint8_t); // ap_stats_size
    class_size += sizeof(uint8_t); // sta_stats_size
    return class_size;
}

bool cACTION_MONITOR_HOSTAP_STATS_MEASUREMENT_RESPONSE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_ap_stats_size = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!m_parse__) *m_ap_stats_size = 0;
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    m_ap_stats = reinterpret_cast<sApStatsParams*>(m_buff_ptr__);
    uint8_t ap_stats_size = *m_ap_stats_size;
    m_ap_stats_idx__ = ap_stats_size;
    if (!buffPtrIncrementSafe(sizeof(sApStatsParams) * (ap_stats_size))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sApStatsParams) * (ap_stats_size) << ") Failed!";
        return false;
    }
    m_sta_stats_size = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!m_parse__) *m_sta_stats_size = 0;
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    m_sta_stats = reinterpret_cast<sStaStatsParams*>(m_buff_ptr__);
    uint8_t sta_stats_size = *m_sta_stats_size;
    m_sta_stats_idx__ = sta_stats_size;
    if (!buffPtrIncrementSafe(sizeof(sStaStatsParams) * (sta_stats_size))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sStaStatsParams) * (sta_stats_size) << ") Failed!";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_HOSTAP_LOAD_MEASUREMENT_NOTIFICATION::cACTION_MONITOR_HOSTAP_LOAD_MEASUREMENT_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_HOSTAP_LOAD_MEASUREMENT_NOTIFICATION::cACTION_MONITOR_HOSTAP_LOAD_MEASUREMENT_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_HOSTAP_LOAD_MEASUREMENT_NOTIFICATION::~cACTION_MONITOR_HOSTAP_LOAD_MEASUREMENT_NOTIFICATION() {
}
sApLoadNotificationParams& cACTION_MONITOR_HOSTAP_LOAD_MEASUREMENT_NOTIFICATION::params() {
    return (sApLoadNotificationParams&)(*m_params);
}

void cACTION_MONITOR_HOSTAP_LOAD_MEASUREMENT_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_HOSTAP_LOAD_MEASUREMENT_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_HOSTAP_LOAD_MEASUREMENT_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sApLoadNotificationParams); // params
    return class_size;
}

bool cACTION_MONITOR_HOSTAP_LOAD_MEASUREMENT_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sApLoadNotificationParams*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sApLoadNotificationParams))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sApLoadNotificationParams) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_BEACON_11K_REQUEST::cACTION_MONITOR_CLIENT_BEACON_11K_REQUEST(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_BEACON_11K_REQUEST::cACTION_MONITOR_CLIENT_BEACON_11K_REQUEST(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_BEACON_11K_REQUEST::~cACTION_MONITOR_CLIENT_BEACON_11K_REQUEST() {
}
sBeaconRequest11k& cACTION_MONITOR_CLIENT_BEACON_11K_REQUEST::params() {
    return (sBeaconRequest11k&)(*m_params);
}

void cACTION_MONITOR_CLIENT_BEACON_11K_REQUEST::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_CLIENT_BEACON_11K_REQUEST::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_BEACON_11K_REQUEST::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sBeaconRequest11k); // params
    return class_size;
}

bool cACTION_MONITOR_CLIENT_BEACON_11K_REQUEST::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sBeaconRequest11k*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sBeaconRequest11k))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sBeaconRequest11k) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_BEACON_11K_RESPONSE::cACTION_MONITOR_CLIENT_BEACON_11K_RESPONSE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_BEACON_11K_RESPONSE::cACTION_MONITOR_CLIENT_BEACON_11K_RESPONSE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_BEACON_11K_RESPONSE::~cACTION_MONITOR_CLIENT_BEACON_11K_RESPONSE() {
}
sBeaconResponse11k& cACTION_MONITOR_CLIENT_BEACON_11K_RESPONSE::params() {
    return (sBeaconResponse11k&)(*m_params);
}

void cACTION_MONITOR_CLIENT_BEACON_11K_RESPONSE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_CLIENT_BEACON_11K_RESPONSE::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_BEACON_11K_RESPONSE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sBeaconResponse11k); // params
    return class_size;
}

bool cACTION_MONITOR_CLIENT_BEACON_11K_RESPONSE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sBeaconResponse11k*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sBeaconResponse11k))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sBeaconResponse11k) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_REQUEST::cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_REQUEST(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_REQUEST::cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_REQUEST(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_REQUEST::~cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_REQUEST() {
}
sStaChannelLoadRequest11k& cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_REQUEST::params() {
    return (sStaChannelLoadRequest11k&)(*m_params);
}

void cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_REQUEST::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_REQUEST::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_REQUEST::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sStaChannelLoadRequest11k); // params
    return class_size;
}

bool cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_REQUEST::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sStaChannelLoadRequest11k*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sStaChannelLoadRequest11k))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sStaChannelLoadRequest11k) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_RESPONSE::cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_RESPONSE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_RESPONSE::cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_RESPONSE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_RESPONSE::~cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_RESPONSE() {
}
sStaChannelLoadResponse11k& cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_RESPONSE::params() {
    return (sStaChannelLoadResponse11k&)(*m_params);
}

void cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_RESPONSE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_RESPONSE::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_RESPONSE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sStaChannelLoadResponse11k); // params
    return class_size;
}

bool cACTION_MONITOR_CLIENT_CHANNEL_LOAD_11K_RESPONSE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sStaChannelLoadResponse11k*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sStaChannelLoadResponse11k))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sStaChannelLoadResponse11k) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CLIENT_NEW_IP_ADDRESS_NOTIFICATION::cACTION_MONITOR_CLIENT_NEW_IP_ADDRESS_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_NEW_IP_ADDRESS_NOTIFICATION::cACTION_MONITOR_CLIENT_NEW_IP_ADDRESS_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CLIENT_NEW_IP_ADDRESS_NOTIFICATION::~cACTION_MONITOR_CLIENT_NEW_IP_ADDRESS_NOTIFICATION() {
}
sMacAddr& cACTION_MONITOR_CLIENT_NEW_IP_ADDRESS_NOTIFICATION::mac() {
    return (sMacAddr&)(*m_mac);
}

beerocks::net::sIpv4Addr& cACTION_MONITOR_CLIENT_NEW_IP_ADDRESS_NOTIFICATION::ipv4() {
    return (beerocks::net::sIpv4Addr&)(*m_ipv4);
}

void cACTION_MONITOR_CLIENT_NEW_IP_ADDRESS_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_mac->struct_swap();
    m_ipv4->struct_swap();
}

bool cACTION_MONITOR_CLIENT_NEW_IP_ADDRESS_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CLIENT_NEW_IP_ADDRESS_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sMacAddr); // mac
    class_size += sizeof(beerocks::net::sIpv4Addr); // ipv4
    return class_size;
}

bool cACTION_MONITOR_CLIENT_NEW_IP_ADDRESS_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_mac = reinterpret_cast<sMacAddr*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sMacAddr))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sMacAddr) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_mac->struct_init(); }
    m_ipv4 = reinterpret_cast<beerocks::net::sIpv4Addr*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(beerocks::net::sIpv4Addr))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(beerocks::net::sIpv4Addr) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_ipv4->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_REQUEST::cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_REQUEST(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_REQUEST::cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_REQUEST(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_REQUEST::~cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_REQUEST() {
}
sSteeringSetGroupRequest& cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_REQUEST::params() {
    return (sSteeringSetGroupRequest&)(*m_params);
}

void cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_REQUEST::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_REQUEST::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_REQUEST::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sSteeringSetGroupRequest); // params
    return class_size;
}

bool cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_REQUEST::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sSteeringSetGroupRequest*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sSteeringSetGroupRequest))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sSteeringSetGroupRequest) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_RESPONSE::cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_RESPONSE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_RESPONSE::cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_RESPONSE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_RESPONSE::~cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_RESPONSE() {
}
sSteeringSetGroupResponse& cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_RESPONSE::params() {
    return (sSteeringSetGroupResponse&)(*m_params);
}

void cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_RESPONSE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_RESPONSE::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_RESPONSE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sSteeringSetGroupResponse); // params
    return class_size;
}

bool cACTION_MONITOR_STEERING_CLIENT_SET_GROUP_RESPONSE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sSteeringSetGroupResponse*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sSteeringSetGroupResponse))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sSteeringSetGroupResponse) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_STEERING_CLIENT_SET_REQUEST::cACTION_MONITOR_STEERING_CLIENT_SET_REQUEST(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_STEERING_CLIENT_SET_REQUEST::cACTION_MONITOR_STEERING_CLIENT_SET_REQUEST(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_STEERING_CLIENT_SET_REQUEST::~cACTION_MONITOR_STEERING_CLIENT_SET_REQUEST() {
}
sSteeringClientSetRequest& cACTION_MONITOR_STEERING_CLIENT_SET_REQUEST::params() {
    return (sSteeringClientSetRequest&)(*m_params);
}

void cACTION_MONITOR_STEERING_CLIENT_SET_REQUEST::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_STEERING_CLIENT_SET_REQUEST::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_STEERING_CLIENT_SET_REQUEST::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sSteeringClientSetRequest); // params
    return class_size;
}

bool cACTION_MONITOR_STEERING_CLIENT_SET_REQUEST::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sSteeringClientSetRequest*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sSteeringClientSetRequest))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sSteeringClientSetRequest) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_STEERING_CLIENT_SET_RESPONSE::cACTION_MONITOR_STEERING_CLIENT_SET_RESPONSE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_STEERING_CLIENT_SET_RESPONSE::cACTION_MONITOR_STEERING_CLIENT_SET_RESPONSE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_STEERING_CLIENT_SET_RESPONSE::~cACTION_MONITOR_STEERING_CLIENT_SET_RESPONSE() {
}
sSteeringClientSetResponse& cACTION_MONITOR_STEERING_CLIENT_SET_RESPONSE::params() {
    return (sSteeringClientSetResponse&)(*m_params);
}

void cACTION_MONITOR_STEERING_CLIENT_SET_RESPONSE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_STEERING_CLIENT_SET_RESPONSE::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_STEERING_CLIENT_SET_RESPONSE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sSteeringClientSetResponse); // params
    return class_size;
}

bool cACTION_MONITOR_STEERING_CLIENT_SET_RESPONSE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sSteeringClientSetResponse*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sSteeringClientSetResponse))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sSteeringClientSetResponse) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_STEERING_EVENT_CLIENT_ACTIVITY_NOTIFICATION::cACTION_MONITOR_STEERING_EVENT_CLIENT_ACTIVITY_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_STEERING_EVENT_CLIENT_ACTIVITY_NOTIFICATION::cACTION_MONITOR_STEERING_EVENT_CLIENT_ACTIVITY_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_STEERING_EVENT_CLIENT_ACTIVITY_NOTIFICATION::~cACTION_MONITOR_STEERING_EVENT_CLIENT_ACTIVITY_NOTIFICATION() {
}
sSteeringEvActivity& cACTION_MONITOR_STEERING_EVENT_CLIENT_ACTIVITY_NOTIFICATION::params() {
    return (sSteeringEvActivity&)(*m_params);
}

void cACTION_MONITOR_STEERING_EVENT_CLIENT_ACTIVITY_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_STEERING_EVENT_CLIENT_ACTIVITY_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_STEERING_EVENT_CLIENT_ACTIVITY_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sSteeringEvActivity); // params
    return class_size;
}

bool cACTION_MONITOR_STEERING_EVENT_CLIENT_ACTIVITY_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sSteeringEvActivity*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sSteeringEvActivity))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sSteeringEvActivity) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_STEERING_EVENT_SNR_XING_NOTIFICATION::cACTION_MONITOR_STEERING_EVENT_SNR_XING_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_STEERING_EVENT_SNR_XING_NOTIFICATION::cACTION_MONITOR_STEERING_EVENT_SNR_XING_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_STEERING_EVENT_SNR_XING_NOTIFICATION::~cACTION_MONITOR_STEERING_EVENT_SNR_XING_NOTIFICATION() {
}
sSteeringEvSnrXing& cACTION_MONITOR_STEERING_EVENT_SNR_XING_NOTIFICATION::params() {
    return (sSteeringEvSnrXing&)(*m_params);
}

void cACTION_MONITOR_STEERING_EVENT_SNR_XING_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_params->struct_swap();
}

bool cACTION_MONITOR_STEERING_EVENT_SNR_XING_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_STEERING_EVENT_SNR_XING_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sSteeringEvSnrXing); // params
    return class_size;
}

bool cACTION_MONITOR_STEERING_EVENT_SNR_XING_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_params = reinterpret_cast<sSteeringEvSnrXing*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sSteeringEvSnrXing))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sSteeringEvSnrXing) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_REQUEST::cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_REQUEST(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_REQUEST::cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_REQUEST(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_REQUEST::~cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_REQUEST() {
}
uint8_t& cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_REQUEST::cert_mode() {
    return (uint8_t&)(*m_cert_mode);
}

sTriggerChannelScanParams& cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_REQUEST::scan_params() {
    return (sTriggerChannelScanParams&)(*m_scan_params);
}

void cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_REQUEST::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_scan_params->struct_swap();
}

bool cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_REQUEST::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_REQUEST::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(uint8_t); // cert_mode
    class_size += sizeof(sTriggerChannelScanParams); // scan_params
    return class_size;
}

bool cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_REQUEST::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_cert_mode = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    m_scan_params = reinterpret_cast<sTriggerChannelScanParams*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sTriggerChannelScanParams))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sTriggerChannelScanParams) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_scan_params->struct_init(); }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_RESPONSE::cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_RESPONSE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_RESPONSE::cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_RESPONSE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_RESPONSE::~cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_RESPONSE() {
}
uint8_t& cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_RESPONSE::success() {
    return (uint8_t&)(*m_success);
}

void cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_RESPONSE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
}

bool cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_RESPONSE::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_RESPONSE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(uint8_t); // success
    return class_size;
}

bool cACTION_MONITOR_CHANNEL_SCAN_TRIGGER_SCAN_RESPONSE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_success = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_REQUEST::cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_REQUEST(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_REQUEST::cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_REQUEST(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_REQUEST::~cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_REQUEST() {
}
void cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_REQUEST::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
}

bool cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_REQUEST::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_REQUEST::get_initial_size()
{
    size_t class_size = 0;
    return class_size;
}

bool cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_REQUEST::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_RESPONSE::cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_RESPONSE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_RESPONSE::cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_RESPONSE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_RESPONSE::~cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_RESPONSE() {
}
uint8_t& cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_RESPONSE::success() {
    return (uint8_t&)(*m_success);
}

void cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_RESPONSE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
}

bool cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_RESPONSE::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_RESPONSE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(uint8_t); // success
    return class_size;
}

bool cACTION_MONITOR_CHANNEL_SCAN_DUMP_RESULTS_RESPONSE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_success = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CHANNEL_SCAN_TRIGGERED_NOTIFICATION::cACTION_MONITOR_CHANNEL_SCAN_TRIGGERED_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_TRIGGERED_NOTIFICATION::cACTION_MONITOR_CHANNEL_SCAN_TRIGGERED_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_TRIGGERED_NOTIFICATION::~cACTION_MONITOR_CHANNEL_SCAN_TRIGGERED_NOTIFICATION() {
}
void cACTION_MONITOR_CHANNEL_SCAN_TRIGGERED_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
}

bool cACTION_MONITOR_CHANNEL_SCAN_TRIGGERED_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CHANNEL_SCAN_TRIGGERED_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    return class_size;
}

bool cACTION_MONITOR_CHANNEL_SCAN_TRIGGERED_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CHANNEL_SCAN_RESULTS_NOTIFICATION::cACTION_MONITOR_CHANNEL_SCAN_RESULTS_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_RESULTS_NOTIFICATION::cACTION_MONITOR_CHANNEL_SCAN_RESULTS_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_RESULTS_NOTIFICATION::~cACTION_MONITOR_CHANNEL_SCAN_RESULTS_NOTIFICATION() {
}
sChannelScanResults& cACTION_MONITOR_CHANNEL_SCAN_RESULTS_NOTIFICATION::scan_results() {
    return (sChannelScanResults&)(*m_scan_results);
}

uint8_t& cACTION_MONITOR_CHANNEL_SCAN_RESULTS_NOTIFICATION::is_dump() {
    return (uint8_t&)(*m_is_dump);
}

void cACTION_MONITOR_CHANNEL_SCAN_RESULTS_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
    m_scan_results->struct_swap();
}

bool cACTION_MONITOR_CHANNEL_SCAN_RESULTS_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CHANNEL_SCAN_RESULTS_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sChannelScanResults); // scan_results
    class_size += sizeof(uint8_t); // is_dump
    return class_size;
}

bool cACTION_MONITOR_CHANNEL_SCAN_RESULTS_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_scan_results = reinterpret_cast<sChannelScanResults*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(sChannelScanResults))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(sChannelScanResults) << ") Failed!";
        return false;
    }
    if (!m_parse__) { m_scan_results->struct_init(); }
    m_is_dump = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!m_parse__) *m_is_dump = 0x0;
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CHANNEL_SCAN_ABORT_REQUEST::cACTION_MONITOR_CHANNEL_SCAN_ABORT_REQUEST(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_ABORT_REQUEST::cACTION_MONITOR_CHANNEL_SCAN_ABORT_REQUEST(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_ABORT_REQUEST::~cACTION_MONITOR_CHANNEL_SCAN_ABORT_REQUEST() {
}
void cACTION_MONITOR_CHANNEL_SCAN_ABORT_REQUEST::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
}

bool cACTION_MONITOR_CHANNEL_SCAN_ABORT_REQUEST::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CHANNEL_SCAN_ABORT_REQUEST::get_initial_size()
{
    size_t class_size = 0;
    return class_size;
}

bool cACTION_MONITOR_CHANNEL_SCAN_ABORT_REQUEST::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CHANNEL_SCAN_ABORT_RESPONSE::cACTION_MONITOR_CHANNEL_SCAN_ABORT_RESPONSE(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_ABORT_RESPONSE::cACTION_MONITOR_CHANNEL_SCAN_ABORT_RESPONSE(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_ABORT_RESPONSE::~cACTION_MONITOR_CHANNEL_SCAN_ABORT_RESPONSE() {
}
uint8_t& cACTION_MONITOR_CHANNEL_SCAN_ABORT_RESPONSE::success() {
    return (uint8_t&)(*m_success);
}

void cACTION_MONITOR_CHANNEL_SCAN_ABORT_RESPONSE::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
}

bool cACTION_MONITOR_CHANNEL_SCAN_ABORT_RESPONSE::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CHANNEL_SCAN_ABORT_RESPONSE::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(uint8_t); // success
    return class_size;
}

bool cACTION_MONITOR_CHANNEL_SCAN_ABORT_RESPONSE::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_success = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CHANNEL_SCAN_ABORTED_NOTIFICATION::cACTION_MONITOR_CHANNEL_SCAN_ABORTED_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_ABORTED_NOTIFICATION::cACTION_MONITOR_CHANNEL_SCAN_ABORTED_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_ABORTED_NOTIFICATION::~cACTION_MONITOR_CHANNEL_SCAN_ABORTED_NOTIFICATION() {
}
uint8_t& cACTION_MONITOR_CHANNEL_SCAN_ABORTED_NOTIFICATION::reason() {
    return (uint8_t&)(*m_reason);
}

void cACTION_MONITOR_CHANNEL_SCAN_ABORTED_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
}

bool cACTION_MONITOR_CHANNEL_SCAN_ABORTED_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CHANNEL_SCAN_ABORTED_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(uint8_t); // reason
    return class_size;
}

bool cACTION_MONITOR_CHANNEL_SCAN_ABORTED_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_reason = reinterpret_cast<uint8_t*>(m_buff_ptr__);
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) {
        LOG(ERROR) << "buffPtrIncrementSafe(" << std::dec << sizeof(uint8_t) << ") Failed!";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}

cACTION_MONITOR_CHANNEL_SCAN_FINISHED_NOTIFICATION::cACTION_MONITOR_CHANNEL_SCAN_FINISHED_NOTIFICATION(uint8_t* buff, size_t buff_len, bool parse) :
    BaseClass(buff, buff_len, parse) {
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_FINISHED_NOTIFICATION::cACTION_MONITOR_CHANNEL_SCAN_FINISHED_NOTIFICATION(std::shared_ptr<BaseClass> base, bool parse) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse){
    m_init_succeeded = init();
}
cACTION_MONITOR_CHANNEL_SCAN_FINISHED_NOTIFICATION::~cACTION_MONITOR_CHANNEL_SCAN_FINISHED_NOTIFICATION() {
}
void cACTION_MONITOR_CHANNEL_SCAN_FINISHED_NOTIFICATION::class_swap()
{
    tlvf_swap(8*sizeof(eActionOp_MONITOR), reinterpret_cast<uint8_t*>(m_action_op));
}

bool cACTION_MONITOR_CHANNEL_SCAN_FINISHED_NOTIFICATION::finalize()
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
    }
    class_swap();
    m_finalized__ = true;
    return true;
}

size_t cACTION_MONITOR_CHANNEL_SCAN_FINISHED_NOTIFICATION::get_initial_size()
{
    size_t class_size = 0;
    return class_size;
}

bool cACTION_MONITOR_CHANNEL_SCAN_FINISHED_NOTIFICATION::init()
{
    if (getBuffRemainingBytes() < get_initial_size()) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    if (m_parse__) { class_swap(); }
    return true;
}


