#include "button.h"

void BUTTON_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

uint8_t BUTTON_Get(void)
{
    uint8_t pressed = 0;

    if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0))
    {
        pressed = 0;
    }
    else
    {
        pressed = 1;
    }
    
    return pressed;
}