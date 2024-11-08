#ifndef SINGLE_MOTOR_H
#define SINGLE_MOTOR_H


#include "ctrl_motor.hpp"
#define ALL 0



class SingleMotor
{
public:
    explicit SingleMotor(CAN_TypeDefHD* _hcan);
    ~SingleMotor();


    enum CommandMode
    {
        COMMAND_TARGET_POINT_SEQUENTIAL = 1,
        COMMAND_TARGET_POINT_INTERRUPTABLE,
        COMMAND_CONTINUES_TRAJECTORY,
        COMMAND_MOTOR_TUNING
    };



    // This is the pose when power on.
   
    const int32_t DEFAULT_JOINT_SPEED = 500;  
   
    const int32_t DEFAULT_JOINT_ACCELERATION_LOW = -5;    
    const int32_t DEFAULT_JOINT_ACCELERATION_HIGH = +5;  
    const CommandMode DEFAULT_COMMAND_MODE = COMMAND_TARGET_POINT_INTERRUPTABLE;


    CommandMode commandMode = DEFAULT_COMMAND_MODE;
    CtrlMotor* motorJ = {nullptr};
   


    void Init();
 
    void MoveJoint(int32_t _Val);
    void SetJointSpeed(int32_t _speed);
    void SetJointAcceleration(int32_t _acc);
    void UpdateJointAngles();
    void UpdateJointAnglesCallback();
    void UpdateJointPose6D();
    void Reboot();
    void CalibrateHomeOffset();
    void Homing();
    void Resting();
    bool IsMoving();
    bool IsEnabled();
    void SetCommandMode(uint32_t _mode);


  

private:
    CAN_TypeDefHD* hcan;
    float jointSpeed = DEFAULT_JOINT_SPEED;
    float jointSpeedRatio = 1;
  
   


};
#endif //SINGLE_MOTOR_H
