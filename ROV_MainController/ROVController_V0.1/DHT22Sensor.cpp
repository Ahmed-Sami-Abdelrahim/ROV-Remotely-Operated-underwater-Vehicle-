#include <Arduino.h>
#include "DHT22Sensor.h"
#include <DHT.h>
#include "DHT22Sensor_cfg.h"
#include "Common.h"

volatile int32_t LastDHTReadingtime = 0;
static float dhtHumedity = 0.0;
static float dhtTemprature = 0.0;

DHT dht(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);



void DHT22Sensor_Setup(void)
{
  dht.begin();
}


uint8_t DHT22Sensor_Loop(void)
{
  uint8_t ret = 0;
  if((millis() - LastDHTReadingtime) > DHT_READING_TIME)
  {
    ret = 1;
    #if DEBUG_DHT
    SERIAL_DEBUG.println("DHT_SEN->DHT sensor");
    #endif
    
    LastDHTReadingtime = millis();
    dhtHumedity = dht.readHumidity()-DHT_OFFSET;
    // Read temperature as Celsius (the default)*/
    dhtTemprature = dht.readTemperature();


    #if DEBUG_DHT
    SERIAL_DEBUG.print("DHT_SEN->Humidity=");
    SERIAL_DEBUG.println(dhtHumedity);
    
    SERIAL_DEBUG.print("DHT_SEN->Temperature=");
    SERIAL_DEBUG.println(dhtTemprature);
    #endif
    
  }
  return ret;
}


float DHT22Sensor_HumidityGetRead(void)
{
  return dhtHumedity;
}

float DHT22Sensor_TempratureGetRead(void)
{
  return dhtTemprature;
}
