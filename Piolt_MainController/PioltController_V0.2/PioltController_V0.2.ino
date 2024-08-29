
#include "Common.h"
#include "MQTT_App.h"
#include "JoyStickController.h"
#define PIOLT_APP_SERIAL_DEBUG 1 




void setup()
{
  SERIAL_DEBUG.begin(SERIAL_DEBUG_BAUDRATE);
  JoyStickController_Setup();
  MQTT_App_setup();
}

void loop()
{
  if(JoyStickController_Loop())
  {
    uint8_t NewDir_X = JoyStickController_MotorXGetDir();
    int16_t NewSpd_X = JoyStickController_MotorXGetSpd();
    
    uint8_t NewDir_Y = JoyStickController_MotorYGetDir();
    int16_t NewSpd_Y = JoyStickController_MotorYGetSpd();
    
    uint8_t NewASWStatus = JoyStickControllerA_GetSW();
    uint8_t NewBSWStatus = JoyStickControllerB_GetSW();

    #if PIOLT_APP_SERIAL_DEBUG
    SERIAL_DEBUG.print("PIOLT_AP-> New  Dir_X Reading ");
    SERIAL_DEBUG.println((char)NewDir_X);
    
    SERIAL_DEBUG.print("PIOLT_AP-> New Spd X Reading ");
    SERIAL_DEBUG.println(NewSpd_X);
    
    SERIAL_DEBUG.print("PIOLT_AP-> New A SW Reading ");
    SERIAL_DEBUG.println(NewASWStatus);

    SERIAL_DEBUG.print("PIOLT_AP-> New B SW Reading ");
    SERIAL_DEBUG.println(NewBSWStatus);
    
    #endif

    MQTT_App_MotorXDirSet(NewDir_X);
    MQTT_App_MotorXSpdSet(NewSpd_X);
    
    MQTT_App_MotorYDirSet(NewDir_Y);
    MQTT_App_MotorYSpdSet(NewSpd_Y);
    
    MQTT_App_LightRSet(NewASWStatus);
    MQTT_App_LightLSet(NewBSWStatus);
  }

  MQTT_App_loop();
  delay(500);
}
