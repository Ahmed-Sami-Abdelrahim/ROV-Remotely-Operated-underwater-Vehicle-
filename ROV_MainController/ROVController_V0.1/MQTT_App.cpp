#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <Dns.h>
#include <Dhcp.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Common.h"
#include "MQTT_cfg.h"





/*User Define functions declerarion*/
void MQTT_connect(void);
void MQTT_Ping(void);
void MQTT_AddSubscribers(void);

uint8_t MQTT_SubscrbersWaitAndRead(void);
void MQTT_Publisher(void);



/*Global static Varibles*/
byte mac[] = {0xDA, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

static float phReading_pub_val = 0.0;
static float temperatureReading_pub_val = 0.0;
static float humidityReading_pub_val = 0.0;

static uint8_t motorDir = MOVE_STOP;
static int16_t motorSpd = 0;
static uint8_t LightR = 0;
static uint8_t LightL = 0;

/*Set up the ethernet client*/
EthernetClient client;
Adafruit_MQTT_Client mqtt(&client, BROKER_SERVER, BROKER_SERVERPORT, BROKER_USERNAME, BROKER_KEY);

/*Publishers variables*/
Adafruit_MQTT_Publish phReading_pub    = Adafruit_MQTT_Publish(&mqtt,PH_TOPIC);
Adafruit_MQTT_Publish temperatureReading_pub = Adafruit_MQTT_Publish(&mqtt,TEMP_TOPIC);
Adafruit_MQTT_Publish humidityReading_pub    = Adafruit_MQTT_Publish(&mqtt,HU_TOPIC);

/*Subscribers variables*/
Adafruit_MQTT_Subscribe motor_ctrl_dir_sub = Adafruit_MQTT_Subscribe(&mqtt,MOTOR_CTRL_DIR_TOPIC);
Adafruit_MQTT_Subscribe motor_ctrl_spd_sub = Adafruit_MQTT_Subscribe(&mqtt,MOTOR_CTRL_SPD_TOPIC);
Adafruit_MQTT_Subscribe light_ctrl_r_sub = Adafruit_MQTT_Subscribe(&mqtt,MOTOR_CTRL_LIGHT_R_TOPIC);
Adafruit_MQTT_Subscribe light_ctrl_l_sub = Adafruit_MQTT_Subscribe(&mqtt,MOTOR_CTRL_LIGHT_L_TOPIC);

/*Timeing variables*/
volatile int32_t LastPublishtime = 0;
 




/*Function Impelementation*/

void MQTT_App_setup() 
{

  
  #if MQTT_APP_SERIAL_DEBUG
  SERIAL_DEBUG.println(F("MQTT_App->MQTT app setting up"));
  SERIAL_DEBUG.println(F("MQTT_App->Init the Client..."));
  #endif
  /*Initialise the Client*/
  Ethernet.begin(mac);
  /*give the ethernet a second to initialize*/
  delay(1000); 
  /*register subsrcibers*/
  MQTT_AddSubscribers();
  
}

 
uint8_t  MQTT_App_loop() 
{
  uint8_t ret = 0;
  #if 0
  SERIAL_DEBUG.println(F("Enter MQTT app Connect"));
  #endif
  /*Confirm that the HW is connected to Broker*/
  MQTT_connect();
  
  /*Wait and Read Incoming data if avilable*/
  #if 0
  SERIAL_DEBUG.println(F("MQTT_App->Enter MQTT app Wait"));
  #endif
  ret = MQTT_SubscrbersWaitAndRead();
  /*Check Time to Pubish*/
 
  if((millis()-LastPublishtime)> PUB_TIME)
  {

    LastPublishtime = millis();
    MQTT_Publisher();
  }
  MQTT_Ping();  

  return ret;
}


uint8_t MQTT_App_MotorDirGet(void)
{
  return motorDir;
}

int16_t MQTT_App_MotorSpdGet(void)
{
  return motorSpd;
}


uint8_t MQTT_App_LightRGet(void)
{
  return LightR;
}
uint8_t MQTT_App_LightLGet(void)
{
  return LightL;
}


/*User Define functions implementation*/


void MQTT_connect(void) 
{
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) 
  {
    return;
  }
  
  #if MQTT_APP_SERIAL_DEBUG
  SERIAL_DEBUG.print("MQTT_App->Connecting to MQTT... ");
  #endif
  
  while ((ret = mqtt.connect()) != 0) 
  {    
      #if MQTT_APP_SERIAL_DEBUG
      // connect will return 0 for connected
      SERIAL_DEBUG.println(mqtt.connectErrorString(ret));
      SERIAL_DEBUG.println("Retrying MQTT connection in 5 seconds...");
      #endif
      
      mqtt.disconnect();
      // wait 5 seconds
      //delay(5000);  

  }

  #if MQTT_APP_SERIAL_DEBUG
  SERIAL_DEBUG.println("MQTT Connected!");
  #endif
}



