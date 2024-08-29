#include "Common.h"
#include "DHT22Sensor.h"

void setup()
{
  // put your setup code here, to run once:
  SERIAL_DEBUG.begin(SERIAL_DEBUG_BAUDRATE);
  DHT22Sensor_Setup();
}

void loop() 
{
  // put your main code here, to run repeatedly:
  DHT22Sensor_Loop();
}
