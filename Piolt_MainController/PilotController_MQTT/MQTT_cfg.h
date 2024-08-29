#ifndef MQTT_CFG_H_
#define MQTT_CFG_H_

 
#define MQTT_APP_SERIAL_DEBUG 1


/*Broker Settings*/
//#define BROKER_SERVER      "Broker.hivemq.com"
#define BROKER_SERVER        "192.168.1.254"
#define BROKER_SERVERPORT    1883
#define BROKER_USERNAME      "NULL"
#define BROKER_KEY           "NULL"



/*Topic Settings*/
/*Publishers*/
#define  MOTOR_CTRL_DIR_TOPIC     "ROV/MDIR"
#define  MOTOR_CTRL_SPD_TOPIC     "ROV/MSPD"
#define  MOTOR_CTRL_LIGHT_R_TOPIC "ROV/LR"
#define  MOTOR_CTRL_LIGHT_L_TOPIC "ROV/LL"

/*Subscribers*/

/*Application*/

#endif /* MQTT_CFG_H_ */
