#include "wifi.h"
#include "stm32f1xx_hal.h"

#include "wh0802.h"

extern osThreadId WifiTaskHandle;
extern UART_HandleTypeDef huart2;

extern osThreadId TimeMenuHandle;

uint8_t read_buf[20];


// Обработчик задачи Wifi
void WifiTask(void const * argument)
{
	
	osThreadSuspend(WifiTaskHandle); // Приостанавливаем задачу

	//wh0802_set_ddram_address(0x40);
	//wh0802_write_data_to_ram(*&read_buf[0]);
	//wh0802_write_data_to_ram(*&read_buf[1]);
	//wh0802_write_data_to_ram(*&read_buf[2]);
	//wh0802_write_data_to_ram(*&read_buf[3]);
	//wh0802_write_data_to_ram(*&read_buf[4]);

	
	for(;;)
	{
		osThreadSuspend(TimeMenuHandle);
		wh0802_write_to_display(0x00, read_buf, CLEAR_ON);
		osThreadSuspend(WifiTaskHandle);
		//HAL_UART_Receive_DMA(&huart2, read_buf, 1);
		//osThreadSuspend(WifiTaskHandle);
		
    	//osDelay(5);
	}



}

