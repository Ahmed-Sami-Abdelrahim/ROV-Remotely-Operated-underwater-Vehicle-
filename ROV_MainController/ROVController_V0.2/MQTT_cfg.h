#ifndef MQTT_CFG_H_
#define MQTT_CFG_H_

 
#define MQTT_APP_SERIAL_DEBUG 1


/*Broker Settings*/
//#define BROKER_SERVER      "Broker.hivemq.com"
#define BROKER_SERVER        "192.168.0.253"
#define BROKER_SERVERPORT    1883
#define BROKER_USERNAME      "NULL"
#define BROKER_KEY           "NULL"



/*Topic Settings*/
/*Publishers*/
#define  PH_TOPIC             "ROV/PH"
#define  TEMP_TOPIC           "ROV/TEMP"
#define  HU_TOPIC             "ROV/HU"
#define  DEPTH_TOPIC          "ROC/DEP"

/*Subscribers*/
//#define  MOTOR_X_CTRL_DIR_TOPIC     "ROV/MDIR"
//#define  MOTOR_X_CTRL_SPD_TOPIC     "ROV/MSPD"

#define  MOTOR_X_CTRL_DIR_TOPIC     "ROV/MDIR/X"
#define  MOTOR_X_CTRL_SPD_TOPIC     "ROV/MSPD/X"

#define  MOTOR_Y_CTRL_DIR_TOPIC     "ROV/MDIR/Y"
#define  MOTOR_Y_CTRL_SPD_TOPIC     "ROV/MSPD/Y"

#define  MOTOR_CTRL_LIGHT_R_TOPIC "ROV/LR"
#define  MOTOR_CTRL_LIGHT_L_TOPIC "ROV/LL"


/*Application*/
#define PUB_TIME (10000) //in MS

#endif /* MQTT_CFG_H_ */
