#include "./atk_mw8266d.h"
#include "./atk_mw8266d_uart.h"
#include "./uart.h"
#include "main.h"
#include "usart.h"
#include "gpio.h"

#define DEMO_TCP_SERVER_IP_cloud      "106.54.203.31"
#define DEMO_TCP_SERVER_PORT_cloud    "8159"
#define DEMO_WIFI_SSID          "CMCC-32A01"
#define DEMO_WIFI_PWD           "zm205801"
#define MY_NAME  "stm32_01"

int sendMsg(const char *buf, int len );

int recvMsg(char *buf, int len);

int recvMsgWithLen(char *buf, int len);

int recvMsgTwo(char *buf, int len);

int sendMsgTwo(const  char *buf, int len);

int InitNet();
int CloseNet();
int sendHeart();
int checkServerHeart();
int setServerHeart();
int addSysTime();
extern int netinitflag;