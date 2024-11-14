#include "./uart.h"
#include "main.h"
uart_it_frame g_uartframe;

extern UART_HandleTypeDef huart1;
void deluartinfo(){
	if(g_uartframe.flag_finish == 1){
		HAL_UART_Transmit(&huart1 , (uint8_t * )g_uartframe.buffer , g_uartframe.length , 1000);
		//deal
		if(g_uartframe.buffer[1] == 'p'){
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,0);
		}else if(g_uartframe.buffer[1] == 'f'){
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,1);
		}
		g_uartframe.length = 0;
		g_uartframe.flag_finish = 0;
	}
}