#include <Arduino.h>
#include "Common.h"
#include "JoyStickController_cfg.h"

static uint8_t Dir = MOVE_STOP;
static int16_t Speed = 0;

static int16_t JoyStickController_MapReading(int16_t inputReading)
{
  #if LOY_STICK_C_SERIAL_DEBUG
  SERIAL_DEBUG.print("JoyStickApp-> Maping Reading");
  SERIAL_DEBUG.println(inputReading);
  #endif
  
  if(inputReading >= ZERO_ADC_READING) // in (MAX ADC 255 ~ Zero ADC 128)
  {
      inputReading = map(inputReading, ZERO_ADC_READING, MAX_ADC_READING,
                                       ZERO_MAP_READING, MAX_MAP_READING);
  }
  else 
  {
      inputReading = map(inputReading,MIN_ADC_READING, ZERO_ADC_READING,
                                      MIN_MAP_READING, ZERO_MAP_READING);
  }

  #if LOY_STICK_C_SERIAL_DEBUG
  SERIAL_DEBUG.print("JoyStickApp-> Mapped Reading");
  SERIAL_DEBUG.println(inputReading);
  #endif
  
  return inputReading;
}


void JoyStickControllerA_Setup(void)
{
  #if LOY_STICK_C_SERIAL_DEBUG
  SERIAL_DEBUG.println("JoyStickApp-> Setup Controller A");
  #endif
  
  pinMode(JOYSTICK_A_X_AXIS_PIN,INPUT);
  pinMode(JOYSTICK_A_Y_AXIS_PIN,INPUT);
  pinMode(JOYSTICK_A_SW_PIN,INPUT);
}

int16_t JoyStickControllerA_GetXReading(void)
{
  #if LOY_STICK_C_SERIAL_DEBUG
  SERIAL_DEBUG.println("JoyStickApp-> Getting Controller A X reading");
  #endif
  
  int16_t AnalogReading = analogRead(JOYSTICK_A_X_AXIS_PIN); // 0  128  255 -> -255 0 255 
  AnalogReading = JoyStickController_MapReading(AnalogReading);         
  return AnalogReading;
}

int16_t JoyStickControllerA_GetYReading(void)
{
  #if LOY_STICK_C_SERIAL_DEBUG
  SERIAL_DEBUG.println("JoyStickApp-> Getting Controller A Y reading");
  #endif
  
  int16_t AnalogReading = analogRead(JOYSTICK_A_Y_AXIS_PIN);
  AnalogReading = JoyStickController_MapReading(AnalogReading);             
  return AnalogReading;
}

uint8_t JoyStickControllerA_GetSW(void)
{
  uint8_t Reading = 0;
  if(HIGH == digitalRead(JOYSTICK_A_SW_PIN))
  {
    Reading = 1;
    
    #if LOY_STICK_C_SERIAL_DEBUG
    SERIAL_DEBUG.println("JoyStickApp->Controller A sw is pressed");
    #endif
  }
 
  return Reading;
}


void JoyStickControllerB_Setup(void)
{
  #if LOY_STICK_C_SERIAL_DEBUG
  SERIAL_DEBUG.println("JoyStickApp-> Setup Controller B");
  #endif
  
  pinMode(JOYSTICK_B_X_AXIS_PIN,INPUT);
  pinMode(JOYSTICK_B_Y_AXIS_PIN,INPUT);
  pinMode(JOYSTICK_B_SW_PIN,INPUT);
}

int16_t JoyStickControllerB_GetXReading(void)
{
  #if LOY_STICK_C_SERIAL_DEBUG
  SERIAL_DEBUG.println("JoyStickApp-> Getting Controller B X reading");
  #endif
  
  int16_t AnalogReading = analogRead(JOYSTICK_B_X_AXIS_PIN);
  AnalogReading = JoyStickController_MapReading(AnalogReading);         
  return AnalogReading;
}

int16_t JoyStickControllerB_GetYReading(void)
{
  #if LOY_STICK_C_SERIAL_DEBUG
  SERIAL_DEBUG.println("JoyStickApp-> Getting Controller B Y reading");
  #endif
  
  int16_t AnalogReading = analogRead(JOYSTICK_B_Y_AXIS_PIN);
  AnalogReading = JoyStickController_MapReading(AnalogReading);             
  return AnalogReading;
}

uint8_t JoyStickControllerB_GetSW(void)
{
  uint8_t Reading = 0;
  if(HIGH == digitalRead(JOYSTICK_B_SW_PIN))
  {
    Reading = 1;
    
    #if LOY_STICK_C_SERIAL_DEBUG
    SERIAL_DEBUG.println("JoyStickApp->Controller B sw is pressed");
    #endif
  }
 return Reading;
}


void JoyStickController_Setup(void)
{
    JoyStickControllerA_Setup();
    JoyStickControllerB_Setup();
}


void JoyStickController_Loop(void)
{
  int16_t AX_Reading = JoyStickControllerA_GetXReading(); // -255 ~ 255
  int16_t AY_Reading = JoyStickControllerA_GetYReading(); // -255 ~ 255
  int16_t BY_Reading = JoyStickControllerB_GetYReading(); // -255 ~ 255

  if(AY_Reading < ZERO_MAP_READING )
  {
    Dir = MOVE_BACKWARD;
    Speed = abs(AY_Reading);
  }
  else if(AY_Reading == ZERO_MAP_READING)
  {
    Dir = MOVE_STOP;
    Speed = 0;
  }
  else if(AY_Reading > ZERO_MAP_READING)
  {
      Dir = MOVE_FORWARD;
      Speed = abs(AY_Reading);
  }

  
  else if(AX_Reading < ZERO_MAP_READING)
  {
      Dir = MOVE_LEFT;
      Speed = abs(AX_Reading);
  }
  else if(AX_Reading == ZERO_MAP_READING)
  {
      Dir = MOVE_STOP;
      Speed = 0;
  }
  else if(AX_Reading > ZERO_MAP_READING)
  {
      Dir = MOVE_RIGHT;
      Speed = abs(AX_Reading);
  }
  
  else if(BY_Reading < ZERO_MAP_READING )
  {
    Dir = MOVE_DOWN;
    Speed = abs(BY_Reading);
  }
  else if(BY_Reading == ZERO_MAP_READING)
  {
    Dir = MOVE_STOP;
    Speed = 0;
  }
  else if(BY_Reading > ZERO_MAP_READING)
  {
      Dir = MOVE_UP;
      Speed = abs(BY_Reading);
  }

  #if LOY_STICK_C_SERIAL_DEBUG
  SERIAL_DEBUG.print ("JoyStickApp->Controller Dir: ");
  SERIAL_DEBUG.print ((char)Dir);
  SERIAL_DEBUG.print (" Controller Speed: ");
  SERIAL_DEBUG.println (Speed);
  #endif
  
}

uint8_t JoyStickController_GetDir(void)
{
  return Dir;
}

int16_t JoyStickController_GetSpd(void)
{
  return Speed;
}
