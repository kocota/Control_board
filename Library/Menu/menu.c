#include "stm32f1xx_hal.h"
#include "menu.h"

DirectionMenu MenuItem[MAX_ITEM]; // создаем 20 едениц в меню.
uint8_t PositionState;
uint8_t Desktop;

// Функция для заполнения строки в массив.
void fill_line (char *line, char *mas)
{
	uint8_t i;
	for(i=0; i<strlen(line); i++)
	{
		mas[i]=line[i];
	}

}


// Функция создания новой единицы в меню.
void menu_item_create (char *item_name, uint8_t number, uint8_t Up, uint8_t Down, uint8_t Next, uint8_t Previous)
{
	MenuItem[number].ItemState = STATE_ON;
	MenuItem[number].Number = number;
	MenuItem[number].Up = Up;
	MenuItem[number].Down = Down;
	MenuItem[number].Next = Next;
	MenuItem[number].Previous = Previous;
	fill_line(item_name, MenuItem[number].NameItem); // заполняем массив с именем строкой.

}

void menu_ini (void)
{
	menu_item_create("Settings",0, 0,7,1,0); // создаем единицу меню
	menu_item_create("Time and date",1, 1,2,12,0);
	menu_item_create("Desktop",2, 1,2,3,0);
	menu_item_create("Time",3, 3,4,15,2);
	menu_item_create("Date",4, 3,5,16,2);
	menu_item_create("Sensor",5, 4,5,5,2);
	menu_item_create("",6, 6,6,6,12);
	menu_item_create("Control",7, 0,7,8,7);
	menu_item_create("Relay1",8, 8,9,8,7);
	menu_item_create("Relay2",9, 8,10,9,7);
	menu_item_create("Relay3",10, 9,11,10,7);
	menu_item_create("Relay4",11, 10,11,11,7);
	menu_item_create("time setting",12, 12,13,6,1);
	menu_item_create("date setting",13, 12,13,14,1);
	menu_item_create("",14, 14,14,14,13);
	menu_item_create("",15, 15,15,15,3);
	menu_item_create("",16, 16,16,16,4);

	PositionState = 0;
	Desktop = DESKTOP_ON;
}
