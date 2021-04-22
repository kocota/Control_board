#include "esp01.h"
#include "stm32f1xx_hal.h"
#include "stdbool.h"
#include "string.h"

extern UART_HandleTypeDef huart2;

bool at_state;


uint8_t transfer_buffer[20];
uint8_t lenght_buf;
uint8_t ATE0[]="ATE0\r\n";
uint8_t ATE1[]="ATE1";
uint8_t AT[]="at\r\n";
uint8_t AT_CIFSR[]="AT+CIFSR\r\n";
uint8_t AT_CIPSERVER_1[]="AT+CIPSERVER=1\r\n";
uint8_t AT_CIPMUX[]="AT+CIPMUX=1\r\n";


uint8_t fill_buffer (uint8_t *buffer, char str[])
{
	uint8_t i;
	lenght_buf=strlen(str);
	
	for(i=0; i<lenght_buf; i++)
	{
		*(buffer+i)=str[i];		
	}
	
	return lenght_buf;
}

void at(void)
{
	at_state=true;
	fill_buffer(transfer_buffer, "at\r\n");
	//HAL_UART_Transmit_IT(&huart2, transfer_buffer, lenght_buf);
	//HAL_UART_Transmit(&huart2, transfer_buffer, lenght_buf);
	
}

void AT_CIPSERVER (void)
{
	fill_buffer(transfer_buffer,"AT+CIPSERVER=1\r\n");
	HAL_UART_Transmit_IT(&huart2, transfer_buffer, lenght_buf);

}

void CIPMUX (void)
{
	fill_buffer(transfer_buffer,"AT+CIPMUX=1\r\n");
	HAL_UART_Transmit_IT(&huart2, transfer_buffer, lenght_buf);

}

void ATD (char str[])
{
	fill_buffer(transfer_buffer, str);
	HAL_UART_Transmit_IT(&huart2, transfer_buffer, lenght_buf);
}

void ATH0 (void)
{
	fill_buffer(transfer_buffer,"ATH0\r\n");
	HAL_UART_Transmit_IT(&huart2, transfer_buffer, lenght_buf);
}

void ATA (void)
{
	fill_buffer(transfer_buffer,"ATA\r\n");
	HAL_UART_Transmit_IT(&huart2, transfer_buffer, lenght_buf);
}

