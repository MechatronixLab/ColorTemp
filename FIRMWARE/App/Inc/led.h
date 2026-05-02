#ifndef INC_LED_H_
#define INC_LED_H_

#include "ch32v00x.h"

void LED_Init(void);
void LED_SetRGB(uint16_t R, uint16_t G, uint16_t B);

#endif /* INC_LED_H_ */