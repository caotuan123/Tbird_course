#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
#include "led.h"
#include "button.h"

//------ for car
#define LA_P PA0
#define LA_S PA1
#define LA_Z PA2

#define LB_P PA3
#define LB_S PA4
#define LB_Z PA5
#define LB_Z2 PA6

#define LC_P PC2
#define LC_S PC3
#define LC_Z PC4

#define LD_P PA7
#define LD_S PC0
#define LD_Z PC1

#define LE_P PC5
#define LE_S PC6
#define LE_Z PC7
#define LE_Z2 PF0
//--------

//-for people

#define LG1_P PE2
#define LG1_Z PE3

#define LG2_P PE6
#define LG2_Z PE7
//--------

//---for train
#define LV_P1 PF1
#define LV_P2 PF2
#define LV_F PF3
//--------------

#define BTNV1 PE4
#define BTNV2 PE5

#define BTNV1_PRESSED() (!(PINE & (1 << BTNV1)))
#define BTNV2_PRESSED() (!(PINE & (1 << BTNV2)))

#define PORTA_MASK 0xFF
#define PORTC_MASK 0xFF
#define PORTF_MASK 0x0F
#define PORTE_MASK 0xCC

typedef struct allapotok
{
	uint8_t led_a_p;
	uint8_t led_a_s;
	uint8_t led_a_z;

	uint8_t led_b_p;
	uint8_t led_b_s;
	uint8_t led_b_z;
	uint8_t led_b_z2;

	uint8_t led_c_p;
	uint8_t led_c_s;
	uint8_t led_c_z;

	uint8_t led_d_p;
	uint8_t led_d_s;
	uint8_t led_d_z;

	uint8_t led_e_p;
	uint8_t led_e_s;
	uint8_t led_e_z;
	uint8_t led_e_z2;

	uint8_t led_g1_p;
	uint8_t led_g1_z;

	uint8_t led_g2_p;
	uint8_t led_g2_z;

	uint8_t led_v_p1;
	uint8_t led_v_p2;
	uint8_t led_v_f;

	const uint8_t times; // period times
	uint8_t counter;		 // current counter for period times

} allapot;

typedef struct pwm_allapotok
{
	uint8_t led_g1_z;
	uint8_t led_g2_z;
	uint8_t led_v_p1;
	uint8_t led_v_p2;
	uint8_t led_v_f;

} pwm_allapot;

pwm_allapot led_pwm_allapot = {0, 0, 0, 0, 1};
//     a_p,a_s,a_z,b_p,b_s,b_z,b_z2,c_p,c_s,c_z,d_p,d_s,d_z,e_p,e_s,e_z,e_z2,g1_p,g1_z,g2_p,g2_z,v_p1,v_p2,v_f
allapot nappali[10] = {
		/*0*/ {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 4, 0},
		/*9*/ {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 2, 0},
		/*1*/ {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 10, 0},
		/*2*/ {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 2, 0},
		/*3*/ {0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 2, 1, 0, 0, 0, 0, 2, 0},
		/*4*/ {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 10, 0},
		/*5*/ {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 0, 2, 0},
		/*6*/ {1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 0, 2, 0},
		/*7*/ {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 10, 0},
		/*8*/ {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 2, 0}

};

//    a_p,a_s,a_z,b_p,b_s,b_z,b_z2,c_p,c_s,c_z,d_p,d_s,d_z,e_p,e_s,e_z,e_z2,g1_p,g1_z,g2_p,g2_z,v_p1,v_p2,v_f
allapot nappali_v[10] = {
		/*0*/ {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 4, 0},
		/*9*/ {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 2, 0},
		/*1*/ {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 10, 0},
		/*2*/ {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 2, 0},
		/*3*/ {0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 2, 1, 0, 0, 0, 0, 2, 0},
		/*4*/ {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 10, 0},
		/*5*/ {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 0, 2, 0},
		/*6*/ {1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 0, 2, 0},
		/*7*/ {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 10, 0},
		/*8*/ {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 2, 0}

};

int common_state = 0;
uint8_t is_train_comming = 0; // 1-> jon a vonat, 0->nincs vonat
uint8_t day_night_mode = 1;		// 1-> nappali, 0->ejszakasi

