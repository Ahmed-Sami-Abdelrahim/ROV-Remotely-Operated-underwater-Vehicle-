#include <Arduino.h>
#include "CytronMotorDriver.h"
#include "Common.h"
#include "MotorControl_cfg.h"
 


CytronMD motorAX(PWM_DIR, MOTORAX_SPEED_PIN, MOTORAX_DIR_PIN);   
CytronMD motorBX(PWM_DIR, MOTORBX_SPEED_PIN, MOTORBX_DIR_PIN);  

CytronMD motorAY(PWM_DIR, MOTORAY_SPEED_PIN, MOTORAY_DIR_PIN);   
CytronMD motorBY(PWM_DIR, MOTORBY_SPEED_PIN, MOTORBY_DIR_PIN);  




static uint8_t MotortDirStatus = MOVE_STOP;
static int16_t MotortSpeed = 0;


/*Start Motor A X axis*/
static void MotorControl_MotorAX_Setup(int16_t Speed ){}

static void MotorControl_MotorAX_MoveForward(int16_t Speed )
{
  motorAX.setSpeed(Speed);
}

static void MotorControl_MotorAX_MoveBackward(int16_t Speed )
{
  motorAX.setSpeed(-Speed);
}

static void MotorControl_MotorAX_MoveStop(int16_t Speed )
{
  motorAX.setSpeed(0);
}
/*End Motor A X axis*/

/*Start Motor B X axis*/

static void MotorControl_MotorBX_Setup(int16_t Speed ){}

static void MotorControl_MotorBX_MoveForward(int16_t Speed )
{
   motorBX.setSpeed(Speed);
}

static void MotorControl_MotorBX_MoveBackward(int16_t Speed )
{
  motorBX.setSpeed(-Speed);
}

static void MotorControl_MotorBX_MoveStop(int16_t Speed )
{
  motorBX.setSpeed(0);
}
/*End Motor B X axis*/

/*Start Motor A Y axis*/
static void MotorControl_MotorAY_Setup(int16_t Speed ){}

static void MotorControl_MotorAY_MoveForward(int16_t Speed )
{
    motorAY.setSpeed(Speed);
}

static void MotorControl_MotorAY_MoveBackward(int16_t Speed )
{
    motorAY.setSpeed(Speed);
}

static void MotorControl_MotorAY_MoveStop(int16_t Speed )
{
    motorAY.setSpeed(0);
}
/*End Motor A Y axis*/

/*Start Motor B Y axis*/
static void MotorControl_MotorBY_Setup(int16_t Speed ){}

static void MotorControl_MotorBY_MoveForward(int16_t Speed )
{
  motorBY.setSpeed(Speed);
}

static void MotorControl_MotorBY_MoveBackward(int16_t Speed )
{
  motorBY.setSpeed(-Speed);
}

static void MotorControl_MotorBY_MoveStop(int16_t Speed )
{
   motorBY.setSpeed(0);
}
/*End Motor B Y axis*/




/*ROV Move Section*/
static void MotorControl_ROV_MoveForward(int16_t Speed)
{
  MotorControl_MotorAX_MoveForward(Speed);
  MotorControl_MotorBX_MoveForward(Speed);
}
static void MotorControl_ROV_MoveBackward(int16_t Speed)
{
  MotorControl_MotorAX_MoveBackward(Speed);
  MotorControl_MotorBX_MoveBackward(Speed);
}
static void MotorControl_ROV_MoveRight(int16_t Speed)
{
    MotorControl_MotorAX_MoveForward(Speed);
    MotorControl_MotorBX_MoveStop(0);
}
static void MotorControl_ROV_MoveLeft(int16_t Speed)
{
    MotorControl_MotorAX_MoveStop(0);
    MotorControl_MotorBX_MoveForward(Speed);
}
static void MotorControl_ROV_MoveUp(int16_t Speed)
{
  MotorControl_MotorAY_MoveForward(Speed);
  MotorControl_MotorBY_MoveForward(Speed);
}
static void MotorControl_ROV_MoveDown(int16_t Speed)
{
  MotorControl_MotorAY_MoveBackward(Speed);
  MotorControl_MotorBY_MoveBackward(Speed);
}

