#ifndef __LIGHT_CONTROLLER__
#define __LIGHT_CONTROLLER__

#define MAX_SCHEDULE   128

void LightController_Create(void);
void LightController_Destroy(void);
void LightController_On(int id);
void LightController_Off(int id);

#endif