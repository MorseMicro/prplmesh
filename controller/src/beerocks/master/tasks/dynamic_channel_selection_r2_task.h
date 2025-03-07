/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2019-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

// This task will eventually replace the existing DCS task, but
// in order not to break existing functionality, it is introduced
// as a new separate task.

#ifndef _DYNAMIC_CHANNEL_SELECTION_R2_TASK_H_
#define _DYNAMIC_CHANNEL_SELECTION_R2_TASK_H_

#include "../db/db.h"
#include "task.h"
#include "task_pool.h"

#include <beerocks/tlvf/beerocks_message.h>
#include <chrono>
#include <tlvf/wfa_map/tlvChannelPreference.h>
#include <tlvf/wfa_map/tlvChannelSelectionResponse.h>
#include <tlvf/wfa_map/tlvProfile2CacCompletionReport.h>
#include <tlvf/wfa_map/tlvProfile2CacStatusReport.h>
#include <tlvf/wfa_map/tlvProfile2ChannelScanRequest.h>
#include <tlvf/wfa_map/tlvRadioOperationRestriction.h>

constexpr uint8_t INTERVAL_TIME_BETWEEN_RETRIES_ON_FAILURE_SEC = 120;
// According to the Multi-AP specification the timeout is 1 second
constexpr std::chrono::seconds CHANNEL_PREFERENCE_TIMEOUT(1);
constexpr std::chrono::seconds CHANNEL_SELECTION_TIMEOUT(1);

namespace son {

class dynamic_channel_selection_r2_task : public task, public std::enable_shared_from_this<task> {
public:
    dynamic_channel_selection_r2_task(db &database, ieee1905_1::CmduMessageTx &cmdu_tx_,
                                      task_pool &tasks_);
    bool handle_ieee1905_1_msg(const sMacAddr &src_mac,
                               ieee1905_1::CmduMessageRx &cmdu_rx) override;

    struct sOnDemandChannelSelectionEvent {
        sMacAddr radio_mac;
        uint8_t channel;
        uint8_t operating_class;
        uint8_t csa_count;
    };

    struct sPreferenceRequestEvent {
        sMacAddr radio_mac;
    };

    struct sSingleScanRequestEvent {
        sMacAddr radio_mac;
    };

    struct sContinuousScanRequestStateChangeEvent {
        sMacAddr radio_mac;
        bool enable;
    };

    struct sScanReportEvent {
        sMacAddr agent_mac;
        std::string ISO_8601_timestamp;
    };

    enum eEvent : uint8_t {
        TRIGGER_ON_DEMAND_CHANNEL_SELECTION,
        REQUEST_NEW_PREFERENCE,
        TRIGGER_SINGLE_SCAN,
        RECEIVED_CHANNEL_SCAN_REPORT,
        CONTINUOUS_STATE_CHANGED_PER_RADIO
    };

    enum class eRadioScanStatus : uint8_t { PENDING, TRIGGERED_WAIT_FOR_ACK, SCAN_IN_PROGRESS };

    enum class eAgentStatus : uint8_t { IDLE, BUSY };

    // Struct of the status of an agent and it's scan requests
    struct sAgentScanStatus {

        // Struct of a radio scan request
        struct sRadioScanRequest {
            uint16_t mid                                         = INVALID_MID_ID;
            eRadioScanStatus status                              = eRadioScanStatus::PENDING;
            std::chrono::system_clock::time_point next_time_scan = {};
            bool is_single_scan                                  = true;
            std::set<node::radio::channel_scan_report::channel_scan_report_key> scan_report_index;
        };

        /**
         * @brief Map of radio scans
         * 
         * Key:     radio mac.
         * Value:   radio scan request as sRadioScanRequest struct.
         */
        using RadioScanMap = std::unordered_map<sMacAddr, sRadioScanRequest>;
        /**
         * @brief Pair of continuous radio scans Map
         * 
         * Key:     radio mac.
         * Value:   radio scan request as sRadioScanRequest struct.
         */
        using RadioScanPair = std::pair<sMacAddr, sRadioScanRequest>;

        eAgentStatus status;

        RadioScanMap single_radio_scans;
        RadioScanMap continuous_radio_scans;

        std::chrono::system_clock::time_point timeout;

        /**
         * @brief Check the if the scan passed its interval duration
         * @param request The radio's request
         * 
         * @return true if scan is on time, false otherwise.
         */
        static bool is_continuous_scan_interval_passed(const sRadioScanRequest &request)
        {
            if (std::chrono::system_clock::now() >= request.next_time_scan) {
                return true;
            }

            return false;
        }
    };

protected:
    virtual void work() override;
    virtual void handle_event(int event_enum_value, void *event_obj) override;

private:
    enum class eScanState : uint8_t { IDLE, TRIGGER_SCAN };
    enum class eSelectionState : uint8_t {
        IDLE,
        WAIT_FOR_SCAN,
        WAIT_FOR_PREFERENCE,
        WAIT_FOR_SELECTION_RESPONSE,
        SELECTION_ABORTED
    };

