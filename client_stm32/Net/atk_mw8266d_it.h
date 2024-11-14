#pragma once
#include "main.h"
#include "stm32f1xx_it.h"
#include "./uart.h"
#include "./atk_mw8266d.h"

void ATK_MW8266d_IRQHandler(void);

void Serial_IRQHandler(void);
	