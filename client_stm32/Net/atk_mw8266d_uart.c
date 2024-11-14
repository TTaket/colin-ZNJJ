#include "atk_mw8266d.h"
#include "atk_mw8266d_uart.h"
#include "stm32f1xx_it.h"
#include "./net.h"
#include "usart.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
extern UART_stu g_uart_rx_frame;
static uint8_t g_uart_tx_buf[ATK_MW8266D_UART_TX_BUF_SIZE]; /* ATK-MW8266D UART发送缓冲 */

/**
 * @brief       ATK-MW8266D UART printf
 * @param       fmt: 待打印的数据
 * @retval      无
 */
void atk_mw8266d_uart_printf(char *fmt, ...)
{
    va_list ap;
    uint16_t len;
    
    va_start(ap, fmt);
    vsprintf((char *)g_uart_tx_buf, fmt, ap);
    va_end(ap);
    
    len = strlen((const char *)g_uart_tx_buf);
		HAL_UART_Transmit(&huart2, g_uart_tx_buf, len, HAL_MAX_DELAY);
}

/**
 * @brief       ATK-MW8266D UART重新开始接收数据
 * @param       无
 * @retval      无
 */
void atk_mw8266d_uart_rx_restart(void)
{
    g_uart_rx_frame.sta.len     = 0;
    g_uart_rx_frame.sta.finsh   = 0;
}

/**
 * @brief       获取ATK-MW8266D UART接收到的一帧数据
 * @param       无
 * @retval      NULL: 未接收到一帧数据
 *              其他: 接收到的一帧数据
 */
uint8_t *atk_mw8266d_uart_rx_get_frame(void)
{
    if (g_uart_rx_frame.sta.finsh == 1)
    {
        g_uart_rx_frame.buf[g_uart_rx_frame.sta.len] = '\0';
        return g_uart_rx_frame.buf;
    }
    else
    {
        return NULL;
    }
}

/**
 * @brief       获取接收到的一帧数据  with len
 * @param       无
 * @retval      NULL: 未接收到一帧数据
 *              其他: 接收到的一帧数据
 */
int atk_mw8266d_uart_rx_get_frame_withlen(char*buf , int len)
{
		int recvlen = 0;
		while(recvlen < len){
			
			if (atk_mw8266d_uart_rx_get_frame_Isableread())
			{
					g_uart_rx_frame.sta_it.bIfIt = 0;
					g_uart_rx_frame.sta_it.bCantIt = 1;
					int buflen = g_uart_rx_frame.sta.len;
					int needlen = len - recvlen;
					int ableread = buflen < needlen ? buflen : needlen;
					
					memcpy(buf , g_uart_rx_frame.buf , needlen);
					buf[len] = '\0';
					recvlen += ableread;
				
					int copylen = buflen - ableread;
					for( int i = 0;i<copylen;i++){
						g_uart_rx_frame.buf[i] = g_uart_rx_frame.buf[i + len];
					}
					g_uart_rx_frame.buf[copylen] = '\0';
					g_uart_rx_frame.sta.len = copylen;
					
					g_uart_rx_frame.sta_it.bCantIt = 0;
					if(g_uart_rx_frame.sta_it.bIfIt){
						//涓柇琛ュ伩
						USART2_IRQHandler();
						g_uart_rx_frame.sta_it.bIfIt = 0;
					}
			}
			else
			{
				HAL_Delay(100);
			}
			
			if(recvlen >= len){
				break;
			}
		}
		return recvlen;
}

int atk_mw8266d_uart_rx_get_frame_Isableread(){
	if(g_uart_rx_frame.sta.len == 0){
		g_uart_rx_frame.sta.finsh = 0;
	}
	if(g_uart_rx_frame.sta.len != 0){
		g_uart_rx_frame.sta.finsh = 1;
	}
	//fang bing fa
	return g_uart_rx_frame.sta.finsh;
}
void atk_mw8266d_uart_printf_two(char *fmt, ...){
	va_list ap;
	uint16_t len;
	
	va_start(ap, fmt);
	vsprintf((char *)g_uart_tx_buf, fmt, ap);
	va_end(ap);
	
	len = strlen((const char *)g_uart_tx_buf);
	sendMsgTwo((const char *)g_uart_tx_buf , len);
}

/**
 * @brief       获取ATK-MW8266D UART接收到的一帧数据的长度
 * @param       无
 * @retval      0   : 未接收到一帧数据
 *              其他: 接收到的一帧数据的长度
 */
uint16_t atk_mw8266d_uart_rx_get_frame_len(void)
{
    if (g_uart_rx_frame.sta.finsh == 1)
    {
        return g_uart_rx_frame.sta.len;
    }
    else
    {
        return 0;
    }
}
