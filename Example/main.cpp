#include "singlemotor.h"
#include <chrono>
#include "interface_can.hpp"

SingleMotor motor(&hcan1);


CAN_context* canCtx = get_can_ctx(&hcan1);
/* Default Entry -------------------------------------------------------*/
int main(void)
{
    // Init all communication 
    CAN_TypeDefHD();

    // Init Robot.
    motor.Init();

 // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();
    


    // move to zero position
    motor.MoveJoint(0);

    // write a loop to move the motor from 0 to 360 degree in 2 seconds

    for (int i = 0; i < 360; i++)
    {
        motor.MoveJoint(i);
     
    }
    // backward rotation
    for (int i = 0; i > -360; i--)
    {
        motor.MoveJoint(i);
      
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    printf("Test Finished\n");
    printf("total message processed: %d\n", canCtx->received_msg_cnt);

    printf("Total time taken: %f\n", duration.count());
    printf("Frame per second: %f\n", canCtx->received_msg_cnt / duration.count());
    return 0;
}
