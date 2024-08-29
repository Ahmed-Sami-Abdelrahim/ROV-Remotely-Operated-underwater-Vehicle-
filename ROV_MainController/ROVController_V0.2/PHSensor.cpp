#include <Arduino.h>
#include "PHSensor_cfg.h"
#include "Common.h"
#include "DFRobot_PH.h"

static float phVoltage = 0.0;
static float phValue = 0.0;
static float phTemperature = PH_SENSOR_CAL_TEMP;
static uint32_t phLastReadTime = 0;

DFRobot_PH ph;

void PhSensor_Setup(void)
{
  pinMode(PH_SENSOR_PIN,INPUT);
  ph.begin();
}

uint8_t PhSensor_Loop(void)
{ 
   uint8_t ret = 0;
   if((millis()-phLastReadTime)>PH_READ_TIME)
   {

    ret = 1;
    #if DEBUG_PH
    SERIAL_DEBUG.println("PH_SEN->Reading PH sensor");
    #endif
    //Reset Time variable
    phLastReadTime = millis();

    phVoltage = (analogRead(PH_SENSOR_PIN)/PH_ADC_RESOLUTION)*(PH_MAX_VOLTE);
  
    phValue   =  ph.readPH(phVoltage,phTemperature);
//    phValue   = phValue/6;
//    phValue   = 3.5 *phValue; 


    #if DEBUG_PH
    SERIAL_DEBUG.print("PH_SEN->V=");
    SERIAL_DEBUG.println(phVoltage);

    SERIAL_DEBUG.print("PH_SEN->PH=");
    SERIAL_DEBUG.println(phValue);
    #endif
    
    
   }
  return ret;
}

float PhSensor_GetRead(void)
{
  return phValue;
}
