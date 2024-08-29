
#include "Common.h"
#include "LightsControl_cfg.h"

static uint8_t LightR_Status = LOW;
static uint8_t LightR_LastStatus = LOW;

static uint8_t LightL_Status = LOW;
static uint8_t LightL_LastStatus = LOW;



static void LigtControl_LightRSetup()
{
  pinMode(LIGHT_RIGHT_PIN,OUTPUT);
  digitalWrite(LIGHT_RIGHT_PIN,LOW);
}

static void LigtControl_LightRSetStatus(uint8_t LightStatus)
{
  digitalWrite(LIGHT_RIGHT_PIN,LightStatus);
}

 



static void LigtControl_LightLSetup()
{
  pinMode(LIGHT_LEFT_PIN,OUTPUT);
  digitalWrite(LIGHT_LEFT_PIN,LOW);
}

static void LigtControl_LightLSetStatus(uint8_t LightStatus)
{
  digitalWrite(LIGHT_LEFT_PIN,LightStatus);
}

 



void LigtControl_Setup(void)
{
  LigtControl_LightRSetup();
  LigtControl_LightLSetup();
}

void LigtControl_Loop(void)
{
  if(LightR_Status != LightR_LastStatus)
  {
    LightR_LastStatus = LightR_Status;
    LigtControl_LightRSetStatus(LightR_LastStatus);
  }

  if(LightL_Status != LightL_LastStatus)
  {
    LightL_LastStatus = LightL_Status;
    LigtControl_LightLSetStatus(LightL_LastStatus);
  }
  
}
void LigtControl_LightRSet(uint8_t LightStatus)
{
  LightR_Status = LightStatus;
}

void LigtControl_LightLSet(uint8_t LightStatus)
{
  LightL_Status = LightStatus;
}
