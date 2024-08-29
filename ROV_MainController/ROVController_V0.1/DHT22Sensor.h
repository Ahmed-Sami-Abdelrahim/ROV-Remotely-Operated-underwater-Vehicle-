#ifndef _DHT22_SENSOR_MEGA_
#define _DHT22_SENSOR_MEGA_

void DHT22Sensor_Setup(void);
uint8_t DHT22Sensor_Loop(void);
float DHT22Sensor_HumidityGetRead(void);
float DHT22Sensor_TempratureGetRead(void);

#endif /*_DHT22_SENSOR_MEGA_*/
