#include "./atk_mw8266d_it.h"

//serial
extern uart_it_frame g_uartframe;
//wifi
extern UART_stu g_uart_rx_frame;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void Serial_IRQHandler(void)
{
	int ret;
  /* USER CODE BEGIN USART1_IRQn 0 */
	uint8_t tmpval = 0;
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
	if( __HAL_UART_GET_FLAG(&huart1 , UART_FLAG_RXNE) != RESET){
		uint8_t tmpchar[] = {""};
		ret = HAL_UART_Receive(&huart1 , &tmpval , 1 ,1000);
		if(g_uartframe.length < Uart_Max_Length){
			g_uartframe.buffer[g_uartframe.length] = tmpval;
			g_uartframe.length++;
		}else{
			//dq
			return;
		}
	}
	
	if( __HAL_UART_GET_FLAG(&huart1 , UART_FLAG_IDLE) != RESET){
		g_uartframe.flag_finish = 1;
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
	}
}

void ATK_MW8266d_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
	int ret;
  /* USER CODE BEGIN USART1_IRQn 0 */
	uint8_t tmpval = 0;
  /* USER CODE END USART1_IRQn 0 */
  /* USER CODE BEGIN USART1_IRQn 1 */
	if(g_uart_rx_frame.sta_it.bCantIt){
		g_uart_rx_frame.sta_it.bIfIt = 1;
		return;
	}
	if( __HAL_UART_GET_FLAG(&huart2 , UART_FLAG_RXNE) != RESET){
		uint8_t tmpchar[] = {""};
		ret = HAL_UART_Receive(&huart2 , &tmpval , 1 ,1000);
		if(g_uart_rx_frame.sta.len < Uart_Max_Length){
			g_uart_rx_frame.buf[g_uart_rx_frame.sta.len] = tmpval;
			g_uart_rx_frame.sta.len++;
		}else{
			//dq
			return;
		}
	}
	
	if( __HAL_UART_GET_FLAG(&huart2 , UART_FLAG_IDLE) != RESET){
		g_uart_rx_frame.sta.finsh = 1;
		__HAL_UART_CLEAR_IDLEFLAG(&huart2);
	}
  /* USER CODE END USART2_IRQn 1 */
}