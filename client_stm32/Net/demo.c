/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "./demo.h"

extern uart_it_frame g_uartframe;

static int isfirst = 1;

void demo_run(){
	
		if(isfirst){
			InitNet();
			atk_mw8266d_uart_rx_restart();
			isfirst = 0;
		}
		
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,0);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,1);
		HAL_Delay(500);
		
		// 处理huart1 也就是串口的通讯
		if(g_uartframe.flag_finish){
			deluartinfo();
		}
		
		// 处理huart2 也就是网卡的信息
		if( atk_mw8266d_uart_rx_get_frame_Isableread()){
			//have info 
			char buf[1005];
			memset(buf , 0 , sizeof buf);
			int len = recvMsgTwo(buf ,sizeof(buf) - 1);
			if(len == 0){
				CloseNet();
			}else{
				HAL_UART_Transmit(&huart1 , (uint8_t * )buf		, len , 1000);
				//行为 ： 系统心跳
				if(len == 6 && 
					(memcmp(buf , "/heart" , len) == 0)){
					HAL_UART_Transmit(&huart1 , (uint8_t *)"[cmd]:recvheart", strlen("[cmd]:recvheart") , 1000);
					setServerHeart();
				}
				else if(len >= 4 && 
					(memcmp(buf , "/cmd" , 4) == 0)){ //行为 ： LED控制
					//server send info
					if(len >= strlen("/cmd openLed") && 
						(memcmp(buf , "/cmd openLed" ,strlen("/cmd openLed")) == 0 )){
						HAL_UART_Transmit(&huart1 , (uint8_t *)"[cmd]:openled", strlen("[cmd]:openled") , 1000);
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,0);
							
					}
					if(len >= strlen("/cmd offfLed") && 
						(memcmp(buf , "/cmd offfLed" ,strlen("/cmd offfLed")) == 0)){
						HAL_UART_Transmit(&huart1 , (uint8_t *)"[cmd]:offfled", strlen("[cmd]:offfled") , 1000);
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,1);
					}
				}else{
					HAL_UART_Transmit(&huart1 , (uint8_t *)"Dont Know Cmd", strlen("Dont Know Cmd") , 1000);
				}
				
			}
		}
		
		//发送心跳
		sendHeart();
		//定时检查系统心跳
		checkServerHeart();
		//系统时间自增
		addSysTime();
}