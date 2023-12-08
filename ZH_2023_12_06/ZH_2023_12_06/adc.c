#include <avr/io.h>
#include "adc.h"

void adc_init(void)
{
	// 	 � ADC enged�lyez�se
	// 	 � ADCSRA � ADEN - 1
	// 	 � Referencia kiv�laszt�sa
	// 	 � ADMUX � REFS1, REFS0 � 00 (4.096V)
	// 	 � ADC �rajel be�ll�t�sa
	// 	 � ADCSRA - ADPS0, ADPS1, ADPS2 � 111 (/128)
	ADCSRA |= (1 << ADEN);
	ADMUX |= (0 << REFS1) | (0 << REFS0);
	ADCSRA |= ((1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));
}
uint16_t adc_mer(void)
{
	// 	 � Csatorna kiv�laszt�sa
	// 	 � ADMUX � MUX4-0 � 0 (CH0-LM35)
	// 	 � Konverzi� elind�t�sa
	// 	 � ADCSRA � ADSC -1
	// 	 � V�rakoz�s a konverzi� befejez�s�re
	// 	 � ADCSRA � ADIF � 1?
	// 	 � M�rt �rt�k elt�rol�sa
	// 	 � ADC (16bit � H, L)
	ADMUX |= ((0 << MUX4) | (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0));
	ADCSRA |= (1 << ADSC);
	ADCSRA |= (1 << ADIF);
	while (!(ADCSRA & (1 << ADIF)))
		;
	return ADC;
}

uint16_t adc_mV(void)
{

	uint16_t mer = adc_mer();
	mer *= 4; // Uref~=4 V
	return mer;
}

uint8_t adc_C(void)
{
	uint16_t mer = adc_mer();
	mer = (mer * 4) / 10; // 1C=10mV
	return mer;
}