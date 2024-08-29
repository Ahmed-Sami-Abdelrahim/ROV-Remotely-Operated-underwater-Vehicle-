#include "Common.h"
#include "JoyStickController.h"

void setup() 
{
  SERIAL_DEBUG.begin(SERIAL_DEBUG_BAUDRATE);
  JoyStickController_Setup();

}

void loop()
{

  JoyStickController_Loop();
  JoyStickControllerA_GetSW();
  JoyStickControllerB_GetSW();
  delay(500);
}
