#ifndef INTERFACE_CAN_HPP
#define INTERFACE_CAN_HPP

#include "can.hpp"
#include "controlcan.h"
#include <semaphore.h>
#include <cstdint>
#include "jetson_can.hpp"

struct CAN_context *get_can_ctx(CAN_TypeDefHD *hcan);
bool StartCanDevice(void);
bool StartCanServer(CAN_TypeDefHD *hcan);
void CanSendMessage(CAN_context *canCtx, BYTE *txData);

// callback functions
void tx_complete_callback(CAN_TypeDefHD *hcan);       // use this to calculate canBus receive rate
void tx_abort_callback(CAN_TypeDefHD *hcan);          // use this to calculate lags in the system
                                                      // success messages  can be calculated by subtracting tx_abort from tx_complete
void msg_pending_callback(CAN_TypeDefHD *hcan);       // not implemented yet
void fifo0_full_callback(CAN_TypeDefHD *hcan);        // not likely to happen since we manage the rate of sending in the application level
                                                      // because the catch in the CAN driver is slower than jetson nano. (prediction)
void fifo1_msg_pending_callback(CAN_TypeDefHD *hcan); // not implemented yet
void fifo1_full_callback(CAN_TypeDefHD *hcan);
void error_callback(CAN_TypeDefHD *hcan); // not implemented yet

#endif // __INTERFACE_CAN_HPP
