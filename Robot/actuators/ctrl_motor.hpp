#ifndef CTRL_MOTOR_HPP
#define CTRL_MOTOR_HPP
#include "controlcan.h"
#include "can.hpp"
#include "jetson_can.hpp"
#include "interface_can.hpp"
enum MotorCommands {
    // 获取类命令
    GET_OPERATION_MODE = 0x03,             // 获取电机运行模式
    SET_STOP_MODE = 0x02,                  // 设置电机为停止模式
    GET_CURRENT = 0x04,                    // 获取电机电流
    GET_TARGET_CURRENT = 0x05,             // 获取电机目标电流
    GET_SPEED = 0x06,                      // 获取电机速度
    GET_TARGET_SPEED = 0x07,               // 获取电机目标转速
    GET_POSITION = 0x08,                   // 获取电机当前位置
    GET_TARGET_POSITION = 0x09,            // 获取电机的目标位置（非位置模式下此参数将不起作用）
    GET_ERROR_STATE = 0x0A,                // 获取电机错误状态
    CLEAR_ERRORS = 0x0B,                   // 清除电机错误
    GET_SPEED_LOOP_P = 0x10,               // 获取速度环比例
    GET_SPEED_LOOP_I = 0x11,               // 获取速度环积分
    GET_SPEED_LOOP_D = 0x33,               // 获取速度环微分
    GET_POSITION_LOOP_P = 0x12,            // 获取位置环比例
    GET_POSITION_LOOP_I = 0x34,            // 获取位置环积分
    GET_POSITION_LOOP_D = 0x13,            // 获取位置环微分
    GET_BUS_VOLTAGE = 0x14,                // 获取母线电压
    GET_MAX_ABS_CURRENT = 0x37,            // 获取电机最大电流绝对值
    GET_MAX_POSITIVE_CURRENT = 0x35,       // 获取最大正电流
    GET_MIN_NEGATIVE_CURRENT = 0x36,       // 获取最小负电流
    GET_ACCELERATION = 0x16,               // 获取加速度
    GET_DECELERATION = 0x17,               // 获取减速度
    GET_MAX_ALLOWED_POSITIVE_SPEED = 0x18, // 获取最大正向允许速度
    GET_MIN_ALLOWED_NEGATIVE_SPEED = 0x19, // 获取最小负向允许速度
    GET_MAX_ALLOWED_POSITION = 0x1A,       // 获取最大正向位置
    GET_MIN_ALLOWED_POSITION = 0x1B,       // 获取最小负向位置
    RESTORE_FROM_FLASH = 0x0D,             // 从Flash恢复参数
    SAVE_TO_FLASH = 0x0E,                  // 储存参数到Flash
    RESTORE_FACTORY_SETTINGS = 0x0F,       // 恢复出厂设置
    SAVE_FACTORY_SETTINGS = 0x1F,          // 储存参数到出厂设置
    GET_MOTOR_TEMPERATURE = 0x31,          // 获取电机温度
    GET_BOARD_TEMPERATURE = 0x32,          // 获取电路板温度
    GET_CURRENT_P = 0x61,                  // 获取电流P
    GET_CURRENT_I = 0x62,                  // 获取电流I
    GET_CURRENT_D = 0x63,                  // 获取电流D
    GET_MOTOR_TYPE = 0x64,                 // 电机型号
    GET_ENCODER_PARAMS = 0x54,             // 获取位置偏移
    GET_COMBINED_DATA = 0x41,              // 获取电流（0）、速度（2）、位置（4），返回8字节数据

