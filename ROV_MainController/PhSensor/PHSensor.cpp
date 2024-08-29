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

void PhSensor_Loop(void)
{
   if((millis()-phLastReadTime)>PH_READ_TIME)
   {
    
    #if DEBUG_PH
    SERIAL_DEBUG.println("PH_SEN->Reading PH sensor");
    #endif
    //Reset Time variable
    phLastReadTime = millis();

    phVoltage = (analogRead(PH_SENSOR_PIN)/PH_ADC_RESOLUTION)*(PH_MAX_VOLTE);
    phValue   =  ph.readPH(phVoltage,phTemperature);


    #if DEBUG_PH
    SERIAL_DEBUG.print("PH_SEN->V=");
    SERIAL_DEBUG.println(phVoltage);

    SERIAL_DEBUG.print("PH_SEN->PH=");
    SERIAL_DEBUG.println(phValue);
    #endif
    
    
   }
  
}

float PhSensor_GetRead(void)
{
  return phValue;
}
