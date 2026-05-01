#ifndef INC_COLOR_H_
#define INC_COLOR_H_

#include "ch32v00x.h"

#include "led.h"



enum COLOR_colors {off, red, yellow, green, cyan, blue, purple, white};

typedef struct 
{
    uint16_t R;
    uint16_t G;
    uint16_t B;
    enum COLOR_colors color;
} color_t;

//uint16_t COLORS_R, COLORS_G, COLORS_B;

void COLOR_Init(void);
void COLOR_Sweep(void);
void COLOR_SetRGB(uint16_t R, uint16_t G, uint16_t B);

#endif /* INC_COLOR_H_ */