    // 设置类命令
    SET_CURRENT_MODE = 0x1C,               // 设置电机运行模式为电流模式，并设置目标电流
    SET_CURRENT_AND_GET_DATA = 0x42,       // 设置电流并获取电流速度位置，返回8字节数据
    SET_VELOCITY_MODE = 0x1D,              // 设置电机运行模式为速度模式，并设置目标速度
    SET_VELOCITY_AND_GET_DATA = 0x43,      // 设置速度并获取电流速度位置，返回8字节数据
    SET_POSITION_MODE = 0x1E,              // 设置电机运行模式为位置模式，并设置目标位置
    SET_POSITION_AND_GET_DATA = 0x44,      // 设置位置并获取电流速度位置，返回8字节数据
    SET_MAX_POSITIVE_CURRENT = 0x20,       // 设置最大正电流
    SET_MIN_NEGATIVE_CURRENT = 0x21,       // 设置最小负电流
    SET_MAX_POSITIVE_ACCELERATION = 0x22,  // 设置电机最大正向加速度
    SET_MIN_NEGATIVE_ACCELERATION = 0x23,  // 设置电机最小负向加速度
    SET_MAX_ALLOWED_SPEED = 0x24,          // 设置最大正向允许速度
    SET_MIN_ALLOWED_SPEED = 0x25,          // 设置最小负向允许速度
    SET_MAX_POSITION = 0x26,               // 设置最大正向位置
    SET_MIN_POSITION = 0x27,               // 设置最小负向位置
    SET_SPEED_LOOP_P = 0x29,               // 设置速度环比例
    SET_SPEED_LOOP_I = 0x2A,               // 设置速度环积分
    SET_SPEED_LOOP_D = 0x2B,               // 设置速度环微分
    SET_POSITION_LOOP_P = 0x2B,            // 设置位置环比例
    SET_POSITION_LOOP_I = 0x2C,            // 设置位置环积分
    SET_POSITION_LOOP_D = 0x2D,            // 设置位置环微分
    SET_CAN_ID = 0x2E,                     // 设置CAN ID
    ENCODER_ZERO = 0x50,                   // 编码器归零
    MOTOR_EMERGENCY_STOP = 0x52,           // 电机急停
    SET_POSITION_OFFSET = 0x53,            // 设置位置偏移
    SET_BAUD_RATE = 0x3F,                  // 设置波特率
};

class CtrlMotor
{
public:
    enum State
    {
        RUNNING,
        FINISH,
        STOP
    };


    //const uint32_t CTRL_CIRCLE_COUNT = 200 * 256;

    CtrlMotor(CAN_TypeDefHD* _hcan, uint8_t _id, bool _inverse = false, uint8_t _reduction = 101,
                  float _angleLimitMin = -180, float _angleLimitMax = 180);

    UINT nodeID;
    float angle = 0;
    float angleLimitMax;
    float angleLimitMin;
    bool inverseDirection;
    uint8_t reduction;
    State state = STOP;

    void SetAngle(int32_t _angle);
    void SetAngleWithVelocityLimit(int32_t _angle, int32_t _vel);
    // CAN Command
    void SetEnable(bool _enable);

    void SetCurrentSetPoint(int32_t _val);
    void SetVelocitySetPoint(int32_t _val);
    void SetPositionSetPoint(int32_t _val);
    void SetPositionWithVelocityLimit(int32_t _pos, int32_t _vel);
    void SetNodeID(uint32_t _id);
    void SetMaxCurrentLimit(int32_t _val);
    void SetMinCurrentLimit(int32_t _val);
    void SetMaxVelocityLimit(int32_t _val);
    void SetMinVelocityLimit(int32_t _val);    
    void SetAcceleration(int32_t _val);
    void SetDeceleration(int32_t _val);
    virtual void SetDceKp(int32_t _val);
    virtual void SetDceKv(int32_t _val);
    virtual void SetDceKi(int32_t _val);
    virtual void SetDceKd(int32_t _val);
    void ApplyPositionAsHome();

    void Reboot();


    void UpdateAngle();
    void UpdateAngleCallback(int32_t _pos, bool _isFinished);


  

private:
    CAN_TypeDefHD* hcan;
    BYTE canBuf[8] = {};
  
};

#endif //CTRL_MOTOR_HPP
