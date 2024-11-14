/**
 ****************************************************************************************************
 * @file        atk_mw8266d.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MW8266Dģ����������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
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

#pragma once
#include "atk_mw8266d_uart.h"

/* ���Ŷ��� */
#define ATK_MW8266D_RST_GPIO_PORT           GPIOC
#define ATK_MW8266D_RST_GPIO_PIN            GPIO_PIN_9
#define ATK_MW8266D_RST_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* PC��ʱ��ʹ�� */

/* IO���� */
#define ATK_MW8266D_RST(x)                  do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(ATK_MW8266D_RST_GPIO_PORT, ATK_MW8266D_RST_GPIO_PIN, GPIO_PIN_SET) :  \
                                                HAL_GPIO_WritePin(ATK_MW8266D_RST_GPIO_PORT, ATK_MW8266D_RST_GPIO_PIN, GPIO_PIN_RESET); \
                                            }while(0)

/* ������� */
#define ATK_MW8266D_EOK         0   /* û�д��� */
#define ATK_MW8266D_ERROR       1   /* ͨ�ô��� */
#define ATK_MW8266D_ETIMEOUT    2   /* ��ʱ���� */
#define ATK_MW8266D_EINVAL      3   /* �������� */

typedef  struct
{
    uint8_t buf[ATK_MW8266D_UART_RX_BUF_SIZE];              /* ֡���ջ��� */
    struct
    {
        uint16_t len    : 15;                               /* ֡���ճ��ȣ�sta[14:0] */
        uint16_t finsh  : 1;                                /* ֡������ɱ�־��sta[15] */
    } sta; 
		struct
    {
				uint8_t bCantIt;                               /*是否是不能中断时间 */
        uint8_t bIfIt;                                 /*中间是否发生过中断 */
    } sta_it; 	 	                                     /*中断的处理*/
} UART_stu; 

/* �������� */
void atk_mw8266d_hw_reset(void);                                            /* ATK-MW8266DӲ����λ */
uint8_t atk_mw8266d_send_at_cmd(char *cmd, char *ack, uint32_t timeout);    /* ATK-MW8266D����ATָ�� */
uint8_t atk_mw8266d_init(void);                                /* ATK-MW8266D��ʼ�� */
uint8_t atk_mw8266d_restore(void);                                          /* ATK-MW8266D�ָ��������� */
uint8_t atk_mw8266d_at_test(void);                                          /* ATK-MW8266D ATָ����� */
uint8_t atk_mw8266d_set_mode(uint8_t mode);                                 /* ����ATK-MW8266D����ģʽ */
uint8_t atk_mw8266d_sw_reset(void);                                         /* ATK-MW8266D�����λ */
uint8_t atk_mw8266d_ate_config(uint8_t cfg);                                /* ATK-MW8266D���û���ģʽ */
uint8_t atk_mw8266d_join_ap(char *ssid, char *pwd);                         /* ATK-MW8266D����WIFI */
uint8_t atk_mw8266d_get_ip(char *buf);                                      /* ATK-MW8266D��ȡIP��ַ */
uint8_t atk_mw8266d_connect_tcp_server(char *server_ip, char *server_port); /* ATK-MW8266D����TCP������ */
uint8_t atk_mw8266d_exit_tcp_server();                                      /* ATK-MW8266D exit TCP������ */
uint8_t atk_mw8266d_enter_unvarnished(void);                                /* ATK-MW8266D����͸�� */
void atk_mw8266d_exit_unvarnished(void);                                    /* ATK-MW8266D�˳�͸�� */
uint8_t atk_mw8266d_connect_atkcld(char *id, char *pwd);                    /* ATK-MW8266D����ԭ���Ʒ����� */
uint8_t atk_mw8266d_disconnect_atkcld(void);                                /* ATK-MW8266D�Ͽ�ԭ���Ʒ��������� */
uint8_t atk_mw8266d_set_tcp_server(char *server_port);											/* ATK-MW8266D����TCP������ */
uint8_t atk_mw8266d_set_AP(char *ssid, char *pwd,char *chl,char *mode);			/* ATK-MW8266D����AP�ȵ� */
uint8_t atk_mw8266d_set_Sta_ip(char *ip, char *gataway,char *netmask);
uint8_t atk_mw8266d_set_Ap_ip(char *ip, char *gataway,char *netmask);
