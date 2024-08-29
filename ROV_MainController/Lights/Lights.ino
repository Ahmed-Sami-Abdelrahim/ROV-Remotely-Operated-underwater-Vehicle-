#include "Common.h"
#include "LightsControl.h"

uint8_t LightR = LOW;
uint8_t LightL = LOW;

void setup() 
{
  // put your setup code here, to run once:
  LigtControl_Setup();

}

void loop() 
{
 
  LightR = !LightR; //toggle status
  LightL = !LightL; //toggle status
  
  LigtControl_LightRSet(LightR);
  LigtControl_LightLSet(LightL);
  LigtControl_Loop();
  delay(500);
}
