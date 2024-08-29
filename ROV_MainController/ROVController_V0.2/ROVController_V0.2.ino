#include "Common.h"
#include "MQTT_App.h"
#include "MotorControl.h"
#include "LightsControl.h"
#include "DHT22Sensor.h"
#include "PHSensor.h"
#define  ROV_APP_SERIAL_DEBUG 1
void setup()
{
 SERIAL_DEBUG.begin(SERIAL_DEBUG_BAUDRATE);

 MotorControl_Setup();
 LigtControl_Setup();
 DHT22Sensor_Setup();
 PhSensor_Setup();
 MQTT_App_setup();

}

void loop() 
{

  if(PhSensor_Loop())
  {
    float NewPhReading = PhSensor_GetRead();
    MQTT_App_PhSet(NewPhReading);
  }

  if(DHT22Sensor_Loop())
  {
    float NewHu = DHT22Sensor_HumidityGetRead();
    float NewTemp = DHT22Sensor_TempratureGetRead();
    MQTT_App_HuSet(NewHu);
    MQTT_App_TempSet(NewTemp);
  }
//
  if(MQTT_App_loop())
  {
    uint8_t NewDir_X = MQTT_App_MotorXDirGet();
    int16_t NewSpd_X = MQTT_App_MotorXSpdGet();
    uint8_t NewDir_Y = MQTT_App_MotorYDirGet();
    int16_t NewSpd_Y = MQTT_App_MotorYSpdGet();
    uint8_t NewLightR = MQTT_App_LightRGet();
    uint8_t NewLightL = MQTT_App_LightLGet();


    #if ROV_APP_SERIAL_DEBUG
    SERIAL_DEBUG.print("PIOLT_AP-> New Dir X Reading ");
    SERIAL_DEBUG.println((char)NewDir_X);
    
    SERIAL_DEBUG.print("PIOLT_AP-> New Spd X Reading ");
    SERIAL_DEBUG.println(NewSpd_X);


    SERIAL_DEBUG.print("PIOLT_AP-> New Dir Y Reading ");
    SERIAL_DEBUG.println((char)NewDir_Y);
    
    SERIAL_DEBUG.print("PIOLT_AP-> New Spd Y Reading ");
    SERIAL_DEBUG.println(NewSpd_Y);
    
    SERIAL_DEBUG.print("PIOLT_AP-> New A SW Reading ");
    SERIAL_DEBUG.println(NewLightR);

    SERIAL_DEBUG.print("PIOLT_AP-> New B SW Reading ");
    SERIAL_DEBUG.println(NewLightL);
    
    #endif

    
    MotorControl_UpdateMotorXStatus(NewDir_X,NewSpd_X);
    MotorControl_UpdateMotorYStatus(NewDir_Y,NewSpd_Y);
    LigtControl_LightRSet(NewLightR);
    LigtControl_LightLSet(NewLightL);
  }


 MotorControl_Loop();
 LigtControl_Loop();

  delay(600);
}
