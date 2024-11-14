#include "./net.h"


int netinitflag = 0;
static int serverHeart = 0;
static int serverHeartCnt = 120;
static int heartCnt = 0;
static int sysTime = 0;
int sendMsg(const char *buf, int len ){
		int ret = HAL_UART_Transmit(&huart2, (const uint8_t*)buf, len, HAL_MAX_DELAY);
		if (ret != HAL_OK)
		{
				return ret;
		}
		return len;
}

int recvMsgWithLen(char *buf, int len){
    if(len == -1) {
        return -1;
    }
    if(len == 0){
        return 0;
    }

    atk_mw8266d_uart_rx_get_frame_withlen(buf , len);
}

int recvMsgTwo(char *buf, int buflen){
    int buf_readlen = 0;
    int recvlen = 0;
    recvlen = recvMsgWithLen((char *)&buf_readlen , 4); 
    if (recvlen == 0) {
        return 0;
    }
    int readlen = buf_readlen;
    if (readlen > buflen) {
        return -1;
    }
    recvlen = recvMsgWithLen(buf, readlen);
    if (recvlen == 0) {
        return 0;
    }
    return recvlen;
}
int sendMsgTwo(const char *buf, int len){
    int sendlen = len;
    int sendret = 0;
    sendret = sendMsg((char * ) & sendlen ,  4);
    if(sendret == -1){
        return -1;
    }
    sendret = sendMsg(buf , sendlen);
    if(sendret == -1){
        return -1;
    }
    return sendret;
}

int InitNet(){
	netinitflag = 0;
	unsigned char ret;
	HAL_UART_Transmit(&huart1 , (uint8_t * )"st init"		, sizeof("st init"), 1000);
	ret = atk_mw8266d_init ();
	if ( ret != 0 )
	{
			while ( 1 )
			{
					HAL_Delay ( 200 );
			}
	}
	ret += atk_mw8266d_set_mode ( 1 );                          /* Stationģʽ */
	ret += atk_mw8266d_join_ap(DEMO_WIFI_SSID, DEMO_WIFI_PWD);  /* Á¬½ӗIFI *///ʾÀý//AT+CWJAP="360WiFi-B0AC02","bc0a0caici"
	HAL_Delay(8500);
	ret += atk_mw8266d_send_at_cmd ( "AT+CIPMUX=0", "OK", 500 ); // dan tong dao 
	ret += atk_mw8266d_connect_tcp_server(DEMO_TCP_SERVER_IP_cloud, DEMO_TCP_SERVER_PORT_cloud);

	if(ret == 0) {
		HAL_UART_Transmit(&huart1 , (uint8_t * )"init success"		, sizeof("init SUCCESS"), 1000);
	}
	else {
		HAL_UART_Transmit(&huart1 , (uint8_t * )"fail"		, sizeof("fail"), 1000);
	}
		
	ret += atk_mw8266d_enter_unvarnished();
	/*start*/
	{
		atk_mw8266d_uart_printf_two ( MY_NAME );
		HAL_Delay(1000);
		/*SEND test*/
		atk_mw8266d_uart_printf_two ( "/send stm32_01 hi wo shi stm32");
		HAL_Delay(1000);
		atk_mw8266d_uart_printf_two ( "/send stm32_01 hi wo shi stm32" );
		HAL_Delay(1000);
	}
	if(ret == 0) {
		HAL_UART_Transmit(&huart1 , (uint8_t * )"net success"		, sizeof("net SUCCESS"), 1000);
	}
	else {
		HAL_UART_Transmit(&huart1 , (uint8_t * )"fail"		, sizeof("fail"), 1000);
		return -1;
	}
	
	netinitflag = 1;
	return 0;
}

int CloseNet(){
		atk_mw8266d_exit_unvarnished();
		netinitflag = 0;
		HAL_Delay(1000);
		int ret = atk_mw8266d_exit_tcp_server();
		if(ret == 0) {
			HAL_UART_Transmit(&huart1 , (uint8_t * )"net close success"		, sizeof("net close success"), 1000);
		}
		else {
			HAL_UART_Transmit(&huart1 , (uint8_t * )"net close fail"		, sizeof("net close fail"), 1000);
			return -1;
		}
		
    atk_mw8266d_uart_rx_restart();
		return 0;
}

int sendHeart(){
	if(heartCnt == 0){
		heartCnt =30;
		HAL_UART_Transmit(&huart1 , (uint8_t * )"send heart"		, sizeof("send heart"), 1000);
		atk_mw8266d_uart_printf_two("/heart");
	}
	heartCnt --;
}

int checkServerHeart(){
	if(serverHeartCnt == 0){
		serverHeartCnt = 120;
		if(sysTime - serverHeart >= 90){
			HAL_UART_Transmit(&huart1 , (uint8_t * )"server heart check fail"		, sizeof("server heart check fail"), 1000);
			CloseNet();
		}else{
			HAL_UART_Transmit(&huart1 , (uint8_t * )"server heart check succ"		, sizeof("server heart check succ"), 1000);
		}
	}
	serverHeartCnt --;
}

int setServerHeart(){
	serverHeart = sysTime;
}

int addSysTime(){
	sysTime++;
}
