/**
 ****************************************************************************************************
 * @file        atk_mw8266d.h
 * @author      ÕıµãÔ­×ÓÍÅ¶Ó(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MW8266DÄ£¿éÇı¶¯´úÂë
 * @license     Copyright (c) 2020-2032, ¹ãÖİÊĞĞÇÒíµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾
 ****************************************************************************************************
 * @attention
 *
 * ÊµÑéÆ½Ì¨:ÕıµãÔ­×Ó MiniSTM32 V4¿ª·¢°å
 * ÔÚÏßÊÓÆµ:www.yuanzige.com
 * ¼¼ÊõÂÛÌ³:www.openedv.com
 * ¹«Ë¾ÍøÖ·:www.alientek.com
 * ¹ºÂòµØÖ·:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#pragma once
#include "atk_mw8266d_uart.h"

/* Òı½Å¶¨Òå */
#define ATK_MW8266D_RST_GPIO_PORT           GPIOC
#define ATK_MW8266D_RST_GPIO_PIN            GPIO_PIN_9
#define ATK_MW8266D_RST_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* PC¿ÚÊ±ÖÓÊ¹ÄÜ */

/* IO²Ù×÷ */
#define ATK_MW8266D_RST(x)                  do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(ATK_MW8266D_RST_GPIO_PORT, ATK_MW8266D_RST_GPIO_PIN, GPIO_PIN_SET) :  \
                                                HAL_GPIO_WritePin(ATK_MW8266D_RST_GPIO_PORT, ATK_MW8266D_RST_GPIO_PIN, GPIO_PIN_RESET); \
                                            }while(0)

/* ´íÎó´úÂë */
#define ATK_MW8266D_EOK         0   /* Ã»ÓĞ´íÎó */
#define ATK_MW8266D_ERROR       1   /* Í¨ÓÃ´íÎó */
#define ATK_MW8266D_ETIMEOUT    2   /* ³¬Ê±´íÎó */
#define ATK_MW8266D_EINVAL      3   /* ²ÎÊı´íÎó */

typedef  struct
{
    uint8_t buf[ATK_MW8266D_UART_RX_BUF_SIZE];              /* Ö¡½ÓÊÕ»º³å */
    struct
    {
        uint16_t len    : 15;                               /* Ö¡½ÓÊÕ³¤¶È£¬sta[14:0] */
        uint16_t finsh  : 1;                                /* Ö¡½ÓÊÕÍê³É±êÖ¾£¬sta[15] */
    } sta; 
		struct
    {
				uint8_t bCantIt;                               /*æ˜¯å¦æ˜¯ä¸èƒ½ä¸­æ–­æ—¶é—´ */
        uint8_t bIfIt;                                 /*ä¸­é—´æ˜¯å¦å‘ç”Ÿè¿‡ä¸­æ–­ */
    } sta_it; 	 	                                     /*ä¸­æ–­çš„å¤„ç†*/
} UART_stu; 

/* ²Ù×÷º¯Êı */
void atk_mw8266d_hw_reset(void);                                            /* ATK-MW8266DÓ²¼ş¸´Î» */
uint8_t atk_mw8266d_send_at_cmd(char *cmd, char *ack, uint32_t timeout);    /* ATK-MW8266D·¢ËÍATÖ¸Áî */
uint8_t atk_mw8266d_init(void);                                /* ATK-MW8266D³õÊ¼»¯ */
uint8_t atk_mw8266d_restore(void);                                          /* ATK-MW8266D»Ö¸´³ö³§ÉèÖÃ */
uint8_t atk_mw8266d_at_test(void);                                          /* ATK-MW8266D ATÖ¸Áî²âÊÔ */
uint8_t atk_mw8266d_set_mode(uint8_t mode);                                 /* ÉèÖÃATK-MW8266D¹¤×÷Ä£Ê½ */
uint8_t atk_mw8266d_sw_reset(void);                                         /* ATK-MW8266DÈí¼ş¸´Î» */
uint8_t atk_mw8266d_ate_config(uint8_t cfg);                                /* ATK-MW8266DÉèÖÃ»ØÏÔÄ£Ê½ */
uint8_t atk_mw8266d_join_ap(char *ssid, char *pwd);                         /* ATK-MW8266DÁ¬½ÓWIFI */
uint8_t atk_mw8266d_get_ip(char *buf);                                      /* ATK-MW8266D»ñÈ¡IPµØÖ· */
uint8_t atk_mw8266d_connect_tcp_server(char *server_ip, char *server_port); /* ATK-MW8266DÁ¬½ÓTCP·şÎñÆ÷ */
uint8_t atk_mw8266d_exit_tcp_server();                                      /* ATK-MW8266D exit TCP·şÎñÆ÷ */
uint8_t atk_mw8266d_enter_unvarnished(void);                                /* ATK-MW8266D½øÈëÍ¸´« */
void atk_mw8266d_exit_unvarnished(void);                                    /* ATK-MW8266DÍË³öÍ¸´« */
uint8_t atk_mw8266d_connect_atkcld(char *id, char *pwd);                    /* ATK-MW8266DÁ¬½ÓÔ­×ÓÔÆ·şÎñÆ÷ */
uint8_t atk_mw8266d_disconnect_atkcld(void);                                /* ATK-MW8266D¶Ï¿ªÔ­×ÓÔÆ·şÎñÆ÷Á¬½Ó */
uint8_t atk_mw8266d_set_tcp_server(char *server_port);											/* ATK-MW8266D½¨Á¢TCP·şÎñÆ÷ */
uint8_t atk_mw8266d_set_AP(char *ssid, char *pwd,char *chl,char *mode);			/* ATK-MW8266D½¨Á¢APÈÈµã */
uint8_t atk_mw8266d_set_Sta_ip(char *ip, char *gataway,char *netmask);
uint8_t atk_mw8266d_set_Ap_ip(char *ip, char *gataway,char *netmask);
