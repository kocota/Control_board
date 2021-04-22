#ifndef MENU
#define MENU

#include "string.h"
#include "stdbool.h"

#define MAX_ITEM 20     // Здесь можно задать максимальное число единиц меню.
#define NAME_LENGTH 16  // Здесь можно задать длину имени единицы меню.

#define STATE_ON  true  // Единица меню включена.
#define STATE_OFF false // Единица меню выключена.

#define DESKTOP_ON    1
#define DESKTOP_OFF   0

typedef struct
{
	bool ItemState;
	char NameItem[NAME_LENGTH];
	uint8_t Number;
	uint8_t Up;
	uint8_t Down;
	uint8_t Next;
	uint8_t Previous;
}DirectionMenu; // Структура единицы меню.



void menu_ini (void);
void menu_item_create (char *item_name, uint8_t number, uint8_t Up, uint8_t Down, uint8_t Next, uint8_t Previous);
void fill_line (char *line, char *mas);


#endif
