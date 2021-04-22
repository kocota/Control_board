#include "display.h"
#include "stm32f1xx_hal.h"
#include "wh0802.h"
#include "keyboard.h"
#include "menu.h"
#include "stdlib.h"


extern RTC_HandleTypeDef hrtc;
extern osMessageQId pos_Queue;
extern osTimerId DisplayTimerHandle;
extern DirectionMenu MenuItem[MAX_ITEM];
extern uint8_t PositionState;
extern osMutexId myMutex01Handle;
extern osSemaphoreId myBinarySem01Handle;
extern osThreadId DisplayHandle;
extern osThreadId TimeMenuHandle;
extern osThreadId TimeTaskHandle;
extern osThreadId DateTaskHandle;
extern osThreadId TimeDisplayTaskHandle;
extern osThreadId DateDisplayTaskHandle;
extern uint8_t Desktop;


RTC_TimeTypeDef Time;
RTC_DateTypeDef Date;
char Hour[2];
char Minute[2];
char Second[2];
//osThreadId TimeMenuID;
//osThreadId DisplayID;
//osThreadId TimeTaskID;
uint8_t ddram=0;
uint8_t desktop_time_state = DESKTOP_TIME_ON;
uint8_t desktop_date_state = DESKTOP_DATE_ON;


// Задача для обработки изображения на дисплее
void Display(void const * argument)
{
	osEvent event;
	menu_ini(); // Инициализируем состояние меню на дисплее.
	
	for(;;)
	{
		event = osMessageGet(pos_Queue, 100);
		if (event.status == osEventMessage)
		{
// Обработчик нажатия кнопки BUTTON1 меню дисплея----------------------
			if(event.value.v==BUTTON1_PRESSED)
			{
				switch(Desktop)
				{
					//case DESKTOP_ON:
						//LED8_ON;
						//Desktop = DESKTOP_OFF;
						//PositionState = 0;
						//osThreadSuspend(TimeMenuHandle);
						//wh0802_write_to_display(0x00, MenuItem[PositionState].NameItem, CLEAR_ON);
						//osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
					//break;
					case DESKTOP_OFF:
						switch(PositionState)
						{
							case 6:
								LED8_ON;
								osTimerStop(DisplayTimerHandle);
								ddram=0x01;
								wh0802_set_ddram_address(ddram);
								wh0802_display_control(DISPLAY_ON, CURSOR_ON, BLINKING_ON);
								osThreadResume(TimeTaskHandle);
								osThreadSuspend(DisplayHandle);
							break;
							case 14:
								LED8_ON;
								osTimerStop(DisplayTimerHandle);
								ddram=0x01;
								wh0802_set_ddram_address(ddram);
								wh0802_display_control(DISPLAY_ON, CURSOR_ON, BLINKING_ON);
								osThreadResume(DateTaskHandle);
								osThreadSuspend(DisplayHandle);
							break;
							case 15:
								LED8_ON;
								osTimerStop(DisplayTimerHandle);
								ddram=0x00;
								wh0802_set_ddram_address(ddram);
								wh0802_display_control(DISPLAY_ON, CURSOR_ON, BLINKING_ON);
								osThreadResume(TimeDisplayTaskHandle);
								osThreadSuspend(DisplayHandle);
							break;
							case 16:
								LED8_ON;
								osTimerStop(DisplayTimerHandle);
								ddram=0x00;
								wh0802_set_ddram_address(ddram);
								wh0802_display_control(DISPLAY_ON, CURSOR_ON, BLINKING_ON);
								osThreadResume(DateDisplayTaskHandle);
								osThreadSuspend(DisplayHandle);
							break;
							//default:
								//osTimerStop(DisplayTimerHandle);
								//LED8_OFF;
								//Desktop = DESKTOP_ON;
								//PositionState = 0;
								//osThreadResume(TimeMenuHandle);
								//wh0802_clear_display();
						}
					break;
				}
			}
//-----------------------------------------------------

//Обработчик нажатия кнопки BUTTON2 меню дисплея--------------------
			if(event.value.v==BUTTON2_PRESSED)
			{
				switch(Desktop)
				{
					//case DESKTOP_ON:
						//LED8_ON;
						//Desktop = DESKTOP_OFF;
						//PositionState = 0;
						//osThreadSuspend(TimeMenuHandle);
						//wh0802_write_to_display(0x00, MenuItem[PositionState].NameItem, CLEAR_ON);
						//osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
					//break;
					case DESKTOP_OFF:
						osTimerStop(DisplayTimerHandle);
						LED8_OFF;
						Desktop = DESKTOP_ON;
						PositionState = 0;
						osThreadResume(TimeMenuHandle);
						wh0802_clear_display();
						//osThreadSuspend(TimeMenuHandle);
						//LED8_ON;
						//osTimerStart(DisplayTimerHandle,10000);
					break;
				}
			}
//-----------------------------------------------------

//Обработчик нажатия кнопки BUTTON3 меню дисплея--------------------
			if(event.value.v==BUTTON3_PRESSED)
			{
				switch(Desktop)
				{
					case DESKTOP_ON:
						LED8_ON;
						Desktop = DESKTOP_OFF;
						PositionState = 0;
						osThreadSuspend(TimeMenuHandle);
						wh0802_write_to_display(0x00, MenuItem[PositionState].NameItem, CLEAR_ON);
						osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
					break;
					case DESKTOP_OFF:
						switch(PositionState)
						{
							case 6:
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							case 14:
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							case 15:
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							case 16:
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							default:
								LED8_ON;
								PositionState = MenuItem[PositionState].Down;
								wh0802_write_to_display(0x00, MenuItem[PositionState].NameItem, CLEAR_ON);
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
						}
					break;
				}
			}
//-----------------------------------------------------

//Обработчик нажатия кнопки BUTTON4 меню дислея--------------------
			if(event.value.v==BUTTON4_PRESSED)
			{
				switch(Desktop)
				{
					case DESKTOP_ON:
						LED8_ON;
						Desktop = DESKTOP_OFF;
						PositionState = 0;
						osThreadSuspend(TimeMenuHandle);
						wh0802_write_to_display(0x00, MenuItem[PositionState].NameItem, CLEAR_ON);
						osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
					break;
					case DESKTOP_OFF:
						switch(PositionState)
						{
							default:
								LED8_ON;
								PositionState = MenuItem[PositionState].Previous;
								wh0802_write_to_display(0x00, MenuItem[PositionState].NameItem, CLEAR_ON);
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
						}
					break;
				}
			}
//-----------------------------------------------------

//Обработчик нажатия кнопки BUTTON5 меню дисплея--------------------
			if(event.value.v==BUTTON5_PRESSED)
			{
				switch(Desktop)
				{
					case DESKTOP_ON:
						LED8_ON;
						Desktop = DESKTOP_OFF;
						PositionState = 0;
						osThreadSuspend(TimeMenuHandle);
						wh0802_write_to_display(0x00, MenuItem[PositionState].NameItem, CLEAR_ON);
						osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
					break;
					case DESKTOP_OFF:
						switch(PositionState)
						{
							case 6:
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							case 14:
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							case 15:
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							case 16:
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							default:
								LED8_ON;
								PositionState = MenuItem[PositionState].Up;
								wh0802_write_to_display(0x00, MenuItem[PositionState].NameItem, CLEAR_ON);
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
						}
					break;
				}
			}
//-----------------------------------------------------

//Обработчик нажатия кнопки BUTTON6 меню дисплея--------------------
			if(event.value.v==BUTTON6_PRESSED)
			{
				switch(Desktop)
				{
					case DESKTOP_ON:
						LED8_ON;
						Desktop = DESKTOP_OFF;
						PositionState = 0;
						osThreadSuspend(TimeMenuHandle);
						wh0802_write_to_display(0x00, MenuItem[PositionState].NameItem, CLEAR_ON);
						osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
					break;
					case DESKTOP_OFF:
						switch(PositionState)
						{
							case 12:
								Time.Hours = 0x23;
								Time.Minutes = 0x59;
								Time.Seconds = 0x59;
								PositionState = 6;
								wh0802_clear_display();
								wh0802_set_ddram_address(0x00);
								wh0802_write_data_to_ram( 0x30| ((Time.Hours>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Hours&0x0F) );
								wh0802_write_data_to_ram(':');
								wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
								wh0802_write_data_to_ram(':');
								wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
								wh0802_set_ddram_address(0x40);
								wh0802_write_data_to_ram('h');
								wh0802_write_data_to_ram('h');
								wh0802_write_data_to_ram(':');
								wh0802_write_data_to_ram('m');
								wh0802_write_data_to_ram('m');
								wh0802_write_data_to_ram(':');
								wh0802_write_data_to_ram('s');
								wh0802_write_data_to_ram('s');
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							case 13:
								Date.Date=0x01;
								Date.Month=0x01;
								Date.Year=0x00;
								PositionState = 14;
								wh0802_clear_display();
								wh0802_set_ddram_address(0x00);
								wh0802_write_data_to_ram( 0x30| ((Date.Date>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Date&0x0F) );
								wh0802_write_data_to_ram(':');
								wh0802_write_data_to_ram( 0x30| ((Date.Month>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Month&0x0F) );
								wh0802_write_data_to_ram(':');
								wh0802_write_data_to_ram( 0x30| ((Date.Year>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Year&0x0F) );
								wh0802_set_ddram_address(0x40);
								wh0802_write_data_to_ram('d');
								wh0802_write_data_to_ram('d');
								wh0802_write_data_to_ram(':');
								wh0802_write_data_to_ram('m');
								wh0802_write_data_to_ram('m');
								wh0802_write_data_to_ram(':');
								wh0802_write_data_to_ram('y');
								wh0802_write_data_to_ram('y');
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							case 3:
								PositionState = 15;
								wh0802_clear_display();
								if(desktop_time_state==DESKTOP_TIME_ON)
								{
									wh0802_set_ddram_address(0x00);
									wh0802_write_data_to_ram('O');
									wh0802_write_data_to_ram('N');
								}
								else
								{
									wh0802_set_ddram_address(0x00);
									wh0802_write_data_to_ram('O');
									wh0802_write_data_to_ram('F');
									wh0802_write_data_to_ram('F');
								}
							break;
							case 4:
								PositionState = 16;
								wh0802_clear_display();
								if(desktop_date_state==DESKTOP_DATE_ON)
								{
									wh0802_set_ddram_address(0x00);
									wh0802_write_data_to_ram('O');
									wh0802_write_data_to_ram('N');
								}
								else
								{
									wh0802_set_ddram_address(0x00);
									wh0802_write_data_to_ram('O');
									wh0802_write_data_to_ram('F');
									wh0802_write_data_to_ram('F');
								}
							break;
							case 15:
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							case 16:
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							case 6:
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							case 14:
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
							break;
							default:
								LED8_ON;
								PositionState = MenuItem[PositionState].Next;
								wh0802_write_to_display(0x00, MenuItem[PositionState].NameItem, CLEAR_ON);
								osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
						}
					break;
				}
			}
//-----------------------------------------------------
		}
	}
}

// Задача для обработки меню времени
void TimeMenu(void const * argument)
{


	for(;;)
	{
		if(desktop_time_state == DESKTOP_TIME_ON)
		{
			HAL_RTC_GetTime(&hrtc, &Time, RTC_FORMAT_BCD);
			wh0802_set_ddram_address(0x00);
			wh0802_write_data_to_ram( 0x30| ((Time.Hours>>4)&0x0F) );
			wh0802_write_data_to_ram( 0x30| (Time.Hours&0x0F) );
			wh0802_write_data_to_ram(':');
			wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
			wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
			wh0802_write_data_to_ram(':');
			wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
			wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
		}
		else
		{
			wh0802_set_ddram_address(0x00);
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
		}
		if(desktop_date_state == DESKTOP_DATE_ON)
		{
			HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BCD);
			wh0802_set_ddram_address(0x40);
			wh0802_write_data_to_ram( 0x30| ((Date.Date>>4)&0x0F) );
			wh0802_write_data_to_ram( 0x30| (Date.Date&0x0F) );
			wh0802_write_data_to_ram('-');
			wh0802_write_data_to_ram( 0x30| ((Date.Month>>4)&0x0F) );
			wh0802_write_data_to_ram( 0x30| (Date.Month&0x0F) );
			wh0802_write_data_to_ram('-');
			wh0802_write_data_to_ram( 0x30| ((Date.Year>>4)&0x0F) );
			wh0802_write_data_to_ram( 0x30| (Date.Year&0x0F) );
		}
		else
		{
			wh0802_set_ddram_address(0x40);
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
			wh0802_write_data_to_ram(' ');
		}

		osDelay(100);
	}
}

// Обработчик задачи установки времени
void TimeTask(void const * argument)
{
	osEvent event1;
	osThreadSuspend(TimeTaskHandle); // Приостанавливаем задачу

	for(;;)
	{
		event1 = osMessageGet(pos_Queue, 100);
		if (event1.status == osEventMessage)
		{
			if(event1.value.v==BUTTON1_PRESSED)
			{

			}
			if(event1.value.v==BUTTON2_PRESSED)
			{
				LED8_OFF;
				wh0802_display_control(DISPLAY_ON, CURSOR_OFF, BLINKING_OFF);
				HAL_RTC_SetTime(&hrtc, &Time, RTC_FORMAT_BCD);
				osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
				osThreadResume(DisplayHandle);
				osThreadSuspend(TimeTaskHandle);

			}
			if(event1.value.v==BUTTON3_PRESSED)
			{
				if(ddram==0x01)
				{
					if(Time.Hours>0x00)
					{
						if((Time.Hours&0x0F)>0x00)
						{
							Time.Hours--;
							wh0802_set_ddram_address(0x00);
							wh0802_write_data_to_ram( 0x30| ((Time.Hours>>4)&0x0F) );
							wh0802_write_data_to_ram( 0x30| (Time.Hours&0x0F) );
							wh0802_set_ddram_address(0x01);
						}
						else
						{
							if(Time.Hours==0x20)
							{
								Time.Hours=0x19;
								wh0802_set_ddram_address(0x00);
								wh0802_write_data_to_ram( 0x30| ((Time.Hours>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Hours&0x0F) );
								wh0802_set_ddram_address(0x01);
							}
							if(Time.Hours==0x10)
							{
								Time.Hours=0x09;
								wh0802_set_ddram_address(0x00);
								wh0802_write_data_to_ram( 0x30| ((Time.Hours>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Hours&0x0F) );
								wh0802_set_ddram_address(0x01);
							}
						}
					}
				}
				if(ddram==0x04)
				{
					if(Time.Minutes>0x00)
					{
						if((Time.Minutes&0x0F)>0x00)
						{
							Time.Minutes--;
							wh0802_set_ddram_address(0x03);
							wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
							wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
							wh0802_set_ddram_address(0x04);
						}
						else
						{
							if(Time.Minutes==0x10)
							{
								Time.Minutes=0x09;
								wh0802_set_ddram_address(0x03);
								wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
								wh0802_set_ddram_address(0x04);
							}
							if(Time.Minutes==0x20)
							{
								Time.Minutes=0x19;
								wh0802_set_ddram_address(0x03);
								wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
								wh0802_set_ddram_address(0x04);
							}
							if(Time.Minutes==0x30)
							{
								Time.Minutes=0x29;
								wh0802_set_ddram_address(0x03);
								wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
								wh0802_set_ddram_address(0x04);
							}
							if(Time.Minutes==0x40)
							{
								Time.Minutes=0x39;
								wh0802_set_ddram_address(0x03);
								wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
								wh0802_set_ddram_address(0x04);
							}
							if(Time.Minutes==0x50)
							{
								Time.Minutes=0x49;
								wh0802_set_ddram_address(0x03);
								wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
								wh0802_set_ddram_address(0x04);
							}
							if(Time.Minutes==0x60)
							{
								Time.Minutes=0x59;
								wh0802_set_ddram_address(0x03);
								wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
								wh0802_set_ddram_address(0x04);
							}
						}
					}
				}
				if(ddram==0x07)
				{
					if(Time.Seconds>0x00)
					{
						if((Time.Seconds&0x0F)>0x00)
						{
							Time.Seconds--;
							wh0802_set_ddram_address(0x06);
							wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
							wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
							wh0802_set_ddram_address(0x07);
						}
						else
						{
							if(Time.Seconds==0x10)
							{
								Time.Seconds=0x09;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
							if(Time.Seconds==0x20)
							{
								Time.Seconds=0x19;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
							if(Time.Seconds==0x30)
							{
								Time.Seconds=0x29;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
							if(Time.Seconds==0x40)
							{
								Time.Seconds=0x39;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
							if(Time.Seconds==0x50)
							{
								Time.Seconds=0x49;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
							if(Time.Seconds==0x60)
							{
								Time.Seconds=0x59;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
						}
					}
				}
			}
			if(event1.value.v==BUTTON4_PRESSED)
			{
				if((ddram==0x04||ddram==0x07))
				{
					ddram=ddram-0x03;
				}
				wh0802_set_ddram_address(ddram);
			}
			if(event1.value.v==BUTTON5_PRESSED)
			{
				if(ddram==0x01)
				{
					if(Time.Hours<0x23)
					{
						if((Time.Hours&0x0F)<0x09)
						{
							Time.Hours++;
							wh0802_set_ddram_address(0x00);
							wh0802_write_data_to_ram( 0x30| ((Time.Hours>>4)&0x0F) );
							wh0802_write_data_to_ram( 0x30| (Time.Hours&0x0F) );
							wh0802_set_ddram_address(0x01);
						}
						else
						{
							if(Time.Hours==0x09)
							{
								Time.Hours=0x10;
								wh0802_set_ddram_address(0x00);
								wh0802_write_data_to_ram( 0x30| ((Time.Hours>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Hours&0x0F) );
								wh0802_set_ddram_address(0x01);
							}
							if(Time.Hours==0x19)
							{
								Time.Hours=0x20;
								wh0802_set_ddram_address(0x00);
								wh0802_write_data_to_ram( 0x30| ((Time.Hours>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Hours&0x0F) );
								wh0802_set_ddram_address(0x01);
							}
						}
					}
				}
				if(ddram==0x04)
				{
					if(Time.Minutes<0x59)
					{
						if((Time.Minutes&0x0F)<0x09)
						{
							Time.Minutes++;
							wh0802_set_ddram_address(0x03);
							wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
							wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
							wh0802_set_ddram_address(0x04);
						}
						else
						{
							if(Time.Minutes==0x09)
							{
								Time.Minutes=0x10;
								wh0802_set_ddram_address(0x03);
								wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
								wh0802_set_ddram_address(0x04);
							}
							if(Time.Minutes==0x19)
							{
								Time.Minutes=0x20;
								wh0802_set_ddram_address(0x03);
								wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
								wh0802_set_ddram_address(0x04);
							}
							if(Time.Minutes==0x29)
							{
								Time.Minutes=0x30;
								wh0802_set_ddram_address(0x03);
								wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
								wh0802_set_ddram_address(0x04);
							}
							if(Time.Minutes==0x39)
							{
								Time.Minutes=0x40;
								wh0802_set_ddram_address(0x03);
								wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
								wh0802_set_ddram_address(0x04);
							}
							if(Time.Minutes==0x49)
							{
								Time.Minutes=0x50;
								wh0802_set_ddram_address(0x03);
								wh0802_write_data_to_ram( 0x30| ((Time.Minutes>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Minutes&0x0F) );
								wh0802_set_ddram_address(0x04);
							}
						}
					}
				}
				if(ddram==0x07)
				{
					if(Time.Seconds<0x59)
					{
						if((Time.Seconds&0x0F)<0x09)
						{
							Time.Seconds++;
							wh0802_set_ddram_address(0x06);
							wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
							wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
							wh0802_set_ddram_address(0x07);
						}
						else
						{
							if(Time.Seconds==0x09)
							{
								Time.Seconds=0x10;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
							if(Time.Seconds==0x19)
							{
								Time.Seconds=0x20;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
							if(Time.Seconds==0x29)
							{
								Time.Seconds=0x30;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
							if(Time.Seconds==0x39)
							{
								Time.Seconds=0x40;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
							if(Time.Seconds==0x49)
							{
								Time.Seconds=0x50;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Time.Seconds>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Time.Seconds&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
						}
					}
				}
			}
			if(event1.value.v==BUTTON6_PRESSED)
			{
				if((ddram==0x01||ddram==0x04))
				{
					ddram=ddram+0x03;
				}
				wh0802_set_ddram_address(ddram);
			}

		}

	}

}

// Обработчик задачи установки даты
void DateTask(void const * argument)
{
	osEvent event2;
	osThreadSuspend(DateTaskHandle); // Приостанавливаем задачу

	for(;;)
	{
		event2 = osMessageGet(pos_Queue, 100);
		if (event2.status == osEventMessage)
		{
			if(event2.value.v==BUTTON1_PRESSED)
			{

			}
			if(event2.value.v==BUTTON2_PRESSED)
			{
				LED8_OFF;
				wh0802_display_control(DISPLAY_ON, CURSOR_OFF, BLINKING_OFF);
				HAL_RTC_SetDate(&hrtc, &Date, RTC_FORMAT_BCD);
				osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
				osThreadResume(DisplayHandle);
				osThreadSuspend(DateTaskHandle);
			}
			if(event2.value.v==BUTTON3_PRESSED)
			{
				if(ddram==0x01)
				{
					if(Date.Date>0x01)
					{
						if((Date.Date&0x0F)>0x00)
						{
							Date.Date--;
							wh0802_set_ddram_address(0x00);
							wh0802_write_data_to_ram( 0x30| ((Date.Date>>4)&0x0F) );
							wh0802_write_data_to_ram( 0x30| (Date.Date&0x0F) );
							wh0802_set_ddram_address(0x01);
						}
						else
						{
							if(Date.Date==0x30)
							{
								Date.Date=0x29;
								wh0802_set_ddram_address(0x00);
								wh0802_write_data_to_ram( 0x30| ((Date.Date>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Date&0x0F) );
								wh0802_set_ddram_address(0x01);
							}
							if(Date.Date==0x20)
							{
								Date.Date=0x19;
								wh0802_set_ddram_address(0x00);
								wh0802_write_data_to_ram( 0x30| ((Date.Date>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Date&0x0F) );
								wh0802_set_ddram_address(0x01);
							}
							if(Date.Date==0x10)
							{
								Date.Date=0x09;
								wh0802_set_ddram_address(0x00);
								wh0802_write_data_to_ram( 0x30| ((Date.Date>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Date&0x0F) );
								wh0802_set_ddram_address(0x01);
							}
						}
					}
				}
				if(ddram==0x04)
				{
					if(Date.Month>0x01)
					{
						if((Date.Month&0x0F)>0x00)
						{
							Date.Month--;
							wh0802_set_ddram_address(0x03);
							wh0802_write_data_to_ram( 0x30| ((Date.Month>>4)&0x0F) );
							wh0802_write_data_to_ram( 0x30| (Date.Month&0x0F) );
							wh0802_set_ddram_address(0x04);
						}
						else
						{
							if(Date.Month==0x10)
							{
								Date.Month=0x09;
								wh0802_set_ddram_address(0x03);
								wh0802_write_data_to_ram( 0x30| ((Date.Month>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Month&0x0F) );
								wh0802_set_ddram_address(0x04);
							}
						}
					}
				}
				if(ddram==0x07)
				{
					if(Date.Year>0x00)
					{
						if((Date.Year&0x0F)>0x00)
						{
							Date.Year--;
							wh0802_set_ddram_address(0x06);
							wh0802_write_data_to_ram( 0x30| ((Date.Year>>4)&0x0F) );
							wh0802_write_data_to_ram( 0x30| (Date.Year&0x0F) );
							wh0802_set_ddram_address(0x07);
						}
						else
						{
							if(Date.Year==0x30)
							{
								Date.Year=0x29;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Date.Year>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Year&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
							if(Date.Year==0x20)
							{
								Date.Year=0x19;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Date.Year>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Year&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
							if(Date.Year==0x10)
							{
								Date.Year=0x09;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Date.Year>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Year&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
						}
					}
				}
			}
			if(event2.value.v==BUTTON4_PRESSED)
			{
				if((ddram==0x04||ddram==0x07))
				{
					ddram=ddram-0x03;
				}
				wh0802_set_ddram_address(ddram);
			}
			if(event2.value.v==BUTTON5_PRESSED)
			{
				if(ddram==0x01)
				{
					if( (Date.Date<0x31)&&( (Date.Month==0x01)||(Date.Month==0x03)||(Date.Month==0x05)||(Date.Month==0x07)||(Date.Month==0x08)||(Date.Month==0x10)||(Date.Month==0x12) ) )
					{
						if((Date.Date&0x0F)<0x09)
						{
							Date.Date++;
							wh0802_set_ddram_address(0x00);
							wh0802_write_data_to_ram( 0x30| ((Date.Date>>4)&0x0F) );
							wh0802_write_data_to_ram( 0x30| (Date.Date&0x0F) );
							wh0802_set_ddram_address(0x01);
						}
						else
						{
							if(Date.Date==0x09)
							{
								Date.Date=0x10;
								wh0802_set_ddram_address(0x00);
								wh0802_write_data_to_ram( 0x30| ((Date.Date>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Date&0x0F) );
								wh0802_set_ddram_address(0x01);
							}
							if(Date.Date==0x19)
							{
								Date.Date=0x20;
								wh0802_set_ddram_address(0x00);
								wh0802_write_data_to_ram( 0x30| ((Date.Date>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Date&0x0F) );
								wh0802_set_ddram_address(0x01);
							}
							if(Date.Date==0x29)
							{
								Date.Date=0x30;
								wh0802_set_ddram_address(0x00);
								wh0802_write_data_to_ram( 0x30| ((Date.Date>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Date&0x0F) );
								wh0802_set_ddram_address(0x01);
							}
						}
					}
				}
				if(ddram==0x04)
				{
					if(Date.Month<0x12)
					{
						if((Date.Month&0x0F)<0x09)
						{
							Date.Month++;
							wh0802_set_ddram_address(0x03);
							wh0802_write_data_to_ram( 0x30| ((Date.Month>>4)&0x0F) );
							wh0802_write_data_to_ram( 0x30| (Date.Month&0x0F) );
							wh0802_set_ddram_address(0x04);
						}
						else
						{
							if(Date.Month==0x09)
							{
								Date.Month=0x10;
								wh0802_set_ddram_address(0x03);
								wh0802_write_data_to_ram( 0x30| ((Date.Month>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Month&0x0F) );
								wh0802_set_ddram_address(0x04);
							}
						}
					}
				}
				if(ddram==0x07)
				{
					if(Date.Year<0x36)
					{
						if((Date.Year&0x0F)<0x09)
						{
							Date.Year++;
							wh0802_set_ddram_address(0x06);
							wh0802_write_data_to_ram( 0x30| ((Date.Year>>4)&0x0F) );
							wh0802_write_data_to_ram( 0x30| (Date.Year&0x0F) );
							wh0802_set_ddram_address(0x07);
						}
						else
						{
							if(Date.Year==0x09)
							{
								Date.Year=0x10;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Date.Year>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Year&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
							if(Date.Year==0x19)
							{
								Date.Year=0x20;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Date.Year>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Year&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
							if(Date.Year==0x29)
							{
								Date.Year=0x30;
								wh0802_set_ddram_address(0x06);
								wh0802_write_data_to_ram( 0x30| ((Date.Year>>4)&0x0F) );
								wh0802_write_data_to_ram( 0x30| (Date.Year&0x0F) );
								wh0802_set_ddram_address(0x07);
							}
						}
					}
				}
			}
			if(event2.value.v==BUTTON6_PRESSED)
			{
				if((ddram==0x01||ddram==0x04))
				{
					ddram=ddram+0x03;
				}
				wh0802_set_ddram_address(ddram);
			}
		}
	}

}

// Обработчик задачи установки времени на дисплее
void TimeDisplayTask(void const * argument)
{
	osEvent event3;
	osThreadSuspend(TimeDisplayTaskHandle); // Приостанавливаем задачу

	for(;;)
	{
		event3 = osMessageGet(pos_Queue, 100);
		if (event3.status == osEventMessage)
		{
			if(event3.value.v==BUTTON2_PRESSED)
			{
				LED8_OFF;
				wh0802_display_control(DISPLAY_ON, CURSOR_OFF, BLINKING_OFF);
				osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
				osThreadResume(DisplayHandle);
				osThreadSuspend(TimeDisplayTaskHandle);
			}
			if(event3.value.v==BUTTON3_PRESSED)
			{
				if(desktop_time_state==DESKTOP_TIME_ON)
				{
					desktop_time_state = DESKTOP_TIME_OFF;
					wh0802_clear_display();
					wh0802_set_ddram_address(0x00);
					wh0802_write_data_to_ram('O');
					wh0802_write_data_to_ram('F');
					wh0802_write_data_to_ram('F');
					wh0802_set_ddram_address(0x00);
				}
				else
				{
					desktop_time_state = DESKTOP_TIME_ON;
					wh0802_clear_display();
					wh0802_set_ddram_address(0x00);
					wh0802_write_data_to_ram('O');
					wh0802_write_data_to_ram('N');
					wh0802_set_ddram_address(0x00);
				}
			}
			if(event3.value.v==BUTTON5_PRESSED)
			{
				if(desktop_time_state==DESKTOP_TIME_ON)
				{
					desktop_time_state = DESKTOP_TIME_OFF;
					wh0802_clear_display();
					wh0802_set_ddram_address(0x00);
					wh0802_write_data_to_ram('O');
					wh0802_write_data_to_ram('F');
					wh0802_write_data_to_ram('F');
					wh0802_set_ddram_address(0x00);
				}
				else
				{
					desktop_time_state = DESKTOP_TIME_ON;
					wh0802_clear_display();
					wh0802_set_ddram_address(0x00);
					wh0802_write_data_to_ram('O');
					wh0802_write_data_to_ram('N');
					wh0802_set_ddram_address(0x00);
				}
			}
		}
	}
}

// Обработчик задачи установки даты на дисплее
void DateDisplayTask(void const * argument)
{
	osEvent event4;
	osThreadSuspend(DateDisplayTaskHandle); // Приостанавливаем задачу

	for(;;)
	{
		event4 = osMessageGet(pos_Queue, 100);
		if (event4.status == osEventMessage)
		{
			if(event4.value.v==BUTTON2_PRESSED)
			{
				LED8_OFF;
				wh0802_display_control(DISPLAY_ON, CURSOR_OFF, BLINKING_OFF);
				osTimerStart(DisplayTimerHandle,DISPLAY_TIMER);
				osThreadResume(DisplayHandle);
				osThreadSuspend(DateDisplayTaskHandle);
			}
			if(event4.value.v==BUTTON3_PRESSED)
			{
				if(desktop_date_state==DESKTOP_DATE_ON)
				{
					desktop_date_state = DESKTOP_DATE_OFF;
					wh0802_clear_display();
					wh0802_set_ddram_address(0x00);
					wh0802_write_data_to_ram('O');
					wh0802_write_data_to_ram('F');
					wh0802_write_data_to_ram('F');
					wh0802_set_ddram_address(0x00);
				}
				else
				{
					desktop_date_state = DESKTOP_DATE_ON;
					wh0802_clear_display();
					wh0802_set_ddram_address(0x00);
					wh0802_write_data_to_ram('O');
					wh0802_write_data_to_ram('N');
					wh0802_set_ddram_address(0x00);
				}
			}
			if(event4.value.v==BUTTON5_PRESSED)
			{
				if(desktop_date_state==DESKTOP_DATE_ON)
				{
					desktop_date_state = DESKTOP_DATE_OFF;
					wh0802_clear_display();
					wh0802_set_ddram_address(0x00);
					wh0802_write_data_to_ram('O');
					wh0802_write_data_to_ram('F');
					wh0802_write_data_to_ram('F');
					wh0802_set_ddram_address(0x00);
				}
				else
				{
					desktop_date_state = DESKTOP_DATE_ON;
					wh0802_clear_display();
					wh0802_set_ddram_address(0x00);
					wh0802_write_data_to_ram('O');
					wh0802_write_data_to_ram('N');
					wh0802_set_ddram_address(0x00);
				}
			}
		}
	}
}

// Обработчик таймера возврата рабочего стола
void DisplayTimer(void const * argument)
{
	LED8_OFF;
	Desktop = DESKTOP_ON;
	PositionState = 0;
	osThreadResume(TimeMenuHandle);
	wh0802_clear_display();
}
