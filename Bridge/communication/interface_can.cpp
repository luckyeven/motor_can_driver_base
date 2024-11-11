#include "interface_can.hpp"

// defined in can.c
extern CAN_TypeDefHD hcan1; // can channel 1 handle
extern CAN_TypeDefHD hcan2; // can channel 2 handle

CAN_context can1Ctx;
CAN_context can2Ctx;
static CAN_context *ctxs = nullptr;

static BYTE data[8];

sem_t sem_can1_tx;
sem_t sem_can2_tx;

struct CAN_context *get_can_ctx(CAN_TypeDefHD *hcan)
{
    if (hcan->dwCANInd == CAN_INDEX_1)
        return &can1Ctx;
    else if (hcan->dwCANInd == CAN_INDEX_2)
        return &can2Ctx;
    else
        printf("falt");
    return nullptr;
}

// Start the Can Device

bool StartCanDevice(void)
{
    if (!open_can())
    {
        return false;
    }
    return true;
}

bool StartCanServer(CAN_TypeDefHD *hcan)
{
    if (hcan->dwCANInd == CAN_INDEX_1)
    {
        ctxs = &can1Ctx;
        ctxs->handle = &hcan1;
        // printf("motor id: %d \n", ctxs);
        sem_init(&sem_can1_tx, 0, 1);
    }
    else if (hcan->dwCANInd == CAN_INDEX_2)
    {
        ctxs = &can2Ctx;
        ctxs->handle = &hcan2;
        sem_init(&sem_can2_tx, 0, 1);
    }
    else
        return false; // fail if none of the above checks matched

    // ctxs->node_id = 0;

    if (ctxs->handle == &hcan1)
    {
        auto status = CAN1_Init();
        return (status == STATUS_OK);
    }
    else if (ctxs->handle == &hcan2)
    {
        auto status = CAN2_Init();
        return (status == STATUS_OK);
    }
    else
    {
        return false; // neither CAN1 nor CAN2 are initialized
    }
}

void tx_complete_callback(CAN_TypeDefHD *hcan)
{
    CAN_context *ctx = get_can_ctx(hcan);
    if (!ctx)
        return;
    ctx->TxCompleteCallbackCnt++;

    if (hcan->dwCANInd == CAN_INDEX_1)
        sem_post(&sem_can1_tx);
    else if (hcan->dwCANInd == CAN_INDEX_2)
        sem_post(&sem_can2_tx);
}

void tx_aborted_callback(CAN_TypeDefHD *hcan)
{
    if (!get_can_ctx(hcan))
        return;
    get_can_ctx(hcan)->TxAbortCallbackCnt++;
}

// TODO: implement this function
void tx_error(CAN_context *ctx)
{
}

void CAN_Fifo0FullCallback(CAN_TypeDefHD *hcan)
{
    if (get_can_ctx(hcan))
        get_can_ctx(hcan)->Fifo0FullCallbackCnt++;
}

void CAN_Fifo1MsgPendingCallback(CAN_TypeDefHD *hcan)
{
    if (get_can_ctx(hcan))
        get_can_ctx(hcan)->Fifo1MsgPendingCallbackCnt++;
}

void CAN_Fifo1FullCallback(CAN_TypeDefHD *hcan)
{
    if (get_can_ctx(hcan))
        get_can_ctx(hcan)->Fifo1FullCallbackCnt++;
}

/*
 * @brief  This function adds error counter when cananalizer detects an error
 */
void CAN_ErrorCallback(CAN_TypeDefHD *hcan)
{
    // TODO: implement this function
}

void CanSendMessage(CAN_context *canCtx, BYTE *txData)
{
    printf("id: %d \n", canCtx->node_id);

    int semaphore_status;
    if (canCtx->handle->dwCANInd == CAN_INDEX_1)
        semaphore_status = sem_wait(&sem_can1_tx);
    else if (canCtx->handle->dwCANInd == CAN_INDEX_2)
        semaphore_status = sem_wait(&sem_can2_tx);
    else
        return;

    if (semaphore_status == 0)
        sendCanCommand(canCtx, txData, tx_complete_callback, tx_aborted_callback);
}
