#include "Common.h"
#include "PHSensor.h"

void setup() 
{
  // put your setup code here, to run once:
  SERIAL_DEBUG.begin(SERIAL_DEBUG_BAUDRATE);
  PhSensor_Setup();
}

void loop()
{
  // put your main code here, to run repeatedly:
  PhSensor_Loop();
}
