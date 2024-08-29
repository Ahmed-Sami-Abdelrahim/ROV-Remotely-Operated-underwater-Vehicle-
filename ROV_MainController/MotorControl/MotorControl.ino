#include "Common.h"
#include "MotorControl.h"

void setup() 
{
  // put your setup code here, to run once:
  SERIAL_DEBUG.begin(SERIAL_DEBUG_BAUDRATE);
  MotorControl_Setup();
//  MotorControl_UpdateStatus(MOVE_FORWARD,255);
//  MotorControl_UpdateStatus(MOVE_BACKWARD,255);
//  MotorControl_UpdateStatus(MOVE_LEFT,255);
//  MotorControl_UpdateStatus(MOVE_RIGHT,255);
//  MotorControl_UpdateStatus(MOVE_UP,255);
//  MotorControl_UpdateStatus(MOVE_DOWN,255);
  MotorControl_UpdateStatus(MOVE_STOP,0);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  MotorControl_Loop();

}