static void MotorControl_ROV_MoveStop(int16_t Speed)
{
  MotorControl_MotorAX_MoveStop( 0 );
  MotorControl_MotorBX_MoveStop( 0 );
  MotorControl_MotorAY_MoveStop( 0 );
  MotorControl_MotorBY_MoveStop( 0 );
}

static void MotorControl_ROV_X_MoveStop(int16_t Speed)
{
  MotorControl_MotorAX_MoveStop( 0 );
  MotorControl_MotorBX_MoveStop( 0 );
}

static void MotorControl_ROV_Y_MoveStop(int16_t Speed)
{
  MotorControl_MotorAY_MoveStop( 0 );
  MotorControl_MotorBY_MoveStop( 0 );
}


void MotorControl_UpdateStatus(uint8_t MotorDir,int16_t Speed)
{
  MotortDirStatus = MotorDir;
  MotortSpeed = Speed;
}


void MotorControl_Setup(void)
{
//  MotorControl_MotorBY_Setup(MOTORAX_DIR_PIN,MOTORAX_SPEED_PIN);
//  MotorControl_MotorBY_Setup(MOTORBX_DIR_PIN,MOTORBX_SPEED_PIN);
//  MotorControl_MotorBY_Setup(MOTORAY_DIR_PIN,MOTORAY_SPEED_PIN);
//  MotorControl_MotorBY_Setup(MOTORBY_DIR_PIN,MOTORBY_SPEED_PIN);
}




void MotorControl_Loop(void)
{
 
    switch(MotortDirStatus)
    {
      case MOVE_FORWARD   :
                    #if MOTOR_APP_SERIAL_DEBUG
                    SERIAL_DEBUG.println("MotorApp-> Moving MOVE_FORWARD");
                    #endif
                    MotorControl_ROV_Y_MoveStop(0);
                    MotorControl_ROV_MoveForward(MotortSpeed);
                    break;
                    
      case MOVE_BACKWARD   :
                    #if MOTOR_APP_SERIAL_DEBUG
                    SERIAL_DEBUG.println("MotorApp-> Moving MOVE_BACKWARD");
                    #endif
                    MotorControl_ROV_Y_MoveStop(0);
                    MotorControl_ROV_MoveBackward(MotortSpeed);
                    break; 
                                             
      case MOVE_LEFT   :
                    #if MOTOR_APP_SERIAL_DEBUG
                    SERIAL_DEBUG.println("MotorApp-> Moving MOVE_LEFT");
                    #endif
                    MotorControl_ROV_Y_MoveStop(0);
                    MotorControl_ROV_MoveLeft(MotortSpeed);
                    break;
                    
      case MOVE_RIGHT : 
                    #if MOTOR_APP_SERIAL_DEBUG
                    SERIAL_DEBUG.println("MotorApp-> Moving MOVE_RIGHT");
                    #endif
                    MotorControl_ROV_Y_MoveStop(0);
                    MotorControl_ROV_MoveRight(MotortSpeed);
                    break;
                    
      case MOVE_UP    : 
                    #if MOTOR_APP_SERIAL_DEBUG
                    SERIAL_DEBUG.println("MotorApp-> Moving MOVE_UP");
                    #endif
                    MotorControl_ROV_X_MoveStop(0);
                    MotorControl_ROV_MoveUp(MotortSpeed);
                    break;
                    
      case MOVE_DOWN  : 
                    #if MOTOR_APP_SERIAL_DEBUG
                    SERIAL_DEBUG.println("MotorApp-> Moving MOVE_DOWN");
                    #endif
                    MotorControl_ROV_X_MoveStop(0);
                    MotorControl_ROV_MoveDown(MotortSpeed);
                    break;
                    
      case MOVE_STOP  :  
      default    : 
                    #if 0
                    SERIAL_DEBUG.println("MotorApp-> Moving stop");
                    #endif
                    MotorControl_ROV_MoveStop(0);
                    break;
    }
    
 
}
