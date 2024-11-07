/**
  ******************************************************************************
  * @file    can.hpp
  * @brief   This file contains all the function prototypes for
  *          the can.cpp file
  ******************************************************************************

  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_HPP__
#define __CAN_HPP__

/* Includes ------------------------------------------------------------------*/
#include "controlcan.h"
#include <iostream>
#include "interface_can.hpp"
/* USER CODE BEGIN Includes */
#define DEVICE_TYPE VCI_USBCAN2
#define DEVICE_INDEX 0
#define CAN_INDEX_1 0
#define CAN_INDEX_2 1


/* USER CODE END Includes */
#define CAN_ID_HD DWORD

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */
void open_can(void);
uint8_t CAN1_Init(void);
uint8_t CAN2_Init(void);
void sendCanCommand(CAN_context *canCtx, BYTE *data);
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */


#endif /* __CAN_HPP__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
