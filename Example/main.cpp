#include "singlemotor.h"
#include <chrono>
#include "interface_can.hpp"


SingleMotor motor(&hcan1) ;


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
    motor.MoveJoint(-360);


    for(int loop = 0; loop < 10;loop++){
     //std::this_thread::sleep_for(std::chrono::milliseconds(3)); 
        for (int i = -360; i < 3600; i++)
        {
                motor.MoveJoint(i);
      //          std::this_thread::sleep_for(std::chrono::milliseconds(3));
        }
        // backward rotation
      //    std::this_thread::sleep_for(std::chrono::milliseconds(3)); 
        for (int i = 360; i > -360; i--)
        {
            motor.MoveJoint(i);
       //     std::this_thread::sleep_for(std::chrono::milliseconds(3));       
        }
    }
    //         motor.MoveJoint(0);
    //   std::this_thread::sleep_for(std::chrono::milliseconds(4000));  
    // motor.MoveJoint(90);
    //   std::this_thread::sleep_for(std::chrono::milliseconds(4000));  
    // motor.MoveJoint(180);
    //   std::this_thread::sleep_for(std::chrono::milliseconds(4000));  
    // motor.MoveJoint(270);
    //       std::this_thread::sleep_for(std::chrono::milliseconds(4000));  
    //         motor.MoveJoint(0);
    //   std::this_thread::sleep_for(std::chrono::milliseconds(4000));  
    //}

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    printf("Test Finished\n");
    printf("total message processed: %d\n", canCtx->TxCompleteCallbackCnt);
    printf("total message aborted: %d\n", canCtx->TxAbortCallbackCnt);
    printf("Total time taken: %f\n", duration.count());
    printf("Frame per second: %f\n", canCtx->TxCompleteCallbackCnt / duration.count());

    //printf("xxxxxxxxxxxx");
    //printf("motorid: %u\n", canCtx->node_id);
    return 0;

}
