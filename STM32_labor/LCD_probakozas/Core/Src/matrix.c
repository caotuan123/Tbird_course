#include "main.h"
#include "matrix.h"




GPIO_TypeDef * matrix_port[7]={

		 KB_PC0_IN_LEFT_GPIO_Port ,

		 KB_PC3_OUT_ROW1_GPIO_Port ,

		KB_PC5_OUT_ROW3_GPIO_Port ,

		 KB_PC1_IN_CENTER_GPIO_Port,

		 KB_PC2_IN_RIGHT_GPIO_Port ,

		 KB_PC4_OUT_ROW2_GPIO_Port ,

		 KB_PC6_OUT_ROW4_GPIO_Port
};

uint16_t matrix_pin[7]={
		 KB_PC0_IN_LEFT_GPIO_Pin ,

		 KB_PC3_OUT_ROW1_GPIO_Pin ,

		    	 KB_PC5_OUT_ROW3_GPIO_Pin ,

				 KB_PC1_IN_CENTER_GPIO_Pin,

				 KB_PC2_IN_RIGHT_GPIO_Pin ,

				 KB_PC4_OUT_ROW2_GPIO_Pin ,

				 KB_PC6_OUT_ROW4_GPIO_Pin
};

// sor PORT

GPIO_TypeDef * sor_PORT[4]={
		 KB_PC3_OUT_ROW1_GPIO_Port ,
		 KB_PC4_OUT_ROW2_GPIO_Port ,
         KB_PC5_OUT_ROW3_GPIO_Port ,
		 KB_PC6_OUT_ROW4_GPIO_Port
};

// sor PIN
uint16_t sor_pin[4]=
{
		KB_PC3_OUT_ROW1_GPIO_Pin ,
		KB_PC4_OUT_ROW2_GPIO_Pin ,
		KB_PC5_OUT_ROW3_GPIO_Pin ,
		KB_PC6_OUT_ROW4_GPIO_Pin
};
void matrix_cimzes(uint8_t sor)//0=3
{
	uint8_t i=0;
	while(i<4)
	{

		HAL_GPIO_WritePin(sor_port[i], sor_pin[i],sor==i);
		i++;


	}

}

uint8_t matrix_olvas(void)
{
	uint8_t  i=0;
	uint8_t olvas=0;
	while(i<7)
	{
		olvas<<=1;
		olvas|=HAL_GPIO_ReadPin(matrix_port[i], matrix_pin[i]);
		i++;
	}

	return olvas;

}
// sor cimzes
// olvasas
// matrix

uint8_t matrix(void)
{

	uint8_t matrix_row; //sor cimzeshez
	uint8_t key=0;
	char  matrix_map[]={'*','0','#',
						'1','2','3',
						'4','5','6',
						'7','8','9',0xFF};
	uint8_t olvas;
	//sor_cimzes
	//5ms delay
	//olvas

	for(matrix_row=0;matrix_row<=3;matrix_row++)
	{
		matrix_cimzes(matrix_row);
		olvas=matrix_olvas();
		HAL_Delay(5);
		if()
	}


}
