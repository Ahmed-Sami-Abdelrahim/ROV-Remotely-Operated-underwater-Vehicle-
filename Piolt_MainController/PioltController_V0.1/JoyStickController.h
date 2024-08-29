#ifndef _JOYSTICK_CONTROLLER_APP_
#define _JOYSTICK_CONTROLLER_APP_

 
 


uint8_t JoyStickController_Setup(void);
uint8_t JoyStickController_Loop(void);

uint8_t JoyStickController_GetDir(void);
int16_t JoyStickController_GetSpd(void);
uint8_t JoyStickControllerA_GetSW(void);
uint8_t JoyStickControllerB_GetSW(void);

#endif /*_JOYSTICK_CONTROLLER_APP_*/
