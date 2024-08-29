
#ifndef MQTT_APP_H_
#define MQTT_APP_H_

 
void MQTT_App_setup();
void MQTT_App_loop();
uint8_t MQTT_App_MotorDirGet(void);
int16_t MQTT_App_MotorSpdGet(void);
uint8_t MQTT_App_LightRGet(void);
uint8_t MQTT_App_LightLGet(void);

// H,T,D,Ph
void MQTT_App_TempSet(float newTemp);
void MQTT_App_HuSet(float newHu);
void MQTT_App_PhSet(float newPh);
// void MQTT_App_DepSet(float newDep);


#endif /* MQTT_APP_H_ */