uint8_t vonat_gomb_get(void);
void do_traffic(allapot *mod);
void ejszakasi_mod();
void nappali_mod();
void night_mode_yellow_leds(uint8_t state);
void pwm_first_half(uint8_t state);
int main(void)
{
	// set up
	led_init();
	timer1_CTCmode_init(256, 15625); // time:0.5s (256, 15625) for 8MHz
	timer0_CTCmode_init(32, 25);		 // time:100us (32, 25) for 8MHz
	sei();
	button_init();

	DDRA = PORTA_MASK;
	DDRC = PORTC_MASK;
	DDRF = PORTF_MASK;
	DDRE = PORTE_MASK;

	DDRE &= ~((1 << BTNV1) | (1 << BTNV2));
	PORTE = (1 << BTNV1) | (1 << BTNV2);

	uint8_t button_tmp;
	uint8_t vonat_but = 0;
	// handle button, change mode
	while (1)
	{

		// vonat_but = vonat_gomb_get();

		// if (vonat_but)
		// {
		// 	static uint8_t elso_vonat_gomb = 0;
		// 	if ((!is_train_comming) && (!elso_vonat_gomb))
		// 	{
		// 		elso_vonat_gomb = vonat_but;
		// 		is_train_comming = 1;
		// 		led_pwm_allapot.led_v_f = 0;
		// 		PORTF &= ~(1 << LV_F);
		// 	}
		// 	if (is_train_comming && (elso_vonat_gomb != vonat_but))
		// 	{
		// 		elso_vonat_gomb = 0;
		// 		is_train_comming = 0;
		// 		led_pwm_allapot.led_v_f = 1;
		// 		PORTF &= ~((1 << LV_P1) | (1 << LV_P2));
		// 	}
		// }

		button_tmp = button_get();
		if (button_tmp)
		{
			if (button_tmp < 3)
				switch (button_tmp) // choose day/night mode
				{
				case 1:
					day_night_mode = 1; // nappali
					common_state = 0;		// start at first state
					break;
				case 2:
					PORTA = 0;
					PORTC = 0;
					PORTE &= ~((1 << LG1_Z) | (1 << LG2_Z) | (1 << LG1_P) | (1 << LG2_P));
					PORTF &= ~((1<< LE_Z2));
					day_night_mode = 0; // ejszakasi
					common_state = 0;		// start at first state
					led_pwm_allapot.led_g1_z = 0;
					led_pwm_allapot.led_g2_z = 0;
					break;
				default:
					break;
				}
			// Uncomment this part if you want to use the train button on the t-bird board

			else if (button_tmp == 3 || button_tmp == 4)
			{
			 static uint8_t elso_vonat_gomb = 0;
				if ((!is_train_comming) && (!elso_vonat_gomb))
				{
					elso_vonat_gomb = button_tmp;
					is_train_comming = 1;
					led_pwm_allapot.led_v_f = 0;
					PORTF &= ~(1 << LV_F);
				}
				if (is_train_comming && (elso_vonat_gomb != button_tmp))
				{
					elso_vonat_gomb = 0;
					is_train_comming = 0;
					led_pwm_allapot.led_v_f = 1;
					PORTF &= ~((1 << LV_P1) | (1 << LV_P2));
				}
			}
		}
	}
}

uint8_t vonat_gomb_get(void)
{
	static uint8_t regi_vonat_gomb_all = 0;
	uint8_t vonat_gomb = 0;

	if (BTNV1_PRESSED())
		vonat_gomb = 1;
	else if (BTNV2_PRESSED())
		vonat_gomb = 2;

	if (vonat_gomb != regi_vonat_gomb_all)
	{
		regi_vonat_gomb_all = vonat_gomb;
		return vonat_gomb;
	}
	return 0;
}

void do_traffic(allapot *mod)
{
	uint8_t regi_allapot;
	PORTA = (mod[common_state].led_a_p << LA_P) |
					(mod[common_state].led_a_s << LA_S) |
					(mod[common_state].led_a_z << LA_Z) |
					(mod[common_state].led_b_p << LB_P) |
					(mod[common_state].led_b_s << LB_S) |
					(mod[common_state].led_b_z << LB_Z) |
					(mod[common_state].led_b_z2 << LB_Z2) |
					(mod[common_state].led_d_p << LD_P);

	PORTC = (mod[common_state].led_d_s << LD_S) |
					(mod[common_state].led_d_z << LD_Z) |
					(mod[common_state].led_c_p << LC_P) |
					(mod[common_state].led_c_s << LC_S) |
					(mod[common_state].led_c_z << LC_Z) |
					(mod[common_state].led_e_p << LE_P) |
					(mod[common_state].led_e_s << LE_S) |
					(mod[common_state].led_e_z << LE_Z);

	regi_allapot = PINF & ((1 << LV_P1) |
												 (1 << LV_P2) |
												 (1 << LV_F));

	PORTF = (mod[common_state].led_e_z2 << LE_Z2) |
					regi_allapot;

	regi_allapot = PINE & ((1 << LG1_Z) | (1 << LG2_Z));

	PORTE = (mod[common_state].led_g1_p << LG1_P) |
					(mod[common_state].led_g2_p << LG2_P) |
					regi_allapot;
}

