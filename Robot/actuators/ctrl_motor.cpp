#include "ctrl_motor.hpp"


CtrlMotor::CtrlMotor(CAN_TypeDefHD* _hcan, uint8_t _id, bool _inverse,
                             uint8_t _reduction, float _angleLimitMin, float _angleLimitMax) :
    nodeID(_id), hcan(_hcan), inverseDirection(_inverse), reduction(_reduction),
    angleLimitMin(_angleLimitMin), angleLimitMax(_angleLimitMax)
{

}


void CtrlMotor::SetEnable(bool _enable)
{
    state = _enable ? FINISH : STOP;
}

void CtrlMotor::SetCurrentSetPoint(int32_t _val)
{
    state = RUNNING;
    canBuf[0] = SET_CURRENT_MODE;
    // Float to Bytes
    auto* b = (unsigned char*) &_val;
    for (int i = 0; i < 4; i++)
        canBuf[i+1] = *(b + i);

    CanSendMessage(get_can_ctx(hcan), canBuf);
}


void CtrlMotor::SetVelocitySetPoint(int32_t _val)
{
    state = RUNNING;

    canBuf[0] = SET_VELOCITY_MODE;
    // Float to Bytes
    auto* b = (unsigned char*) &_val;
    for (int i = 0; i < 4; i++)
        canBuf[i+1] = *(b + i);

    CanSendMessage(get_can_ctx(hcan), canBuf);
}


void CtrlMotor::SetPositionSetPoint(int32_t _val)
{
   
    canBuf[0] = SET_POSITION_MODE;
    // Float to Bytes
    auto* b = (unsigned char*) &_val;
    for (int i = 0; i < 4; i++)
        canBuf[i+1] = *(b + i);
 

    CanSendMessage(get_can_ctx(hcan), canBuf);
}

// TODO: implement this function
void CtrlMotor::SetPositionWithVelocityLimit(int32_t _pos, int32_t _vel) 
{
   
}


void CtrlMotor::SetNodeID(uint32_t _id) // use with caution
{
    

    // Int to Bytes
    canBuf[0] = SET_CAN_ID;
    auto* b = (unsigned char*) &_id;
    for (int i = 0; i < 4; i++)
        canBuf[i+1] = *(b + i);
    
    CanSendMessage(get_can_ctx(hcan), canBuf);
}


void CtrlMotor::SetMaxCurrentLimit(int32_t _val)
{
  
    canBuf[0] = SET_MAX_POSITIVE_CURRENT;
    // Float to Bytes
    auto* b = (unsigned char*) &_val;
    for (int i = 0; i < 4; i++)
        canBuf[i] = *(b + i);
    canBuf[4] = 1; 

    CanSendMessage(get_can_ctx(hcan), canBuf);
}


void CtrlMotor::SetMinCurrentLimit(int32_t _val)
{
  
    canBuf[0] = SET_MIN_NEGATIVE_ACCELERATION;
    // Float to Bytes
    auto* b = (unsigned char*) &_val;
    for (int i = 0; i < 4; i++)
        canBuf[i+1] = *(b + i);

    CanSendMessage(get_can_ctx(hcan), canBuf);
}


void CtrlMotor::SetMaxVelocityLimit(int32_t _val)
{
  
    canBuf[0] = SET_MAX_ALLOWED_SPEED;
    // Float to Bytes
    auto* b = (unsigned char*) &_val;
    for (int i = 0; i < 4; i++)
        canBuf[i+1] = *(b + i);
    

    CanSendMessage(get_can_ctx(hcan), canBuf);
}
void CtrlMotor::SetMinVelocityLimit(int32_t _val)
{
  
    canBuf[0] = SET_MIN_ALLOWED_SPEED;
    // Float to Bytes
    auto* b = (unsigned char*) &_val;
    for (int i = 0; i < 4; i++)
        canBuf[i+1] = *(b + i);
    

    CanSendMessage(get_can_ctx(hcan), canBuf);
}


void CtrlMotor::SetAcceleration(int32_t _val)
{

    canBuf[0] = SET_MAX_POSITIVE_ACCELERATION;
    // Float to Bytes
    auto* b = (unsigned char*) &_val;
    for (int i = 0; i < 4; i++)
        canBuf[i+1] = *(b + i);
   

    CanSendMessage(get_can_ctx(hcan), canBuf);
}

void CtrlMotor::SetDeceleration(int32_t _val)
{

    canBuf[0] = SET_MIN_NEGATIVE_ACCELERATION;
    // Float to Bytes
    auto* b = (unsigned char*) &_val;
    for (int i = 0; i < 4; i++)
        canBuf[i+1] = *(b + i);
   

    CanSendMessage(get_can_ctx(hcan), canBuf);
}


void CtrlMotor::ApplyPositionAsHome()  
{
// TODO: soft zero position alignment

}




void CtrlMotor::Reboot()
{
   

    //CanSendMessage(get_can_ctx(hcan), canBuf, &txHeader); TODO: clean up 
}



void CtrlMotor::SetAngle(int32_t _angle)
{
    _angle = inverseDirection ? -_angle : _angle;
    int32_t MotorCnt = _angle / 360.0f * (uint8_t) reduction * 65536 ;
    SetPositionSetPoint(MotorCnt);
}


void CtrlMotor::SetAngleWithVelocityLimit(int32_t _angle, int32_t _vel)
{
    // TODO: implement this function
}


void CtrlMotor::UpdateAngle()
{
    

    //CanSendMessage(get_can_ctx(hcan), canBuf);
}


void CtrlMotor::UpdateAngleCallback(int32_t _pos, bool _isFinished)
{
    state = _isFinished ? FINISH : RUNNING;

    float tmp = _pos / (float) reduction * 360;
    angle = inverseDirection ? -tmp : tmp;
}


void CtrlMotor::SetDceKp(int32_t _val)
{   
   
}


void CtrlMotor::SetDceKv(int32_t _val)
{
}


void CtrlMotor::SetDceKi(int32_t _val)
{
  
}


void CtrlMotor::SetDceKd(int32_t _val)
{
  
}
