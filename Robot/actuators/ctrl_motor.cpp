#include "ctrl_motor.hpp"
/*
 * 所有的 // TODO: reserved function 都是未经过测试的，预留给未来使用的接口。 
*/
CtrlMotor::CtrlMotor(CAN_TypeDefHD *_hcan, UINT _id, bool _inverse,
                     uint8_t _reduction, float _angleLimitMin, float _angleLimitMax) : nodeID(_id), hcan(_hcan), inverseDirection(_inverse), reduction(_reduction),
                                                                                       angleLimitMin(_angleLimitMin), angleLimitMax(_angleLimitMax)
{
    ctx = get_can_ctx(hcan);

    txHeader = {

        .motorId = nodeID};
    // printf("textheader id: %d\n",txHeader.motorId);
}

void CtrlMotor::SetEnable(bool _enable)
{ // TODO: reserved function
    state = _enable ? FINISH : STOP;
}

void CtrlMotor::SetCurrentSetPoint(int32_t _val)
{ // TODO: reserved function
    state = RUNNING;
    canBuf[0] = SET_CURRENT_MODE;
    // Float to Bytes
    auto *b = (unsigned char *)&_val;
    for (int i = 0; i < 4; i++)
        canBuf[i + 1] = *(b + i);

    CanSendMessage(ctx, canBuf, &txHeader);
}

void CtrlMotor::SetVelocitySetPoint(int32_t _val)
{ // TODO: reserved function
    state = RUNNING;

    canBuf[0] = SET_VELOCITY_MODE;
    // Float to Bytes
    auto *b = (unsigned char *)&_val;
    for (int i = 0; i < 4; i++)
        canBuf[i + 1] = *(b + i);

    CanSendMessage(ctx, canBuf, &txHeader);
}

void CtrlMotor::SetPositionSetPoint(int32_t _val)
{
    ctx->DataLen = 5; // sendding command.   for receiving length is  1
    canBuf[0] = (BYTE)SET_POSITION_MODE;

    //  Float to Bytes

    auto *b = (unsigned char *)&_val;
    for (int i = 0; i < 4; i++)
    {
        canBuf[i + 1] = *(b + i);
    }

    // printf("setpositionsetpoint id: %d", txHeader.motorId);
    CanSendMessage(ctx, canBuf, &txHeader);
}

// TODO: implement this function
void CtrlMotor::SetPositionWithVelocityLimit(int32_t _pos, int32_t _vel)
{ // TODO: reserved function
}

void CtrlMotor::SetNodeID(uint32_t _id) // use with caution
{                                       // TODO: reserved function

    // Int to Bytes
    canBuf[0] = SET_CAN_ID;
    auto *b = (unsigned char *)&_id;
    for (int i = 0; i < 4; i++)
        canBuf[i + 1] = *(b + i);

    CanSendMessage(ctx, canBuf, &txHeader);
}

void CtrlMotor::SetMaxCurrentLimit(int32_t _val)
{ // TODO: reserved function

    canBuf[0] = SET_MAX_POSITIVE_CURRENT;
    // Float to Bytes
    auto *b = (unsigned char *)&_val;
    for (int i = 0; i < 4; i++)
        canBuf[i] = *(b + i);
    canBuf[4] = 1;

    CanSendMessage(ctx, canBuf, &txHeader);
}

void CtrlMotor::SetMinCurrentLimit(int32_t _val)
{ // TODO: reserved function

    canBuf[0] = SET_MIN_NEGATIVE_ACCELERATION;
    // Float to Bytes
    auto *b = (unsigned char *)&_val;
    for (int i = 0; i < 4; i++)
        canBuf[i + 1] = *(b + i);

    CanSendMessage(ctx, canBuf, &txHeader);
}

void CtrlMotor::SetMaxVelocityLimit(int32_t _val)
{ // TODO: reserved function

    canBuf[0] = SET_MAX_ALLOWED_SPEED;
    // Float to Bytes
    auto *b = (unsigned char *)&_val;
    for (int i = 0; i < 4; i++)
        canBuf[i + 1] = *(b + i);

    CanSendMessage(ctx, canBuf, &txHeader);
}
void CtrlMotor::SetMinVelocityLimit(int32_t _val)
{ // TODO: reserved function

    canBuf[0] = SET_MIN_ALLOWED_SPEED;
    // Float to Bytes
    auto *b = (unsigned char *)&_val;
    for (int i = 0; i < 4; i++)
        canBuf[i + 1] = *(b + i);

    CanSendMessage(ctx, canBuf, &txHeader);
}

void CtrlMotor::SetAcceleration(int32_t _val)
{ // TODO: reserved function

    canBuf[0] = SET_MAX_POSITIVE_ACCELERATION;
    // Float to Bytes
    auto *b = (unsigned char *)&_val;
    for (int i = 0; i < 4; i++)
        canBuf[i + 1] = *(b + i);

    CanSendMessage(ctx, canBuf, &txHeader);
}

void CtrlMotor::SetDeceleration(int32_t _val)
{ // TODO: reserved function

    canBuf[0] = SET_MIN_NEGATIVE_ACCELERATION;
    // Float to Bytes
    auto *b = (unsigned char *)&_val;
    for (int i = 0; i < 4; i++)
        canBuf[i + 1] = *(b + i);

    CanSendMessage(ctx, canBuf, &txHeader);
}

void CtrlMotor::ApplyPositionAsHome()
{
    // TODO: soft zero position alignment
}

void CtrlMotor::Reboot()
{ // TODO: reserved function

    // CanSendMessage(ctx, canBuf, &txHeader, &txHeader); TODO: clean up
}

void CtrlMotor::SetAngle(int32_t _angle)
{
    // printf("in SetAngle, id is %u\n", ctx->node_id);
    _angle = inverseDirection ? -_angle : _angle;
    int32_t MotorCnt = _angle / 360.0f * (uint8_t)reduction * 65536;
    // printf("MotorCnt: %d \n", MotorCnt);
    SetPositionSetPoint(MotorCnt);
}

void CtrlMotor::SetAngleWithVelocityLimit(int32_t _angle, int32_t _vel)
{
    // TODO: implement this function
}

void CtrlMotor::UpdateAngle()
{
    // TODO: reserved function
    // CanSendMessage(ctx, canBuf, &txHeader);
}

void CtrlMotor::UpdateAngleCallback(int32_t _pos, bool _isFinished)
{
    state = _isFinished ? FINISH : RUNNING;

    float tmp = _pos / (float)reduction * 360;
    angle = inverseDirection ? -tmp : tmp;
}
// TODO:
void CtrlMotor::SetDceKp(int32_t _val)
{
}
// TODO:
void CtrlMotor::SetDceKv(int32_t _val)
{
}
// TODO:
void CtrlMotor::SetDceKi(int32_t _val)
{
}
// TODO:
void CtrlMotor::SetDceKd(int32_t _val)
{
}
