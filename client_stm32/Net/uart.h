#pragma once
#define Uart_Max_Length 128
typedef struct{
	int length;
	int flag_finish;
	char buffer[Uart_Max_Length];
}uart_it_frame;


void deluartinfo();