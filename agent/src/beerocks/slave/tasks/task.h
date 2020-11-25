/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef _TASK_H_
#define _TASK_H_

#include <beerocks/tlvf/beerocks_header.h>
#include <tlvf/CmduMessageRx.h>

#include <chrono>

namespace beerocks {

/**
* @brief Enum which defines all tasks type.
* 
* Each task must have an entry on the enum eType, so it will be possible to send the task an
* event. 
*/
enum eTaskType : uint8_t {
    TOPOLOGY,
    AP_AUTOCONFIGURATION,
    CHANNEL_SELECTION,
    CHANNEL_SCAN,
    CAPABILITY_REPORTING,
    LINK_METRICS_COLLECTION,
};

class Task {
public:
    Task() = delete;
    explicit Task(eTaskType task_type) : m_task_type(task_type) {}
    virtual ~Task() {}

    /**
     * @brief Retrun the task type.
     * 
     * Called by TaskPool send_event().
     * 
     * @return eType Task type.
     */
    virtual eTaskType get_task_type() { return m_task_type; }

    /**
     * @brief Work function. Shall do the task routine. Called by TaskPool run_task() function.
     */
    virtual void work(){};

    /**
     * @brief Handle events, which are being send from containing thread.
     * 
     * @param event_enum_value Event enum value which shall be defined on the task.
     * @param event_obj Pointer to some chunk of memory used to pass data to the event handler.
     */
    virtual void handle_event(uint8_t event_enum_value, const void *event_obj){};

    /**
     * @brief Handle CMDU message.
     * 
     * @param cmdu_rx CMDU object containing the received message to be handled.
     * @param iface_index Index of the network interface that the CMDU message was received on.
     * @param dst_mac Destination MAC address.
     * @param src_mac AL MAC address of the sender.
     * @param fd File descriptor of the socket connection with the slave that sent the message.
     * @param beerocks_header Beerocks Message header (Only on VS message).
     * @return true if the message has been handled, otherwise false.
     */
    virtual bool handle_cmdu(ieee1905_1::CmduMessageRx &cmdu_rx, uint32_t iface_index,
                             const sMacAddr &dst_mac, const sMacAddr &src_mac, int fd,
                             std::shared_ptr<beerocks_header> beerocks_header)
    {
        return false;
    }

    /**
     * @brief Task execution time setter method.
     * 
     * @param time A timepoint of the task's last execution.
     */
    void set_last_exec_time(std::chrono::steady_clock::time_point time) { m_last_exec_time = time; }

    /**
     * @brief Task execution time getter method.
     */
    std::chrono::steady_clock::time_point get_last_exec_time() { return m_last_exec_time; }

private:
    eTaskType m_task_type;
    std::chrono::steady_clock::time_point m_last_exec_time;
};

} // namespace beerocks

#endif // _TASK_H_