uint8_t  MQTT_SubscrbersWaitAndRead(void)
{
  uint8_t ret = 0;
  // this is our 'wait for incoming subscription packets' busy subloop
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(200))) 
  {
     ret = 1;
    if (subscription == &motor_ctrl_dir_sub)
    {
      #if MQTT_APP_SERIAL_DEBUG
      SERIAL_DEBUG.print(F("MQTT_App-> Motor Dir Got: "));
      SERIAL_DEBUG.println((char *)motor_ctrl_dir_sub.lastread);
      #endif
      if(MOVE_FORWARD == motor_ctrl_dir_sub.lastread[0])
      {
        motorDir = MOVE_FORWARD;
      }
      else if(MOVE_BACKWARD == motor_ctrl_dir_sub.lastread[0])
      {
        motorDir = MOVE_BACKWARD;
      }
      else if(MOVE_RIGHT == motor_ctrl_dir_sub.lastread[0])
      {
        motorDir = MOVE_RIGHT;
      }
      else if(MOVE_LEFT == motor_ctrl_dir_sub.lastread[0])
      {
        motorDir = MOVE_LEFT;
      }
      else if(MOVE_UP == motor_ctrl_dir_sub.lastread[0])
      {
        motorDir = MOVE_UP;
      }
      else if(MOVE_DOWN == motor_ctrl_dir_sub.lastread[0])
      {
        motorDir = MOVE_DOWN;
      }
      else
      {
        motorDir = MOVE_STOP;
      }
      
    }


    if (subscription == &motor_ctrl_spd_sub)
    {
      motorSpd = atoi((char *)motor_ctrl_spd_sub.lastread);
      
      #if MQTT_APP_SERIAL_DEBUG
      SERIAL_DEBUG.print(F("MQTT_App-> Motor Speed Got: "));
      ///SERIAL_DEBUG.print((char *)motor_ctrl_spd_sub.lastread);
      SERIAL_DEBUG.println(motorSpd);
      #endif

     
      
    }

 
    if (subscription == &light_ctrl_r_sub)
    {
      LightR = atoi((char *)light_ctrl_r_sub.lastread);
      
      #if MQTT_APP_SERIAL_DEBUG
      SERIAL_DEBUG.print(F("MQTT_App-> Light R Got: "));
      
      SERIAL_DEBUG.println(LightR);
      #endif
      
    }

    if (subscription == &light_ctrl_l_sub)
    {
      LightL = atoi((char *)light_ctrl_l_sub.lastread);
      
      #if MQTT_APP_SERIAL_DEBUG
      SERIAL_DEBUG.print(F("MQTT_App-> Light L Got: "));
      
      SERIAL_DEBUG.println(LightL);
      #endif
      
    }
    
  }

  return ret;
}



void MQTT_Ping(void)
{
    // ping the server to keep the mqtt connection alive
  if(mqtt.ping()) 
  {
    
  }
  else
  {
    #if MQTT_APP_SERIAL_DEBUG
    SERIAL_DEBUG.println("MQTT_App->MQTT Ping faild!");
    #endif
    mqtt.disconnect();
  }

}


void MQTT_AddSubscribers(void)
{
  mqtt.subscribe(&motor_ctrl_dir_sub);
  mqtt.subscribe(&motor_ctrl_spd_sub);
  mqtt.subscribe(&light_ctrl_r_sub);
  mqtt.subscribe(&light_ctrl_l_sub);
}


void MQTT_Publisher(void)
{

  //read sensors 

    #if MQTT_APP_SERIAL_DEBUG
     SERIAL_DEBUG.println(F("Enter MQTT app Publish"));
    #endif

    if (phReading_pub.publish(phReading_pub_val) == 0)
    {
      #if MQTT_APP_SERIAL_DEBUG   
      SERIAL_DEBUG.println(F("MQTT_App->Publishing Current Reading Failed"));
      #endif
    } 
    else 
    {
      #if MQTT_APP_SERIAL_DEBUG 
      SERIAL_DEBUG.println(F("MQTT_App->Publishing PH Reading OK"));
      #endif
    }
  
  if (temperatureReading_pub.publish(temperatureReading_pub_val) == 0)
  {
    #if MQTT_APP_SERIAL_DEBUG 
    SERIAL_DEBUG.println(F("MQTT_App->Publishing temperature Reading Failed"));
    #endif
  } 
  else 
  {
    #if MQTT_APP_SERIAL_DEBUG 
    SERIAL_DEBUG.println(F("MQTT_App->Publishing temperature Reading OK"));
    #endif
  }
  
  if (humidityReading_pub.publish(humidityReading_pub_val) == 0)
  {
    #if MQTT_APP_SERIAL_DEBUG 
    SERIAL_DEBUG.println(F("MQTT_App->Publishing humidity Reading Failed"));
    #endif
  } 
  else 
  {
  #if MQTT_APP_SERIAL_DEBUG 
  SERIAL_DEBUG.println(F("MQTT_App->Publishing humidity Reading OK"));
  #endif
  }

}

void MQTT_App_TempSet(float newTemp)
{
  temperatureReading_pub_val = newTemp;
}
void MQTT_App_HuSet(float newHu)
{
   humidityReading_pub_val = newHu;
}
void MQTT_App_PhSet(float newPh)
{
   phReading_pub_val = newPh;
}
