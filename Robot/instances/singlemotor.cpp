#include <iostream>

#include <chrono>

#include "ctrl_motor.hpp"
#include "singlemotor.h"
#include "interface_can.hpp"


SingleMotor::SingleMotor(CAN_TypeDefHD* _hcan) :
    hcan(_hcan)
{
    motorJ= new CtrlMotor(_hcan, 14, false, 101, -360, 360);
  
}



SingleMotor::~SingleMotor()
{
    close_device();
    delete motorJ;

   
}

void SingleMotor::Init()
{   
    
    if(!StartCanDevice()){
        return;
    }

    if(!StartCanServer(hcan)){
        return;
    }
    //SetCommandMode(DEFAULT_COMMAND_MODE);
    //SetJointSpeed(DEFAULT_JOINT_SPEED);
}

void SingleMotor::Reboot()
{
    motorJ->Reboot();
    
}

void SingleMotor::MoveJoint(int32_t _Val)
{   //printf("angle: %d \n", _Val);
    motorJ->SetAngle(_Val);
}



void SingleMotor::SetJointSpeed(int32_t _speed)
{
    if (_speed < 0)_speed = 0;
    else if (_speed > 5000) _speed = 5000;

   motorJ->SetVelocitySetPoint(_speed);
}


