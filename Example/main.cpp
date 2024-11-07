#include "singlemotor.h"


SingleMotor motor(&hcan1);

CAN_context* canCtx = get_can_ctx(&hcan1);
/* Default Entry -------------------------------------------------------*/
void Main(void)
{
    // Init all communication 
    open_can();

    // Init Robot.
    motor.Init();

  
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

    printf("Test Finished\n");
    printf("total message processed: %d\n", canCtx->received_msg_cnt);


    
}
