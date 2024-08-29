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

void MQTT_SubscrbersWaitAndRead(void);
void MQTT_Publisher(void);



/*Global static Varibles*/
byte mac[] = {0xDD, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

 

static uint8_t motorLastDir = MOVE_STOP;
static int16_t motorLastSpd = 0;
static uint8_t LightLastR = 0;
static uint8_t LightLastL = 0;

static uint8_t motorDir = MOVE_STOP;
static int16_t motorSpd = 0;
static uint8_t c = 0;
static uint8_t LightL = 0;
static uint8_t LightR = 0;

/*Set up the ethernet client*/
EthernetClient client;
Adafruit_MQTT_Client mqtt(&client, BROKER_SERVER, BROKER_SERVERPORT, BROKER_USERNAME, BROKER_KEY);

/*Publishers variables*/
Adafruit_MQTT_Publish motor_ctrl_dir_pub    = Adafruit_MQTT_Publish(&mqtt,MOTOR_CTRL_DIR_TOPIC);
Adafruit_MQTT_Publish motor_ctrl_spd_pub    = Adafruit_MQTT_Publish(&mqtt,MOTOR_CTRL_SPD_TOPIC);
Adafruit_MQTT_Publish light_ctrl_r_dir_pub  = Adafruit_MQTT_Publish(&mqtt,MOTOR_CTRL_LIGHT_R_TOPIC);
Adafruit_MQTT_Publish light_ctrl_l_dir_pub  = Adafruit_MQTT_Publish(&mqtt,MOTOR_CTRL_LIGHT_L_TOPIC);

/*Subscribers variables*/
 

/*Timeing variables*/
 
 




/*Function Impelementation*/


static void MQTT_App_MotorDirPublish(void)
{
  if(motorDir != motorLastDir)
  {
    motorLastDir = motorDir;
    char motorDirString[10];
    memset(motorDirString,0,10);
    sprintf(motorDirString,"%c",motorLastDir);
    
    if (motor_ctrl_dir_pub.publish(motorDirString) == 0)
    {
      #if MQTT_APP_SERIAL_DEBUG   
      SERIAL_DEBUG.println(F("MQTT_App->Publishing Motor dir Failed"));
      #endif
    } 
    else 
    {
      #if MQTT_APP_SERIAL_DEBUG 
      SERIAL_DEBUG.println(F("MQTT_App->Publishing Motor dir OK"));
      #endif
    }

  }
  
}


static void MQTT_App_MotorSpdPublish(void)
{
  if(motorSpd != motorLastSpd)
  {
      motorLastSpd = motorSpd;
      char motorSpdString[10];
      memset(motorSpdString,0,10);
      sprintf(motorSpdString,"%d",motorLastSpd);
      
    if (motor_ctrl_spd_pub.publish(motorSpdString) == 0)
    {
      #if MQTT_APP_SERIAL_DEBUG   
      SERIAL_DEBUG.println(F("MQTT_App->Publishing Motor spd Failed"));
      #endif
    } 
    else 
    {
      #if MQTT_APP_SERIAL_DEBUG 
      SERIAL_DEBUG.println(F("MQTT_App->Publishing Motor spd OK"));
      #endif
    }
  
  }
  
}


static void MQTT_App_LightRPublish(void)
{
  if(LightR != LightLastR)
  {
      LightLastR = LightR;
 
    if (light_ctrl_r_dir_pub.publish((uint32_t)LightLastR) == 0)
    {
      #if MQTT_APP_SERIAL_DEBUG   
      SERIAL_DEBUG.println(F("MQTT_App->Publishing Light R Failed"));
      #endif
    } 
    else 
    {
      #if MQTT_APP_SERIAL_DEBUG 
      SERIAL_DEBUG.println(F("MQTT_App->Publishing Light R OK"));
      #endif
    }
  
  }
  
}



static void MQTT_App_LightLPublish(void)
{
  if(LightL != LightLastL)
  {
      LightLastL = LightL;
 
    if (light_ctrl_l_dir_pub.publish((uint32_t)LightLastL) == 0)
    {
      #if MQTT_APP_SERIAL_DEBUG   
      SERIAL_DEBUG.println(F("MQTT_App->Publishing Light L Failed"));
      #endif
    } 
    else 
    {
      #if MQTT_APP_SERIAL_DEBUG 
      SERIAL_DEBUG.println(F("MQTT_App->Publishing Light L OK"));
      #endif
    }
  
  }
  
}



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

 
void MQTT_App_loop() 
{

  #if 0
  SERIAL_DEBUG.println(F("Enter MQTT app Connect"));
  #endif
  /*Confirm that the HW is connected to Broker*/
  MQTT_connect();
  
  /*Wait and Read Incoming data if avilable*/
  #if 0
  SERIAL_DEBUG.println(F("MQTT_App->Enter MQTT app Wait"));
  #endif
  MQTT_SubscrbersWaitAndRead();
  MQTT_Publisher();
  MQTT_Ping();  
}


void MQTT_App_MotorDirSet(uint8_t newDir)
{
   motorDir = newDir;
}

void MQTT_App_MotorSpdSet(int16_t newSpd)
{
  motorSpd = newSpd;
}

void MQTT_App_LightRSet(uint8_t newState)
{
   LightR = newState;
}

void MQTT_App_LightLSet(uint8_t newState)
{
   LightL = newState;
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



void MQTT_SubscrbersWaitAndRead(void)
{
 
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
 
}


void MQTT_Publisher(void)
{

    //read sensors 

    #if 0
     SERIAL_DEBUG.println(F("Enter MQTT app Publish"));
    #endif

    MQTT_App_MotorDirPublish();
    MQTT_App_MotorSpdPublish();
    MQTT_App_LightRPublish();
    MQTT_App_LightLPublish();


}
