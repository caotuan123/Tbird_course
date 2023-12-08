/*
 * hetszeg.h
 *
 * Created: 08/12/2023 7:01:52 SA
 *  Author: CaoAnhTuan
 */ 


#ifndef HETSZEG_H_
#define HETSZEG_H_



void sevseg_init();
// put this function in timer ISR to display sevseg_data in to seven segment
void sevseg_run();
// put unsigned int type number into seven segment
// maximum is 4 digit
void sevseg_print_num_uint(unsigned int num);

#endif /* HETSZEG_H_ */