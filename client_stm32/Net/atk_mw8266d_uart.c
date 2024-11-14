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
static uint8_t g_uart_tx_buf[ATK_MW8266D_UART_TX_BUF_SIZE]; /* ATK-MW8266D UART���ͻ��� */

/**
 * @brief       ATK-MW8266D UART printf
 * @param       fmt: ����ӡ������
 * @retval      ��
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
 * @brief       ATK-MW8266D UART���¿�ʼ��������
 * @param       ��
 * @retval      ��
 */
void atk_mw8266d_uart_rx_restart(void)
{
    g_uart_rx_frame.sta.len     = 0;
    g_uart_rx_frame.sta.finsh   = 0;
}

/**
 * @brief       ��ȡATK-MW8266D UART���յ���һ֡����
 * @param       ��
 * @retval      NULL: δ���յ�һ֡����
 *              ����: ���յ���һ֡����
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
 * @brief       ��ȡ���յ���һ֡����  with len
 * @param       ��
 * @retval      NULL: δ���յ�һ֡����
 *              ����: ���յ���һ֡����
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
						//中断补偿
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
 * @brief       ��ȡATK-MW8266D UART���յ���һ֡���ݵĳ���
 * @param       ��
 * @retval      0   : δ���յ�һ֡����
 *              ����: ���յ���һ֡���ݵĳ���
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
