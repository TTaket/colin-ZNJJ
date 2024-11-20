/**
 ****************************************************************************************************
 * @file        atk_mw8266d_uart.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MW8266Dģ��UART�ӿ���������
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� MiniSTM32 V4������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "stdint.h"
/* ���Ŷ��� */
//在这里改变串口
#define ATK_MW8266D_UART_TX_GPIO_PORT           GPIOA
#define ATK_MW8266D_UART_TX_GPIO_PIN            GPIO_PIN_3
#define ATK_MW8266D_UART_TX_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0) /* PC��ʱ��ʹ�� */

#define ATK_MW8266D_UART_RX_GPIO_PORT           GPIOA
#define ATK_MW8266D_UART_RX_GPIO_PIN            GPIO_PIN_2
#define ATK_MW8266D_UART_RX_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0) /* PD��ʱ��ʹ�� */

/* UART�շ������С */
#define ATK_MW8266D_UART_RX_BUF_SIZE            128
#define ATK_MW8266D_UART_TX_BUF_SIZE            64


extern uint8_t g_uart_tx_buf[ATK_MW8266D_UART_TX_BUF_SIZE]; /* ATK-MW8266D UART���ͻ��� */

/* �������� */
void atk_mw8266d_uart_printf(char *fmt, ...);       /* ATK-MW8266D UART printf */
void atk_mw8266d_uart_rx_restart(void);             /* ATK-MW8266D UART���¿�ʼ�������� */
uint8_t *atk_mw8266d_uart_rx_get_frame(void);       /* ��ȡATK-MW8266D UART���յ���һ֡���� */
uint16_t atk_mw8266d_uart_rx_get_frame_len(void);   /* ��ȡATK-MW8266D UART���յ���һ֡���ݵĳ��� */

/*user*/
int atk_mw8266d_uart_rx_get_frame_Isableread();
void atk_mw8266d_uart_printf_two(char *fmt, ...);       /* ATK-MW8266D UART printf */
int atk_mw8266d_uart_rx_get_frame_withlen(char*buf , int len);
