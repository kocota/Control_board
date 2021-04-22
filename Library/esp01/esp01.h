#ifndef ESP01
#define ESP01

#include "stm32f1xx_hal.h"

//#define AT      HAL_UART_Transmit_IT(&huart2, at, 8);
void at(void);
void AT_CIPSERVER (void);
void CIPMUX (void);
uint8_t fill_buffer (uint8_t* buffer, char str[]);
void ATD (char str[]);
void ATH0 (void);
void ATA (void);

#endif