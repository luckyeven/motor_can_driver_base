
#include "can.hpp"


CAN_TypeDefHD hcan1 ;
CAN_TypeDefHD hcan2 ;

uint8_t open_can(void)
{
    VCI_BOARD_INFO pInfo1[50];
    int retry_count = 0;
    const int max_retries = 10; 

    while (retry_count < max_retries)
    {
        int num = VCI_FindUsbDevice2(pInfo1);
        std::cout << ">>USBCAN DEVICE NUM: " << num << " PCS" << std::endl;
        
        DWORD dwRel = VCI_OpenDevice(DEVICE_TYPE, DEVICE_INDEX, 0);
        if (dwRel == 1)
        {
            std::cout << "Open Success" << std::endl;
            return STATUS_OK; // Exit if device opens successfully
        }
        else
        {
            std::cout << "open-fail: " << dwRel << " - Retrying in 1 second..." << std::endl;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait for 1 second before retrying
        retry_count++;
    }
    
    std::cout << "Failed to open device after 10 seconds. Exiting..." << std::endl;
    return STATUS_ERR;
}
/* CAN1 init function */
uint8_t CAN1_Init(void)
{
    hcan1.dwDeviceType = VCI_USBCAN2;
    hcan1.dwDeviceInd = DEVICE_INDEX;
    hcan1.dwCANInd = CAN_INDEX_1;

    VCI_INIT_CONFIG config;
    config.AccCode = 0x80000008;
    config.AccMask = 0xFFFFFFFF;
    config.Filter = 2;
    config.Timing0 = 0x00;
    config.Timing1 = 0x14;
    config.Mode = 0;

    if (VCI_InitCAN(DEVICE_TYPE, DEVICE_INDEX, CAN_INDEX_1, &config) != STATUS_OK)
    {
        printf("Init CAN1 failed\n");
        return STATUS_ERR;
    }

    if (VCI_StartCAN(DEVICE_TYPE, DEVICE_INDEX, CAN_INDEX_1) != STATUS_OK)
    {
        printf("Start CAN1 failed\n");
        return STATUS_ERR;
    }
    return STATUS_OK;
}

/* CAN2 init function */
uint8_t CAN2_Init(void)
{
    hcan2.dwDeviceType = VCI_USBCAN2;
    hcan2.dwDeviceInd = DEVICE_INDEX;
    hcan2.dwCANInd = CAN_INDEX_2;
    VCI_INIT_CONFIG config;
    config.AccCode = 0x80000008;
    config.AccMask = 0xFFFFFFFF;
    config.Filter = 2;
    config.Timing0 = 0x00;
    config.Timing1 = 0x14;
    config.Mode = 0;

    if (VCI_InitCAN(DEVICE_TYPE, DEVICE_INDEX, CAN_INDEX_2, &config) != STATUS_OK)
    {
        printf("Init CAN2 failed\n");
        return STATUS_ERR;
    }

    if (VCI_StartCAN(DEVICE_TYPE, DEVICE_INDEX, CAN_INDEX_2) != STATUS_OK)
    {
        printf("Start CAN2 failed\n");
        return STATUS_ERR;
    }
    return STATUS_OK;
}


uint8_t close_device(){
{

	if(!VCI_ResetCAN(VCI_USBCAN2, 0, 0))return STATUS_ERR;//复位CAN1通道。
	
	if(!VCI_ResetCAN(VCI_USBCAN2, 0, 1))return STATUS_ERR;//复位CAN2通道。
	
	if(!VCI_CloseDevice(VCI_USBCAN2,0)) return STATUS_ERR;//关闭设备。
	return STATUS_OK;// temperory retur. 

}

} 

/*
 * Send a single CAN command
 * @param canIdList: list of CAN IDs
 * @param commandList: list of commands
 * @param parameterList: list of parameters
 * @param dataLen: length of data
 * @return STATUS_OK if success, STATUS_ERR if failed
 *
 * The reason for sending a single command at a time is that the VCI_Transmit function use buffer to store on going data flow
 * and the buffer may cause delay due to data transfer from buffer to the actual CAN bus. we try to avoid this delay by controlling
 * sending rate at the application level.
 *
 * Above is an assumption due to the implementation of algorithm is invisible to us. But anyway try to avoid sending command lists is also  recommended by the official documentation.
 */



void sendCanCommand(CAN_context *canCtx, BYTE *data, tx_complete_Callback tx_complete_callback, tx_aborted_Callback tx_aborted_callback)
{

    VCI_CAN_OBJ send;
    // send[i].ID = 0;
    send.SendType = 1;
    send.RemoteFlag = 0;
    send.ExternFlag = 0;
    send.DataLen = canCtx->DataLen;
    send.ID = canCtx->node_id;
    send.Data[0] = data[0];
    // std::cout << "ID:" << send[i].ID << " Command Send: " << send[i].Data[0] << parameterList[i] << std::endl;

    // TODO: phrase the data in application level.(done)

    // int res[4];
    // toIntArray(data, res, 4);
    for (int para_seg = 1; para_seg < canCtx->DataLen; para_seg++)
    {
        send.Data[para_seg] = data[para_seg ];
    }

    DWORD rel;
    rel = VCI_Transmit(canCtx->handle->dwDeviceType, canCtx->handle->dwDeviceInd, canCtx->handle->dwCANInd, &send, 1);
    // std::cout << "Number of Frames:" << rel <<  std::endl;

    // TODO: remove below print functions. use callback function instead.

    if (rel > 0)
    {
        for (int i = 0; i < rel; i++)
        {
            printf("CAN1 TX ID:0x%08X", send.ID);
            printf(" DLC:0x%02X", send.DataLen);
            printf(" data:0x");

            for (int iii = 0; iii < send.DataLen; iii++)
            {
                printf(" %02X", send.Data[iii]);
            }
            printf("\n");
        }
        tx_complete_callback(canCtx->handle);
    }
    else
    {
        //tx_aborted_callback(canCtx->handle);
        // callback function

        tx_aborted_callback(canCtx->handle);
    }

    // callback function
    
}