void nappali_mod()
{

	// this state just happen once
	if (common_state == 0)
	{
		if (is_train_comming)
			do_traffic(nappali_v);
		else
			do_traffic(nappali);
	}

	// count
	if (nappali[common_state].counter < nappali[common_state].times)
	{
		nappali[common_state].counter++;
	}
	else
	{
		// change to the next state
		nappali[common_state].counter = 0;
		common_state++;
		if (common_state == 10)
			common_state = 1;

		if (is_train_comming)
			do_traffic(nappali_v);
		else
			do_traffic(nappali);
	}

	if (nappali[common_state].led_g1_z == 2)
		led_pwm_allapot.led_g1_z = 1;
	else if (nappali[common_state].led_g1_z == 1)
		PORTE |= (1 << LG1_Z);
	else
	{
		led_pwm_allapot.led_g1_z = 0;
		PORTE &= ~(1 << LG1_Z);
	}

	if (nappali[common_state].led_g2_z == 2)
		led_pwm_allapot.led_g2_z = 1;
	else if (nappali[common_state].led_g2_z == 1)
		PORTE |= (1 << LG2_Z);
	else
	{
		led_pwm_allapot.led_g2_z = 0;
		PORTE &= ~(1 << LG2_Z);
	}
}

ISR(TIMER1_COMPA_vect)
{
	if (day_night_mode)
		nappali_mod();
}

// handle pwm
ISR(TIMER0_COMP_vect)
{
	static int t0_main_counter = 0;

	static int t0_first_half_counter = 0;
	static int t0_second_half_counter = 0;

	static int first_half_pwm = 0;
	static int second_half_pwm = 0;

	t0_main_counter++;
	if (t0_main_counter == 10000)
	{
		first_half_pwm = 0;
		t0_main_counter = 0;
	}

	if (t0_main_counter > 5000)
	/* first half: do pwm on yellow leds, train light red1,
	 train light white and gyalog green leds */
	{
		t0_first_half_counter++;
		if (t0_first_half_counter == 100) // maximum of pwm
		{
			t0_first_half_counter = 0;

			first_half_pwm++;
			if (first_half_pwm == 50)
				first_half_pwm = 0;
		}

		if (first_half_pwm > t0_first_half_counter)
		{
			pwm_first_half(1);
		}
		else
		{
			pwm_first_half(0);
		}
	}
	// second half turn off all light except train light red2
	else
	{
		t0_second_half_counter++;
		if (t0_second_half_counter == 100)
		{
			second_half_pwm++;
			if (second_half_pwm == 50)
				second_half_pwm = 0;
			t0_second_half_counter = 0;
		}

		if (second_half_pwm > t0_second_half_counter)
		{
			if (is_train_comming)
				PORTF |= (1 << LV_P2);
		}
		else
		{
			if (is_train_comming)
				PORTF &= ~(1 << LV_P2);
		}
	}
}

void night_mode_yellow_leds(uint8_t state)
{
	if (!day_night_mode) // ejszakasi mod
	{
		if (state)
		{ // turn on all yellow leds
			PORTA =
					(1 << LA_S) |
					(1 << LB_S);

			PORTC =
					(1 << LD_S) |
					(1 << LC_S) |
					(1 << LE_S);
		}
		else
		{
			// turn off all yellow leds
			PORTA &= ~(
					(1 << LA_S) |
					(1 << LB_S));

			PORTC &=
					~((1 << LD_S) |
						(1 << LC_S) |
						(1 << LE_S));
		}
	}
}

// Pedestrian crossing light
void gyalog_green_leds(uint8_t state)
{
	if (state)
	{
		if (led_pwm_allapot.led_g1_z)
			PORTE |= (1 << LG1_Z);
		if (led_pwm_allapot.led_g2_z)
			PORTE |= (1 << LG2_Z);
	}
	else
	{
		if (led_pwm_allapot.led_g1_z)
			PORTE &= ~(1 << LG1_Z);
		if (led_pwm_allapot.led_g2_z)
			PORTE &= ~(1 << LG2_Z);
	}
}

void train_leds(uint8_t state)
{
	if (state)
	{
		if (led_pwm_allapot.led_v_f)
			PORTF |= (1 << LV_F);
		if (is_train_comming)
			PORTF |= (1 << LV_P1);
	}
	else
	{
		if (led_pwm_allapot.led_v_f)
			PORTF &= ~(1 << LV_F);
		if (is_train_comming)
			PORTF &= ~(1 << LV_P1);
	}
}
void pwm_first_half(uint8_t state)
{
		night_mode_yellow_leds(state);
		gyalog_green_leds(state);
		train_leds(state);
}