#include <iostream>

#include <chrono>
#include "ctrl_motor.hpp" 
#include "singlemotor.h"


SingleMotor::SingleMotor(CAN_HandleTypeDef* _hcan) :
    hcan(_hcan)
{
    motorJ= new CtrlMotor(_hcan, 0, false, 1, -180, 180);
  
}

SingleMotor::~SingleMotor()
{
   
    delete motorJ;

   
}

void SingleMotor::Init()
{   
    SetCommandMode(DEFAULT_COMMAND_MODE);
    SetJointSpeed(DEFAULT_JOINT_SPEED);
}

void SingleMotor::Reboot()
{
    motorJ->Reboot();
    
}

void SingleMotor::MoveJoint(int32_t _Val)
{
    motorJ->SetPositionSetPoint(_Val);
}



void SingleMotor::SetJointSpeed(int32_t _speed)
{
    if (_speed < 0)_speed = 0;
    else if (_speed > 5000) _speed = 5000;

   motorJ->SetVelocitySetPoint(_speed);
}


