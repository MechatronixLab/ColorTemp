#ifndef INC_APP_H_
#define INC_APP_H_

#include "ch32v00x.h"

#include "button.h"
#include "color.h"
#include "temperaure.h"

typedef enum
{
    MODE_NORMAL     = 0,
    MODE_EXTENDED   = 1,
    MODE_SWEEP      = 2,
    MODE_LAST       = 3
} AppMode_e;

void APP_TemperatureToColor(int16_t temperature);
void APP_Init(void);
void APP_Run(void);

#endif /* INC_APP_H_ */