    // clang-format off
    const std::unordered_map<eScanState, std::string> m_scan_states_string = {
      { eScanState::IDLE,           "IDLE"          },
      { eScanState::TRIGGER_SCAN,   "TRIGGER_SCAN"  },
    };
    const std::unordered_map<eSelectionState, std::string> m_selection_states_string = {
      { eSelectionState::IDLE,                          "IDLE"                          },
      { eSelectionState::WAIT_FOR_SCAN,                 "WAIT_FOR_SCAN"                 },
      { eSelectionState::WAIT_FOR_PREFERENCE,           "WAIT_FOR_PREFERENCE"           },
      { eSelectionState::WAIT_FOR_SELECTION_RESPONSE,   "WAIT_FOR_SELECTION_RESPONSE"   },
      { eSelectionState::SELECTION_ABORTED,             "SELECTION_ABORTED"             },
    };
    // clang-format on

    struct sChannelSelectionRequest {
        explicit sChannelSelectionRequest(uint8_t csa_count_) : csa_count(csa_count_) {}
        virtual ~sChannelSelectionRequest() = default;

        uint8_t csa_count;
    };
    struct sOnDemandChannelSelectionRequest : public sChannelSelectionRequest {
        sOnDemandChannelSelectionRequest(uint8_t channel_number_, uint8_t primary_beacon_channel_,
                                         uint8_t operating_class_, uint8_t csa_count_)
            : sChannelSelectionRequest(csa_count_), channel_number(channel_number_),
              primary_beacon_channel(primary_beacon_channel_), operating_class(operating_class_)
        {
        }

        uint8_t channel_number;
        uint8_t primary_beacon_channel;
        uint8_t operating_class;
    };
    struct sOnDemandAutoChannelSelectionRequest : public sChannelSelectionRequest {
        sOnDemandAutoChannelSelectionRequest(const std::unordered_set<uint8_t> &channel_pool_,
                                             uint8_t csa_count_)
            : sChannelSelectionRequest(csa_count_), channel_pool(channel_pool_)
        {
        }

        std::unordered_set<uint8_t> channel_pool;
    };
    eScanState m_scan_state           = eScanState::IDLE;
    eSelectionState m_selection_state = eSelectionState::IDLE;

    // Class constants
    static constexpr uint16_t INVALID_MID_ID = UINT16_MAX;

    db &database;
    ieee1905_1::CmduMessageTx &cmdu_tx;
    task_pool &tasks;

    /**
     * @brief Map of agent's status.
     * 
     * Key:     agent mac.
     * Value:   agent scan status as sAgentScanStatus struct.
     */
    std::unordered_map<sMacAddr, sAgentScanStatus> m_agents_scan_status_map;

    typedef std::unordered_map<sMacAddr, std::shared_ptr<sChannelSelectionRequest>>
        AgentChannelSelectionRequest;
    std::unordered_map<sMacAddr, AgentChannelSelectionRequest> m_pending_selection_requests;
    std::chrono::steady_clock::time_point m_selection_timeout;

    /**
     * @brief Handle single scan request events.
     * Add a radio scan request in the event to pending scan requests.
     * 
     * @param scan_request_event Refernce to sSingleScanRequestEvent object.
     * @return true if successful, false otherwise.
     */
    bool handle_single_scan_request_event(const sSingleScanRequestEvent &scan_request_event);

    /**
     * @brief Handle continuous scan request events.
     * Add a radio scan request in the event to pending scan requests.
     * 
     * @param scan_request_event Refernce to sContinuousScanRequestStateChangeEvent object.
     * @return true if successful, false otherwise.
     */
    bool handle_continuous_scan_request_event(
        const sContinuousScanRequestStateChangeEvent &scan_request_event);

    /**
     * @brief Handle On-Demand Channel-Selection request events.
     * Send a Channel-Selection-Request 1905.1 message to the Agent.
     * 
     * @param channel_selection_event Reference to an sOnDemandChannelSelectionEvent object.
     * @return true if successful, false otherwise.
     */
    bool handle_on_demand_channel_selection_request_event(
        const sOnDemandChannelSelectionEvent &channel_selection_event);

    /**
     * @brief Handle Preference Query request event.
     * 
     * @param preference_request_event Reference to sPreferenceRequestEvent object.
     * @return true if successful, false otherwise.
     */
    bool handle_preference_request_event(const sPreferenceRequestEvent &preference_request_event);

    /**
     * @brief Send pending channel Selection requests
     * 
     * @return true if successful, false otherwise.
     */
    bool send_selection_requests();

    bool remove_invalid_channel_selection_requests();

    /**
     * @brief Send a Channel Preference Query message to a given agent.
     * aligned with the 1905.1 requirements, we need to send a Channel-Preference query to receive
     * a Channel Preference Report, which contains useful information for the Channel-Selection
     * feature.
     * 
     * @param agent_mac MAC address of the agent.
     * @return true if successful, false otherwise.
     */
    bool send_channel_preference_query(const sMacAddr &agent_mac);

