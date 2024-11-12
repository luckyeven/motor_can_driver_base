#include "prototype_robot.h"
#include <chrono>
#include "interface_can.hpp"


PrototypeRobot robot(&hcan1) ;


CAN_context* canCtx = get_can_ctx(&hcan1);


/* Default Entry -------------------------------------------------------*/
int main(void)
{   
    // Init all communication 
    CAN_TypeDefHD();

    // Init Robot.
    robot.Init();

 // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();
    
    int32_t angles[7] = {0};


    // move to zero position
    robot.MoveJoints(angles);


    for(int loop = 0; loop < 10;loop++){
     //std::this_thread::sleep_for(std::chrono::milliseconds(3)); 
        for (int i = -360; i < 360; i++)
        {       
            for(int j = 0; j < 7;j++){
              angles[j] = i;  
            }
              robot.MoveJoints(angles);  
      //          std::this_thread::sleep_for(std::chrono::milliseconds(3));
        }
        // backward rotation
      //    std::this_thread::sleep_for(std::chrono::milliseconds(3)); 
        for (int i = 360; i > -360; i--)
        {
            for(int j = 0; j < 7;j++){
              angles[j] = i;  
            }
              robot.MoveJoints(angles);  
       //     std::this_thread::sleep_for(std::chrono::milliseconds(3));       
        }
    }
    //         robot.MoveJoint(0);
    //   std::this_thread::sleep_for(std::chrono::milliseconds(4000));  
    // robot.MoveJoint(90);
    //   std::this_thread::sleep_for(std::chrono::milliseconds(4000));  
    // robot.MoveJoint(180);
    //   std::this_thread::sleep_for(std::chrono::milliseconds(4000));  
    // robot.MoveJoint(270);
    //       std::this_thread::sleep_for(std::chrono::milliseconds(4000));  
    //         robot.MoveJoint(0);
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
    //printf("robotid: %u\n", canCtx->node_id);
    return 0;

}
