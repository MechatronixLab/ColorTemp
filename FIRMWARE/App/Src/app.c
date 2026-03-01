#include "app.h"

void APP_Init(void)
{
    LED_Init();
    TEMPERATURE_Init();

    APP_Run();
}

void APP_Run(void)
{
    while(1)
    {
        LED_SetRGB(1000,    0,    0);
        Delay_Ms(125);

        LED_SetRGB( 500,  500,    0);
        Delay_Ms(125);

        LED_SetRGB(   0, 1000,    0);
        Delay_Ms(125);
        
        LED_SetRGB(   0,  500,  500);
        Delay_Ms(125);

        LED_SetRGB(   0,    0, 1000);
        Delay_Ms(125);

        LED_SetRGB(  500,    0,  500);
        Delay_Ms(125);

        TEMPERATURE_GetT_dC();
    }
}