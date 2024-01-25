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

int common_state = 0;
uint8_t regi_allapot;

struct phan_so
{
	int mau;
	int tu;
}

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

	const uint8_t times; // TODO explain
	uint8_t counter;		// TODO explain

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

allapot ejszakas[2] = {
		/*0*/ {0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		/*1*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},

};

uint8_t pwm1 = 0;
uint8_t pwm2 = 0;
uint16_t timer0_counter = 0;
uint8_t timer0_counter_1 = 0;
uint8_t timer0_counter_2 = 0;
uint8_t regi_gomb = 0;
uint8_t jon_a_vonat = 0;	 // 1-> jon a vonat, 0->nincs vonat
uint8_t mod_valasztas = 1; // 1-> nappali, 0->ejszakasi

uint8_t vonat_gomb_get(void);
void do_traffic(allapot *mod);
void ejszakasi_mod();
void nappali_mod();

int main(void)
{

	led_init();
	timer1_CTCmode_init(256, 15625); /// 256-15625
	timer0_CTCmode_init(32, 25);
	sei();

	button_init();

	DDRA = PORTA_MASK;
	DDRC = PORTC_MASK;
	DDRF = PORTF_MASK;
	DDRE = PORTE_MASK;

	DDRE &= ~((1 << BTNV1) | (1 << BTNV2));
	PORTE = (1 << BTNV1) | (1 << BTNV2);

	uint8_t button_tmp;
	uint8_t regi_vonat_gomb = 0;
	uint8_t regi_vonat_gomb1 = 0;
	uint8_t vonat_but = 0;
	uint8_t sum = 0;
	while (1)
	{

		vonat_but = vonat_gomb_get();

		if (vonat_but)
		{
			if ((!jon_a_vonat) && (!regi_vonat_gomb1))
			{
				regi_vonat_gomb1 = vonat_but;
				jon_a_vonat = 1;
				PORTF &= ~(1 << LV_F);
			}
			if (jon_a_vonat && (regi_vonat_gomb1 != vonat_but))
			{
				regi_vonat_gomb1 = 0;
				jon_a_vonat = 0;
				PORTF &= ~((1 << LV_P1) | (1 << LV_P2));
			}
		}

		button_tmp = button_get();
		if (button_tmp)
		{
			if (button_tmp < 3)
				switch (button_tmp)
				{
				case 1:
					mod_valasztas = 1;
					common_state = 0;
					break;
				case 2:
					PORTA = 0;
					PORTC = 0;
					PORTE &= ~((1 << LG1_Z) | (1 << LG2_Z) | (1 << LG1_P) | (1 << LG2_P));
					mod_valasztas = 0;
					common_state = 0;
					break;
				default:
					break;
				}
			else if (button_tmp == 3 || button_tmp == 4)
			{
				if ((!jon_a_vonat) && (!regi_vonat_gomb))
				{
					regi_vonat_gomb = button_tmp;
					jon_a_vonat = 1;
					led_pwm_allapot.led_v_f = 0;
					PORTF &= ~(1 << LV_F);
				}
				if (jon_a_vonat && (regi_vonat_gomb != button_tmp))
				{
					regi_vonat_gomb = 0;
					jon_a_vonat = 0;
					led_pwm_allapot.led_v_f = 1;
					PORTF &= ~((1 << LV_P1) | (1 << LV_P2));
				}
			}
		}
	}
}

uint8_t vonat_gomb_get(void)
{
	uint8_t vonat_gomb = 0;

	if (BTNV1_PRESSED())
		vonat_gomb = 1;
	else if (BTNV2_PRESSED())
		vonat_gomb = 2;

	if (vonat_gomb != regi_gomb)
	{
		regi_gomb = vonat_gomb;
		return vonat_gomb;
	}
	else

		return 0;
}

void do_traffic(allapot *mod)
{
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
		if (jon_a_vonat)
			do_traffic(nappali_v);
		else
			do_traffic(nappali);
	}

	//count
	if (nappali[common_state].counter < nappali[common_state].times)
	{
		nappali[common_state].counter++;
	}
	else
	{
		//change to the next state
		nappali[common_state].counter = 0;
		common_state++;
		if (common_state == 10)
			common_state = 1;
		
		if (jon_a_vonat)
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

void ejszakasi_mod()
{

	if (ejszakas[common_state].counter < ejszakas[common_state].times)
	{
		ejszakas[common_state].counter++;
	}
	else
	{
		ejszakas[common_state].counter = 0;
		common_state++;
		if (common_state == 2)
			common_state = 0;
		led_out(common_state);

		do_traffic(ejszakas);
	}
}
ISR(TIMER1_COMPA_vect)
{
	if (mod_valasztas)
		nappali_mod();
	
		//ejszakasi_mod();
}
ISR(TIMER0_COMP_vect)
{
	timer0_counter++;
	if (timer0_counter == 10000)
	{
		pwm1 = 0;
		timer0_counter = 0;
	}
	if (timer0_counter > 5000)
	{
		timer0_counter_1++;
		if (timer0_counter_1 == 100)
		{
			pwm1++;
			if (pwm1 == 50)
				pwm1 = 0;
			timer0_counter_1 = 0;
		}
		if (pwm1 > timer0_counter_1)
		{
			if (!mod_valasztas)
			{

				PORTA =
						(1 << LA_S) |
						(1 << LB_S);

				PORTC =
						(1 << LD_S) |
						(1 << LC_S) |
						(1 << LE_S);
			}
			if (led_pwm_allapot.led_g1_z)
				PORTE |= (1 << LG1_Z);
			if (led_pwm_allapot.led_g2_z)
				PORTE |= (1 << LG2_Z);
			if (led_pwm_allapot.led_v_f)
				PORTF |= (1 << LV_F);
			if (jon_a_vonat)
				PORTF |= (1 << LV_P1);
		}
		else
		{
			if (!mod_valasztas)
			{

				PORTA &= ~(
						(1 << LA_S) |
						(1 << LB_S));

				PORTC &=
						~((1 << LD_S) |
							(1 << LC_S) |
							(1 << LE_S));
			}
			if (led_pwm_allapot.led_g1_z)
				PORTE &= ~(1 << LG1_Z);
			if (led_pwm_allapot.led_g2_z)
				PORTE &= ~(1 << LG2_Z);
			if (led_pwm_allapot.led_v_f)
				PORTF &= ~(1 << LV_F);
			if (jon_a_vonat)
				PORTF &= ~(1 << LV_P1);
		}
	}
	else
	{
		timer0_counter_2++;
		if (timer0_counter_2 == 100)
		{
			pwm2++;
			if (pwm2 == 50)
				pwm2 = 0;
			timer0_counter_2 = 0;
		}
		if (pwm2 > timer0_counter_2)
		{
			if (jon_a_vonat)
				PORTF |= (1 << LV_P2);
		}
		else
		{
			if (jon_a_vonat)
				PORTF &= ~(1 << LV_P2);
		}
	}
}
