#ifndef MATRIX_H_
#define MATRIX_H_
#include <avr/io.h>

extern uint8_t matrix_old_key;
void  matrix_init(void);
char  matrix_get(void);

#endif 