    /**
     * @brief Check the scans queue for any pending requests in idle agents
     * 
     * @return true if pending scan in idle agent found, false otherwise.
     */
    bool is_scan_pending_for_any_idle_agent();

    /**
     * @brief Check if the agent has pending scans that can be triggered.
     * Will return true only if the agent is in IDLE state and therefore
     * ready to run the pending scan.
     * 
     * @param agent_scan_status A reference to sAgentScanStatus struct
     * @return true if pending scan in idle agent found, false otherwise.
     */
    bool is_agent_idle_with_pending_radio_scans(const sAgentScanStatus &agent_scan_status);

    /**
     * @brief Trigger pending scan requests for any idle agent.
     * 
     * @return true if successful, false otherwise.
     */
    bool trigger_pending_scan_requests();

    /**
     * @brief Check if a scan was triggered for a given radio
     * 
     * @param radio_mac MAC address of the radio 
     * @param is_single_scan boolean value that represents the type of the scan
     * @return true if scan is triggered, false otherwise.
     */
    bool is_scan_triggered_for_radio(const sMacAddr &radio_mac, bool is_single_scan);

    /**
     * @brief Handle scan request events.
     * Add a radio scan request in the event to pending scan requests.
     * 
     * @param scan_request_event Refernce to sScanRequestEvent object.
     * @return true if successful, false otherwise.
     */
    bool handle_scan_request_event();

    /**
     * @brief Handle scan report events
     * 
     * @param scan_report_event Refernce to sScanReportEvent object.
     * @return true if successful, false otherwise.
     */
    bool handle_scan_report_event(const sScanReportEvent &scan_report_event);

    /**
     * @brief Create a channel scan request message, with empty radio_list.
     * 
     * @param[in] agent_mac MAC address of the agent.
     * @param[out] mid The unique message-id of the message sent to the agent.
     * @param[out] channel_scan_request_tlv Shared pointer to the Channel_scan_request_tlv.
     * @return true if successful, false otherwise.
     */
    bool create_channel_scan_request_message(
        sMacAddr agent_mac, uint16_t &mid,
        std::shared_ptr<wfa_map::tlvProfile2ChannelScanRequest> &channel_scan_request_tlv);

    /**
     * @brief Send channel scan request message to agent
     * 
     * @param agent_mac MAC address of the agent.
     * @return true if successful, false otherwise.
     */
    bool send_scan_request_to_agent(const sMacAddr &agent_mac);

    /**
     * @brief Scan all agent for timeout and abort scans in progress
     * 
     * @return true if timeout found, false otherwise.
     */
    bool handle_timeout_in_busy_agents();

    /**
     * @brief Handle 1905.1 Channel Selection Response message
     * 
     * @param src_mac MAC address of the incoming message.
     * @param cmdu_rx Received CMDU message to handle.
     * @return true if handled correctly, false otherwise.
     */
    bool handle_cmdu_1905_channel_selection_response(const sMacAddr &src_mac,
                                                     ieee1905_1::CmduMessageRx &cmdu_rx);

    /**
     * @brief Handle 1905.1 Channel Preference Report message
     * This message contains an agent's Channel-Preference which is needed to accurately utilize
     * the Channel-Selection feature.
     * 
     * @param src_mac MAC address of the incoming message.
     * @param cmdu_rx Received CMDU message to handle.
     * @return true if handled correctly, false otherwise.
     */
    bool handle_cmdu_1905_channel_preference_report(const sMacAddr &src_mac,
                                                    ieee1905_1::CmduMessageRx &cmdu_rx);

    /**
     * @brief Handles Radio Operation Restriction TLV of Channel Preference Report
     * 
     * @param radio_operation_restriction_tlv Channel Preference TLV
     * @return True on success, false otherwise.
    */
    bool handle_tlv_radio_operation_restriction(
        const std::shared_ptr<wfa_map::tlvRadioOperationRestriction>
            &radio_operation_restriction_tlv);
    /**
     * @brief Handles Channel Preference TLV of Channel Preference Report
     * 
     * @param channel_preference_tlv Channel Preference TLV
     * @return True on success, false otherwise.
    */
    bool handle_tlv_channel_preference(
        const std::shared_ptr<wfa_map::tlvChannelPreference> &channel_preference_tlv);

    /**
     * @brief Handles Tlv of Profile-2 CAC Completion Report.
     *
     * @param cac_completion_report_tlv CAC completion report TLV
     * @return True on success, false otherwise.
    */
    bool handle_tlv_profile2_cac_completion_report(
        const std::shared_ptr<wfa_map::tlvProfile2CacCompletionReport> &cac_completion_report_tlv);

    /**
     * @brief Handles Tlv of Profile-2 CAC Status Report.
     *
     * @param agent agent db object
     * @param cac_status_report_tlv CAC status report TLV
     * @return True on success, false otherwise.
    */
    bool handle_tlv_profile2_cac_status_report(
        const std::shared_ptr<Agent> agent,
        const std::shared_ptr<wfa_map::tlvProfile2CacStatusReport> &cac_status_report_tlv);

    bool handle_timeout_in_selection_flow();
};

} //namespace son
#endif
