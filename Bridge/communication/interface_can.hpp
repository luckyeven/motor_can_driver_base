#ifndef __INTERFACE_CAN_HPP
#define __INTERFACE_CAN_HPP

#include "controlcan.h"
#include "can.hpp"
struct CAN_context
{
    CAN_HandleTypeDef *handle = nullptr;
    UINT node_id = 0;
    BYTE DataLen = 0;
    uint32_t tx_msg_cnt = 0;

    // uint8_t node_id_rng_state = 0;

    // count occurrence various callbacks
    // some of them are not used yet
    uint32_t TxCompleteCallbackCnt = 0;
    uint32_t TxAbortCallbackCnt = 0;
    int MsgPendingCallbackCnt = 0;
    int Fifo0FullCallbackCnt = 0;
    int Fifo1MsgPendingCallbackCnt = 0;
    int Fifo1FullCallbackCnt = 0;

    int ErrorCallbackCnt = 0;

    uint32_t received_msg_cnt = 0;
    uint32_t received_ack = 0;
    uint32_t unexpected_errors = 0;
    uint32_t unhandled_messages = 0;
};

struct CAN_context *get_can_ctx(CAN_HandleTypeDef *hcan);
void startCanDevice(void);
bool StartCanServer(CAN_HandleTypeDef *hcan);
void CanSendMessage(CAN_context *canCtx, BYTE *txData);

// callback functions
void tx_complete_callback(CAN_HandleTypeDef *hcan);       // use this to calculate canBus receive rate
void tx_abort_callback(CAN_HandleTypeDef *hcan);          // use this to calculate lags in the system
                                                          // success messages  can be calculated by subtracting tx_abort from tx_complete
void msg_pending_callback(CAN_HandleTypeDef *hcan);       // not implemented yet
void fifo0_full_callback(CAN_HandleTypeDef *hcan);        // not likely to happen since we manage the rate of sending in the application level
                                                          // because the catch in the CAN driver is slower than jetson nano. (prediction)
void fifo1_msg_pending_callback(CAN_HandleTypeDef *hcan); // not implemented yet
void fifo1_full_callback(CAN_HandleTypeDef *hcan);
void error_callback(CAN_HandleTypeDef *hcan); // not implemented yet

#endif // __INTERFACE_CAN_HPP
