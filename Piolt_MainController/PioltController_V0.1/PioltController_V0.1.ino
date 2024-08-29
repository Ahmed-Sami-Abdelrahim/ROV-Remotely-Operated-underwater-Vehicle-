
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
    uint8_t NewDir = JoyStickController_GetDir();
    int16_t NewSpd = JoyStickController_GetSpd();
    uint8_t NewASWStatus = JoyStickControllerA_GetSW();
    uint8_t NewBSWStatus = JoyStickControllerB_GetSW();

    #if PIOLT_APP_SERIAL_DEBUG
    SERIAL_DEBUG.print("PIOLT_AP-> New Dir Reading ");
    SERIAL_DEBUG.println((char)NewDir);
    
    SERIAL_DEBUG.print("PIOLT_AP-> New Spd Reading ");
    SERIAL_DEBUG.println(NewSpd);
    
    SERIAL_DEBUG.print("PIOLT_AP-> New A SW Reading ");
    SERIAL_DEBUG.println(NewASWStatus);

    SERIAL_DEBUG.print("PIOLT_AP-> New B SW Reading ");
    SERIAL_DEBUG.println(NewBSWStatus);
    
    #endif

    MQTT_App_MotorDirSet(NewDir);
    MQTT_App_MotorSpdSet(NewSpd);
    MQTT_App_LightRSet(NewASWStatus);
    MQTT_App_LightLSet(NewBSWStatus);
  }

  MQTT_App_loop();
  delay(500);
}
