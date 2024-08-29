#include "Common.h"
#include "MQTT_App.h"

void setup() 
{
  // put your setup code here, to run once:
  SERIAL_DEBUG.begin(SERIAL_DEBUG_BAUDRATE);
  MQTT_App_setup();
}

void loop()
{
  // put your main code here, to run repeatedly:
  MQTT_App_loop();
}
