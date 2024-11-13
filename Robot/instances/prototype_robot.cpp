#include <iostream>

#include <chrono>

#include "ctrl_motor.hpp"
#include "prototype_robot.h"
#include "interface_can.hpp"

PrototypeRobot::PrototypeRobot(CAN_TypeDefHD *_hcan) : hcan(_hcan)
{
    motorJ[0] = new CtrlMotor(_hcan, 16, false, 101, -180, 180);
    motorJ[1] = new CtrlMotor(_hcan, 17, false, 101, -180, 180);
    motorJ[2] = new CtrlMotor(_hcan, 18, false, 101, -180, 180);
    motorJ[3] = new CtrlMotor(_hcan, 19, true, 101, -180, 180);
    motorJ[4] = new CtrlMotor(_hcan, 20, false, 101, -180, 180);
    motorJ[5] = new CtrlMotor(_hcan, 21, false, 101, -180, 180);
    motorJ[6] = new CtrlMotor(_hcan, 22, false, 101, -180, 180);
}

PrototypeRobot::~PrototypeRobot()
{
    close_device();
    for (int i = 0; i < 7; ++i)
    {
        delete motorJ[i];
        motorJ[i] = nullptr;
    }
}

void PrototypeRobot::Init()
{

    if (!StartCanDevice())
    {
        return;
    }

    if (!StartCanServer(hcan))
    {
        return;
    }
    // SetCommandMode(DEFAULT_COMMAND_MODE);
    // SetJointSpeed(DEFAULT_JOINT_SPEED);
}

void PrototypeRobot::Reboot()
{
    // TODO: reserved function
    // motorJ->Reboot();
}

void PrototypeRobot::MoveJoints(int32_t *_Val)
{ // printf("angle: %d \n", _Val);

    for (int i = 0; i < 7; i++)
    {
        motorJ[i]->SetAngle(_Val[i]);
    }
}

void PrototypeRobot::SetJointSpeed(int32_t _speed)
{
    if (_speed < 0)
        _speed = 0;
    else if (_speed > 5000)
        _speed = 5000;
    // TODO: reserved function
    // motorJ->SetVelocitySetPoint(_speed);
}
