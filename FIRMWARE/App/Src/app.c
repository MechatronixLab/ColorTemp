#include "app.h"

void APP_TemperatureToColor(int16_t temperature)
{
    uint16_t R, G, B;

    if      (temperature < -400) // < 20.0 ¡ãC
    {
        R = 1000;
        G = 1000;
        B = 1000;
    }
    else if (temperature < -200)
    {
        R = 1000;
        G = 5 * (-temperature - 200);
        B = 1000;        
    }
    else if (temperature < 0)
    {
        R = 5 * (-temperature);
        G = 0;
        B = 1000;        
    }
    else if (temperature < 200)
    {
        R = 0;
        G = 5 * temperature;
        B = 5 * (200 - temperature);        
    }
    else if (temperature < 400)
    {
        R = 5 * (temperature - 200);
        G = 5 * (400 - temperature);
        B = 0;        
    }
    else if (temperature < 600)
    {
        R = 1000;
        G = 0;
        B = 5 * (temperature - 400);        
    }
    else if (temperature < 800)
    {
        R = 1000;
        G = 5 * (temperature - 600);
        B = 1000;    
    }
    else // if (temperature >= 800)
    {
        R = 1000;
        G = 1000;
        B = 1000;
    }

    COLOR_SetRGB(R, G, B);
}

void APP_Init(void)
{
    BUTTON_Init();
    COLOR_Init();
    TEMPERATURE_Init();

    APP_Run();
}

void APP_Run(void)
{
    int16_t t_dC = 0;       // Temperature in 0.1 ¡ãC
    uint16_t alpha = 40;    // Temperature filter parameter

    uint16_t delay_ms = 0;

    uint8_t button_pressed = 0;

    AppMode_e mode = MODE_NORMAL;

    while(1)
    {
        t_dC = ( (alpha - 1) * t_dC + TEMPERATURE_GetT_dC() ) / alpha;

        if (BUTTON_Get())
        {
            if (button_pressed == 0)
            {
                mode++;
                if (mode >= MODE_LAST)
                {
                    mode = MODE_NORMAL;
                }
                printf("Mode selected: %d \r\n", mode);
            }
            button_pressed = 1;
        }
        else
        { 
            button_pressed = 0;
        }

        switch (mode)
        {
            case MODE_NORMAL:
                delay_ms = 100;
                APP_TemperatureToColor(t_dC);
                break;

            case MODE_EXTENDED:
                delay_ms = 100;
                APP_TemperatureToColor(t_dC);
                break;

            case MODE_SWEEP:
                delay_ms = 1;
                COLOR_Sweep();
                break;
            
            default:
                mode = MODE_NORMAL;
                break;
        }
        
        Delay_Ms(delay_ms);

        // if (t_dC >= 0)
        // {
        //     printf("Temperature: %3d.%1d " CHAR_DEGREE "C \r\n", 
        //                     t_dC/10, 
        //                     t_dC%10);
        // }
        // else
        // {
        //     printf("Temperature: %3d.%1d " CHAR_DEGREE "C \r\n", 
        //                     t_dC/10, 
        //                    -t_dC%10);
        // }
    }
}
