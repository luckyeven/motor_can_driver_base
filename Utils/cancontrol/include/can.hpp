/**
  ******************************************************************************
  * @file    can.hpp
  * @brief   This file contains all the function prototypes for
  *          the can.cpp file
  ******************************************************************************

  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CAN_HPP
#define CAN_HPP

/* Includes ------------------------------------------------------------------*/
#include "jetson_can.hpp"
#include "controlcan.h"
#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
//#include "interface_can.hpp"

/* USER CODE BEGIN Includes */
#define DEVICE_TYPE VCI_USBCAN2
#define DEVICE_INDEX 0

/* USER CODE END Includes */
#define CAN_ID_HD DWORD

// 句柄类型定义

extern CAN_TypeDefHD hcan1;
extern CAN_TypeDefHD hcan2;

/* USER CODE BEGIN Private defines */

using tx_complete_Callback = std::function<void(CAN_TypeDefHD*)>;
using tx_aborted_Callback = std::function<void(CAN_TypeDefHD*)>;
/* USER CODE END Private defines */
uint8_t open_can(void);
uint8_t CAN1_Init(void);
uint8_t CAN2_Init(void);
void sendCanCommand(CAN_context *canCtx, BYTE *data, header_textdef* txHeader ,tx_complete_Callback tx_complete_callback, tx_aborted_Callback tx_aborted_callback);
uint8_t close_device(void);
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */


#endif /* __CAN_HPP__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
