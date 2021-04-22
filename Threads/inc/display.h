#ifndef DISPLAY
#define DISPLAY

#define DISPLAY_TIMER 5000 //Время возврата на рабочий стол
#define DESKTOP_TIME_ON  1
#define DESKTOP_TIME_OFF 0
#define DESKTOP_DATE_ON  1
#define DESKTOP_DATE_OFF 0

#include "cmsis_os.h"

void Display(void const * argument); // Прототип потока дисплея
void TimeMenu(void const * argument); // Прототип потока дисплея
void DisplayTimer(void const * argument); //Прототип обработчика таймера дисплея
void TimeTask(void const * argument); // Прототип обработчика задачи установки времени
void DateTask(void const * argument); // Прототип обработчика задачи установки даты
void TimeDisplayTask(void const * argument); // Прототип обработчика задачи установки отображения времени на дисплее
void DateDisplayTask(void const * argument); // Прототип обработчика задачи установки отображения даты на дисплее

#endif
