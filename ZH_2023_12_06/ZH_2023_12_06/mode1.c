#include "mode1.h"

#include "adc.h"
#include "timer.h"
#include "hetszeg.h"
void mode1_start()
{
	// start timer
	timer1_CTCmode_init(256, 1000);
	adc_init();
}
void mode1_stop()
{
	// stop timer
	timer1_CTCmode_init(0, 0);
}

void mode1_run()
{
	static int sum, counter;
	sum += adc_C();
	counter++;
	if (counter == 10)
	{
		sum /= 10;

		sevseg_print_num_uint(sum);
		sum = 0;
		counter = 0;
	}
}
