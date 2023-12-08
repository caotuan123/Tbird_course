#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void adc_init(void);
uint16_t adc_mer(void);
uint16_t adc_mV(void);
uint8_t adc_C(void);
#endif