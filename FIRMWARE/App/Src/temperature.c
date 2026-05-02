#include "temperaure.h"

void TEMPERATURE_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // Enable Clocks for GPIOA and ADC1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);

    // Set ADC Clock Prescaler (ADC should not exceed 14MHz)
    // 48MHz / 4 = 12MHz
    RCC_ADCCLKConfig(RCC_PCLK2_Div4);

    // Configure PA2 as Analog Input
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // Analog Input Mode
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ADC Configuration
    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // Single conversion
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1, ENABLE);

    // Calibrate the ADC
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
}

int16_t TEMPERATURE_GetT_dC(void)
{
    uint16_t adc_raw = 0;
    uint16_t adc_mV  = 0;
    int16_t temperature = 0;

    // Configure channel 0 for a sample time of 241 cycles
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_241Cycles);

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    // Wait until conversion is complete
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    adc_raw = ADC_GetConversionValue(ADC1);

    adc_mV = (adc_raw * ADC_VDD_mV) / 1024;

    temperature = adc_mV - 500;   // Temperature in 0.1 °„C/mV; 500mV offset (MCP9700A)

    if (temperature < 0)
    {
        printf( "Temperature: %3d.%1d " CHAR_DEGREE "C \r\n", 
                         temperature/10, 
                        -temperature%10);
    }
    else
    {
        printf( "Temperature: %3d.%1d " CHAR_DEGREE "C \r\n", 
                         temperature/10, 
                         temperature%10);
    }

    return temperature;
}