#include "color.h"

enum COLOR_colors COLORS_state = off;

uint16_t COLORS_R = 0;
uint16_t COLORS_G = 0;
uint16_t COLORS_B = 0;

color_t mainLED = {0};

void COLOR_Init(void)
{
    COLORS_R = 1000;
	COLORS_G = 0;
	COLORS_B = 1000;
    COLORS_state = red;

	mainLED.R = 1000;
	mainLED.G =    0;
	mainLED.B = 1000;
	mainLED.color = red;

	LED_Init();
}

void COLOR_Sweep(void)
{
	switch (COLORS_state)
	{
		case off:		// Shutdown

			COLORS_R = 0;
			COLORS_G = 0;
			COLORS_B = 0;

			break;

		case red:		// Red

			COLORS_B--;
			if (COLORS_B == 0)
			{
				COLORS_state = yellow;
			}
			break;

		case yellow:	// Yellow

			COLORS_G++;
			if (COLORS_G == 1000)
			{
				COLORS_state = green;
			}
			break;

		case green:		// Green

			COLORS_R--;
			if (COLORS_R == 0)
			{
				COLORS_state = cyan;
			}
			break;

		case cyan:		// Cyan

			COLORS_B++;
			if (COLORS_B == 1000)
			{
				COLORS_state = blue;
			}
			break;

		case blue:		// Blue

			COLORS_G--;
			if (COLORS_G == 0)
			{
				COLORS_state = purple;
			}
			break;

		case purple:	// Purple

			COLORS_R++;
			if (COLORS_R == 1000)
			{
				COLORS_state = red;
			}
			break;

		case white:		// White

			COLORS_R = 1000;
			COLORS_G = 1000;
			COLORS_B = 1000;

			break;

		default:		// Default: Shutdown

			COLORS_R = 0;
			COLORS_G = 0;
			COLORS_B = 0;

			break;
	}

    LED_SetRGB(COLORS_R, COLORS_G, COLORS_B);
}

void COLOR_SetRGB(uint16_t R, uint16_t G, uint16_t B)
{
	LED_SetRGB(R, G, B);
}