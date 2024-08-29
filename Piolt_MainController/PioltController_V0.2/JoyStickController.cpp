#include <Arduino.h>
#include "Common.h"
#include "JoyStickController_cfg.h"

static uint8_t Dir_X = MOVE_STOP;
static int16_t Speed_X = 0;

static uint8_t Dir_Y = MOVE_STOP;
static int16_t Speed_Y = 0;

static uint8_t  A_SWStatus = 0;
static uint8_t  B_SWStatus = 0;



static int16_t AX_LastReading = 0;
static int16_t AY_LastReading = 0;
static int16_t BY_LastReading = 0;
static uint8_t  A_SWLastStatus = 0;
static uint8_t  B_SWLastStatus = 0;


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
  if(AnalogReading < ADC_OFFSET_MAX && AnalogReading > ADC_OFFSET_MIN)
  {
    AnalogReading = ZERO_ADC_READING;
  }
  AnalogReading = JoyStickController_MapReading(AnalogReading);         
  return AnalogReading;
}

int16_t JoyStickControllerA_GetYReading(void)
{
  #if LOY_STICK_C_SERIAL_DEBUG
  SERIAL_DEBUG.println("JoyStickApp-> Getting Controller A Y reading");
  #endif
  
  int16_t AnalogReading = analogRead(JOYSTICK_A_Y_AXIS_PIN);
  if(AnalogReading < ADC_OFFSET_MAX && AnalogReading > ADC_OFFSET_MIN)
  {
    AnalogReading = ZERO_ADC_READING;
  }
  
  AnalogReading = JoyStickController_MapReading(AnalogReading);             
  return AnalogReading;
}

uint8_t JoyStickControllerA_ReadSW(void)
{
  uint8_t ret = 0;
  uint8_t temp_sw_read = digitalRead(JOYSTICK_A_SW_PIN);
  
  if( temp_sw_read == HIGH && A_SWLastStatus == LOW)
  {
     
    A_SWStatus = !A_SWStatus;
    B_SWStatus = !B_SWStatus;
    ret = 1;

    #if LOY_STICK_C_SERIAL_DEBUG
    SERIAL_DEBUG.print("JoyStickApp->Controller A sw is changed to");
    SERIAL_DEBUG.println(A_SWLastStatus);
    #endif
  }
 
   A_SWLastStatus = temp_sw_read;
  
  return ret;
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
  if(AnalogReading < ADC_OFFSET_MAX && AnalogReading > ADC_OFFSET_MIN)
  {
    AnalogReading = ZERO_ADC_READING;
  }
  AnalogReading = JoyStickController_MapReading(AnalogReading);         
  return AnalogReading;
}

int16_t JoyStickControllerB_GetYReading(void)
{
  #if LOY_STICK_C_SERIAL_DEBUG
  SERIAL_DEBUG.println("JoyStickApp-> Getting Controller B Y reading");
  #endif
  
  int16_t AnalogReading = analogRead(JOYSTICK_B_Y_AXIS_PIN);
  if(AnalogReading < ADC_OFFSET_MAX && AnalogReading > ADC_OFFSET_MIN)
  {
    AnalogReading = ZERO_ADC_READING;
  }
  AnalogReading = JoyStickController_MapReading(AnalogReading);             
  return AnalogReading;
}

uint8_t JoyStickControllerB_ReadSW(void)
{
  uint8_t ret = 0;
  uint8_t temp_sw_read = digitalRead(JOYSTICK_A_SW_PIN);
  
  if( temp_sw_read == HIGH && A_SWLastStatus == LOW)
  {
     

    ret = 1;

    #if LOY_STICK_C_SERIAL_DEBUG
    SERIAL_DEBUG.print("JoyStickApp->Controller A sw is changed to");
    SERIAL_DEBUG.println(A_SWLastStatus);
    #endif
  }
 
   A_SWLastStatus = temp_sw_read;
  
  return ret;
}

void JoyStickController_Setup(void)
{
    JoyStickControllerA_Setup();
    JoyStickControllerB_Setup();
}



uint8_t  JoyStickController_Loop(void)
{
  uint8_t ret = 0;
  int16_t AX_Reading = JoyStickControllerA_GetXReading(); // -255 ~ 255
  int16_t AY_Reading = JoyStickControllerA_GetYReading(); // -255 ~ 255
  int16_t BY_Reading = JoyStickControllerB_GetYReading(); // -255 ~ 255

if((AX_Reading!= AX_LastReading)||(AY_Reading!= AY_LastReading)||(BY_Reading != BY_LastReading))
 
 {
   ret = 1;
   AX_LastReading = AX_Reading;  
   AY_LastReading = AY_Reading;
   BY_LastReading = BY_Reading ;

  if(AY_Reading < ZERO_MAP_READING )
  {
      Dir_X = MOVE_FORWARD;
      Speed_X = abs(AY_Reading);
  }

  else if(AY_Reading > ZERO_MAP_READING)
  {
      Dir_X = MOVE_BACKWARD;
      Speed_X = abs(AY_Reading);
  }
  else if(AX_Reading < ZERO_MAP_READING)
  {
      Dir_X = MOVE_LEFT;
      Speed_X = abs(AX_Reading);
  }

  else if(AX_Reading > ZERO_MAP_READING)
  {
      Dir_X = MOVE_RIGHT;
      Speed_X = abs(AX_Reading);
  }
  else
  {
      Dir_X = MOVE_STOP;
      Speed_X = 0;
  }
  
  if(BY_Reading < ZERO_MAP_READING )
  {
    Dir_Y = MOVE_UP;
    Speed_Y = abs(BY_Reading);
  }
  else if(BY_Reading > ZERO_MAP_READING)
  {
    Dir_Y = MOVE_DOWN;
    Speed_Y = abs(BY_Reading);
      
  }
  else
  {
      Dir_Y = MOVE_STOP;
      Speed_Y = 0;
  }

  #if LOY_STICK_C_SERIAL_DEBUG 
  SERIAL_DEBUG.print ("JoyStickApp->Controller Dir_X: ");
  SERIAL_DEBUG.print ((char)Dir_X);
  SERIAL_DEBUG.print (" Controller Speed_X: ");
  SERIAL_DEBUG.println (Speed_X);
  #endif


 }

  uint8_t A_SWret = JoyStickControllerA_ReadSW();

  if(A_SWret == 1) ret = 1;
  

  return ret;
}

uint8_t JoyStickController_MotorXGetDir(void)
{
  return Dir_X;
}

int16_t JoyStickController_MotorXGetSpd(void)
{
  return Speed_X;
}


uint8_t JoyStickController_MotorYGetDir(void)
{
  return Dir_Y;
}

int16_t JoyStickController_MotorYGetSpd(void)
{
  return Speed_Y;
}


uint8_t JoyStickControllerA_GetSW(void)
{
   return A_SWStatus;
}
uint8_t JoyStickControllerB_GetSW(void)
{
 return B_SWStatus;
}
