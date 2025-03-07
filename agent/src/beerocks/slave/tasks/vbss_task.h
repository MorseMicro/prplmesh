#ifndef _VBSS_TASK_H_
#define _VBSS_TASK_H_

#include "task.h"
#include <bcl/network/sockets_impl.h>
#include <tlvf/CmduMessageTx.h>

namespace beerocks {

// Forward declaration for Agent context saving
class slave_thread;

class VbssTask : public Task {
public:
    VbssTask(slave_thread &btl_ctx, ieee1905_1::CmduMessageTx &cmdu_tx);
    ~VbssTask() {}

    bool handle_cmdu(ieee1905_1::CmduMessageRx &cmdu_rx, uint32_t iface_index,
                     const sMacAddr &dst_mac, const sMacAddr &src_mac, int fd,
                     std::shared_ptr<beerocks_header> beerocks_header) override;

private:
    slave_thread &m_btl_ctx;
    ieee1905_1::CmduMessageTx &m_cmdu_tx;
    int active_onboarding_ap_manager_fd = beerocks::net::FileDescriptor::invalid_descriptor;

    /**
     * @brief Forward Virtual BSS Request messages to the AP manager.
     *
     * @param cmdu_rx Received CMDU.
     * @return true on success, otherwise false.
     */
    void handle_virtual_bss_request(ieee1905_1::CmduMessageRx &cmdu_rx);

    /**
     * @brief Handle the security context request sent by the
     * controller.
     *
     * @param cmdu_rx Received CMDU to be handled.
     * @return true on success, otherwise false
     */
    bool handle_security_context_request(ieee1905_1::CmduMessageRx &cmdu_rx);

    /**
     * @brief Handle the channel switch announcement request sent by the controller.
     * 
     * @param cmdu_rx Received CMDU to be handled.
     * @return true on success, false otherwise.
     */
    bool handle_channel_switch_request(ieee1905_1::CmduMessageRx &cmdu_rx);

    /**
     * @brief Handle the Virtual BSS Move Preparation Request message.
     *
     * @param cmdu_rx Received CMDU.
     * @return true on success, otherwise false
     */
    bool handle_virtual_bss_move_preparation_request(ieee1905_1::CmduMessageRx &cmdu_rx);

    /**
     * @brief Forward Virtual BSS Response messages to the Controller.
     *
     * @param cmdu_rx Received CMDU.
     * @return true on success, otherwise false.
     */
    void handle_virtual_bss_response(ieee1905_1::CmduMessageRx &cmdu_rx);

    /**
     * @brief Handle the Move Cancel request sent by the controller.
     *
     * @param cmdu_rx Received CMDU to be handled.
     * @return true on success, false otherwise.
     */
    bool handle_move_cancel_request(ieee1905_1::CmduMessageRx &cmdu_rx);
};
} // namespace beerocks

#endif // _VBSS_TASK_H_
