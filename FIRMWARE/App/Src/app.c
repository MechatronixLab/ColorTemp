#include "app.h"

void APP_TemperatureToColor(int16_t temperature)
{
    uint16_t R, G, B;

    // TODO: Transition linearly from magenta to white (<200 and >600)

    if (temperature < -200) // < 20.0 ¡ãC
    {
        R = 1000;
        G = 1000;
        B = 1000;
    }
    else if (temperature <= 0)
    {
        R = 5 * (- temperature);
        G = 0;
        B = 1000;        
    }
    else if (temperature <= 200)
    {
        R = 0;
        G = 5 * temperature;
        B = 5 * (200 - temperature);        
    }
    else if (temperature <= 400)
    {
        R = 5 * (temperature - 200);
        G = 5 * (400 - temperature);
        B = 0;        
    }
    else if (temperature <= 600)
    {
        R = 1000;
        G = 0;
        B = 5 * (temperature - 400);        
    }
    else    // (temperature > 600)
    {
        R = 1000;
        G = 1000;
        B = 1000;
    }

    COLOR_SetRGB(R, G, B);
}

void APP_Init(void)
{
    COLOR_Init();
    TEMPERATURE_Init();

    APP_Run();
}

void APP_Run(void)
{
    // uint16_t loop_counter = 0;

    int16_t t_dC = -300;

    while(1)
    {


        // COLOR_Sweep();
        // Delay_Ms(2);
        // loop_counter++;

        // if(loop_counter >= 500)
        // {
        //     loop_counter = 0;
        //     TEMPERATURE_GetT_dC();
        // }

        APP_TemperatureToColor(t_dC);
    if (t_dC < 0)
    {
        printf( "Temperature: %3d.%1d " CHAR_DEGREE "C \r\n", 
                         t_dC/10, 
                        -t_dC%10);
    }
    else
    {
        printf( "Temperature: %3d.%1d " CHAR_DEGREE "C \r\n", 
                         t_dC/10, 
                         t_dC%10);
    }
        Delay_Ms(50);

        t_dC++;
        if (t_dC > 700)
        {
            t_dC = -300;
        }
    }
}