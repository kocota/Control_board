#include "keyboard.h"
#include "stm32f1xx_hal.h"


osThreadId KeyBoardID;

extern osMessageQId pos_Queue;
extern osTimerId DisplayTimerHandle;

extern osThreadId TimeMenuID;
extern osMutexId myMutex01Handle;
extern osThreadId TimeMenuHandle;

extern UART_HandleTypeDef huart2;

uint8_t button_state1=0;
uint8_t button_state2=0;
uint8_t button_state3=0;
uint8_t button_state4=0;
uint8_t button_state5=0;
uint8_t button_state6=0;

uint8_t dma_buf[20];
extern uint8_t read_buf[20];


// Задача для обработки клавиатуры
void Keyboard(void const * argument)
{
	KeyBoardID = osThreadGetId();
	
	for(;;)
	{
	 if(BUTTON1_READ==GPIO_PIN_RESET)
		{
			if(button_state1<2) //проверяем счетчик времени нажатия кнопки
			{
				button_state1++;
			}
			
			if(button_state1==1)
			{
				osMessagePut(pos_Queue, BUTTON1_PRESSED, 100);
				//dma_buf[0]='a';
				//dma_buf[1]='t';

				dma_buf[0]='A';
				dma_buf[1]='T';
				dma_buf[2]='+';
				dma_buf[3]='C';
				dma_buf[4]='W';
				dma_buf[5]='M';
				dma_buf[6]='O';
				dma_buf[7]='D';
				dma_buf[8]='E';
				dma_buf[9]='=';
				dma_buf[10]='1';
				dma_buf[11]='\r';
				dma_buf[12]='\n';

				HAL_UART_Transmit_DMA(&huart2, dma_buf, 13);
				HAL_UART_Receive_DMA(&huart2, read_buf, 11);
			}
		}
	 else
		{
			if(button_state1>0)
			{
				button_state1--;
			}
		}
	 if(BUTTON2_READ==GPIO_PIN_RESET)
		{
			if(button_state2<2) //проверяем счетчик времени нажатия кнопки
			{
				button_state2++;
			}
			
			if(button_state2==1)
			{
				osMessagePut(pos_Queue, BUTTON2_PRESSED, 100);



				dma_buf[0]='A';
				dma_buf[1]='T';
				dma_buf[2]='+';
				dma_buf[3]='C';
				dma_buf[4]='W';
				dma_buf[5]='J';
				dma_buf[6]='A';
				dma_buf[7]='P';
				dma_buf[8]='=';
				dma_buf[9]='"';
				dma_buf[10]='O';
				dma_buf[11]='n';
				dma_buf[12]='e';
				dma_buf[13]='P';
				dma_buf[14]='l';
				dma_buf[15]='u';
				dma_buf[16]='s';
				dma_buf[17]=' ';
				dma_buf[18]='5';
				dma_buf[19]='T';
				dma_buf[20]='"';
				dma_buf[21]=',';
				dma_buf[22]='"';
				dma_buf[23]='1';
				dma_buf[24]='1';
				dma_buf[25]='1';
				dma_buf[26]='1';
				dma_buf[27]='1';
				dma_buf[28]='1';
				dma_buf[29]='1';
				dma_buf[30]='1';
				dma_buf[31]='"';
				dma_buf[32]='\r';
				dma_buf[33]='\n';

				HAL_UART_Transmit_DMA(&huart2, dma_buf, 34);

			}
		}
	 else
		{
			if(button_state2>0)
			{
				button_state2--;
			}
		}
	 if(BUTTON3_READ==GPIO_PIN_RESET) // проверяем состояние нажатия кнопки 3
		{
			if(button_state3<2) //проверяем счетчик времени нажатия кнопки
			{
				button_state3++;
			}
			
			if(button_state3==1)
			{
				osMessagePut(pos_Queue, BUTTON3_PRESSED, 100);
			}
			
		}
	 else
		{
			if(button_state3>0)
			{
				button_state3--;
			}
		}
	 if(BUTTON4_READ==GPIO_PIN_RESET)
	 {
		if(button_state4<2) //проверяем счетчик времени нажатия кнопки
			{
				button_state4++;
			}
			
			if(button_state4==1)
			{
				osMessagePut(pos_Queue, BUTTON4_PRESSED, 100);
				//osThreadSuspend(TimeMenuHandle);
				//LED8_ON;
				//osTimerStart(DisplayTimerHandle,10000);
			} 
	 }
	 else
		{
			if(button_state4>0)
			{
				button_state4--;
			}
		}
	 if(BUTTON5_READ==GPIO_PIN_RESET) 
		{
			if(button_state5<2) //проверяем счетчик времени нажатия кнопки
			{
				button_state5++;
			}
			
			if(button_state5==1)
			{
				osMessagePut(pos_Queue, BUTTON5_PRESSED, 100);
				//osThreadSuspend(TimeMenuHandle);
				//LED8_ON;
				//osTimerStart(DisplayTimerHandle,10000);
			}
		}
	 else
		{
			if(button_state5>0)
			{
				button_state5--;
			}
		}
	 if(BUTTON6_READ==GPIO_PIN_RESET)
	 {
		 if(button_state6<2) //проверяем счетчик времени нажатия кнопки
			{
				button_state6++;
			}
			
			if(button_state6==1)
			{
				osMessagePut(pos_Queue, BUTTON6_PRESSED, 100);
				//osThreadSuspend(TimeMenuHandle);
				//LED8_ON;
				//osTimerStart(DisplayTimerHandle,10000);
			} 
	 }
	 else
		{
			if(button_state6>0)
			{
				button_state6--;
			}
		}
		
    osDelay(50);
	}



}

