#include "led.h"

void LED_Init(void)
{
    uint16_t prescaler = (  24 - 1);    // 24 MHz Master Clock -> 1 MHz
    uint16_t period    = (1000 - 1);    // 1 kHz period

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    TIM_OCInitTypeDef TIM_OCInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    // Enable Clocks (Added Port A)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC | 
                           RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;

    // Configure PC3 (RED)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // Configure PA1 (GREEN)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Configure PD2 (BLUE)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // Time Base Setup
    TIM_TimeBaseInitStructure.TIM_Prescaler = prescaler;
    TIM_TimeBaseInitStructure.TIM_Period = period;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    // PWM Mode Setup
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM1, &TIM_OCInitStructure); // PD2 - BLUE
    TIM_OC2Init(TIM1, &TIM_OCInitStructure); // PA1 - GREEN
    TIM_OC3Init(TIM1, &TIM_OCInitStructure); // PC3 - RED

    // Housekeeping & Enable
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);

    TIM_CtrlPWMOutputs(TIM1, ENABLE); // Required for TIM1
    TIM_Cmd(TIM1, ENABLE);
}

void LED_SetRGB(uint16_t R, uint16_t G, uint16_t B)
{
    // Subtract from 1000 because LEDs are connected from VDD to the GPIOs
    TIM1->CH3CVR = (1000 - R);
    TIM1->CH2CVR = (1000 - G);
    TIM1->CH1CVR = (1000 - B); 
}