


#ifndef _MOTOR_CONTROL_APP_
#define _MOTOR_CONTROL_APP_


void MotorControl_UpdateMotorXStatus(uint8_t MotorDir,int16_t Speed);
void MotorControl_UpdateMotorYStatus(uint8_t MotorDir,int16_t Speed);
void MotorControl_Setup(void);
void MotorControl_Loop(void);



#endif /*_MOTOR_CONTROL_APP_*/
