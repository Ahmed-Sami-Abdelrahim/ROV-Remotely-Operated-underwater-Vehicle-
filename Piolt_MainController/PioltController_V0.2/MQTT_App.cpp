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
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xDE};

 

static uint8_t motorXLastDir = MOVE_STOP;
static int16_t motorXLastSpd = 0;

static uint8_t motorYLastDir = MOVE_STOP;
static int16_t motorYLastSpd = 0;

static uint8_t LightLastR = 0;
static uint8_t LightLastL = 0;

static uint8_t motorXDir = MOVE_STOP;
static int16_t motorXSpd = 0;

static uint8_t motorYDir = MOVE_STOP;
static int16_t motorYSpd = 0;

static uint8_t LightL = 0;
static uint8_t LightR = 0;

/*Set up the ethernet client*/
EthernetClient client;
Adafruit_MQTT_Client mqtt(&client, BROKER_SERVER, BROKER_SERVERPORT, BROKER_USERNAME, BROKER_KEY);

/*Publishers variables*/
Adafruit_MQTT_Publish motor_x_ctrl_dir_pub    = Adafruit_MQTT_Publish(&mqtt,MOTOR_X_CTRL_DIR_TOPIC);
Adafruit_MQTT_Publish motor_x_ctrl_spd_pub    = Adafruit_MQTT_Publish(&mqtt,MOTOR_X_CTRL_SPD_TOPIC);

Adafruit_MQTT_Publish motor_y_ctrl_dir_pub    = Adafruit_MQTT_Publish(&mqtt,MOTOR_Y_CTRL_DIR_TOPIC);
Adafruit_MQTT_Publish motor_y_ctrl_spd_pub    = Adafruit_MQTT_Publish(&mqtt,MOTOR_Y_CTRL_SPD_TOPIC);

Adafruit_MQTT_Publish light_ctrl_r_dir_pub  = Adafruit_MQTT_Publish(&mqtt,MOTOR_CTRL_LIGHT_R_TOPIC);
Adafruit_MQTT_Publish light_ctrl_l_dir_pub  = Adafruit_MQTT_Publish(&mqtt,MOTOR_CTRL_LIGHT_L_TOPIC);

/*Subscribers variables*/
 

/*Timeing variables*/
 
 




/*Function Impelementation*/


static void MQTT_App_motorXDirPublish(void)
{
  if(motorXDir != motorXLastDir)
  {
    motorXLastDir = motorXDir;
    char motorXDirString[10];
    memset(motorXDirString,0,10);
    sprintf(motorXDirString,"%c",motorXLastDir);
    
    if (motor_x_ctrl_dir_pub.publish(motorXDirString) == 0)
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


static void MQTT_App_motorXSpdPublish(void)
{
  if(motorXSpd != motorXLastSpd)
  {
      motorXLastSpd = motorXSpd;
      char motorXSpdString[10];
      memset(motorXSpdString,0,10);
      sprintf(motorXSpdString,"%d",motorXLastSpd);
      
    if (motor_x_ctrl_spd_pub.publish(motorXSpdString) == 0)
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




static void MQTT_App_motorYDirPublish(void)
{
  if(motorYDir != motorYLastDir)
  {
    motorYLastDir = motorYDir;
    char motorYDirString[10];
    memset(motorYDirString,0,10);
    sprintf(motorYDirString,"%c",motorYLastDir);
    
    if (motor_y_ctrl_dir_pub.publish(motorYDirString) == 0)
    {
      #if MQTT_APP_SERIAL_DEBUG   
      SERIAL_DEBUG.println(F("MQTT_App->Publishing Motor dir y Failed"));
      #endif
    } 
    else 
    {
      #if MQTT_APP_SERIAL_DEBUG 
      SERIAL_DEBUG.println(F("MQTT_App->Publishing Motor dir y OK"));
      #endif
    }

  }
  
}


static void MQTT_App_motorYSpdPublish(void)
{
  if(motorYSpd != motorYLastSpd)
  {
      motorYLastSpd = motorYSpd;
      char motorYSpdString[10];
      memset(motorYSpdString,0,10);
      sprintf(motorYSpdString,"%d",motorYLastSpd);
      
    if (motor_y_ctrl_spd_pub.publish(motorYSpdString) == 0)
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


void MQTT_App_MotorXDirSet(uint8_t newDir)
{
   motorXDir = newDir;
}

void MQTT_App_MotorXSpdSet(int16_t newSpd)
{
  motorXSpd = newSpd;
}


void MQTT_App_MotorYDirSet(uint8_t newDir)
{
   motorYDir = newDir;
}

void MQTT_App_MotorYSpdSet(int16_t newSpd)
{
  motorYSpd = newSpd;
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

    MQTT_App_motorXDirPublish();
    MQTT_App_motorXSpdPublish();
    MQTT_App_motorYDirPublish();
    MQTT_App_motorYSpdPublish();
    MQTT_App_LightRPublish();
    MQTT_App_LightLPublish();


}
