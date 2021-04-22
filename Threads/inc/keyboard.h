#ifndef KEYBOARD
#define KEYBOARD

#include "cmsis_os.h"

void Keyboard(void const * argument); // Прототип потока
void test (void);

#define LED8_ON         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET)
#define LED8_OFF        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET)
#define BUTTON1_READ    HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)
#define BUTTON2_READ    HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)
#define BUTTON3_READ    HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)
#define BUTTON4_READ    HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15)
#define BUTTON5_READ    HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)
#define BUTTON6_READ    HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)

#define BUTTON1_PRESSED 1
#define BUTTON2_PRESSED 2
#define BUTTON3_PRESSED 3
#define BUTTON4_PRESSED 4
#define BUTTON5_PRESSED 5
#define BUTTON6_PRESSED 6

#endif
