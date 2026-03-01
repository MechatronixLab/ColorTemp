#include "ch32v00x.h"

#define ADC_VDD_mV   5000   // VDD in mV

#define CHAR_DEGREE "\xB0"  // бу

void TEMPERATURE_Init(void);
uint16_t TEMPERATURE_GetT_dC(void);