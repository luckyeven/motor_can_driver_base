#ifndef JETSON_CAN_HPP
#define JETSON_CAN_HPP

#include "controlcan.h"
#include <cstdint>


typedef struct _CAN_TypeDefHD
{
	DWORD dwDeviceType;
	DWORD dwDeviceInd;
	DWORD dwCANInd;
} CAN_TypeDefHD;

struct CAN_context
{
    CAN_TypeDefHD *handle = nullptr;
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
    int TxMailboxAbortCallbackCnt = 0;
    int ErrorCallbackCnt = 0;

    uint32_t received_msg_cnt = 0;
    uint32_t received_ack = 0;
    uint32_t unexpected_errors = 0;
    uint32_t unhandled_messages = 0;
};

#endif