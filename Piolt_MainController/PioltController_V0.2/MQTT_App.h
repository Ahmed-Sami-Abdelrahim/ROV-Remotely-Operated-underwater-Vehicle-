
#ifndef MQTT_APP_H_
#define MQTT_APP_H_

 
void MQTT_App_setup();
void MQTT_App_loop();

void MQTT_App_MotorXDirSet(uint8_t newDir);
void MQTT_App_MotorXSpdSet(int16_t newSpd);

void MQTT_App_MotorYDirSet(uint8_t newDir);
void MQTT_App_MotorYSpdSet(int16_t newSpd);

void MQTT_App_LightRSet(uint8_t newState);
void MQTT_App_LightLSet(uint8_t newState);

#endif /* MQTT_APP_H_ */
