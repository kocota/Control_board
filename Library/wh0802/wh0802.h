#ifndef WH0802
#define WH0802

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

// Закоментируйте строку, если не используете CMSIS OS-------
#define CMSIS_OS
//---------------------------------------------------------


//----------------------------------------
//to change pins and ports

#define LED_MCU_Pin          GPIO_PIN_7
#define LED_MCU_GPIO_Port    GPIOA
#define RS_Pin               GPIO_PIN_1
#define RS_GPIO_Port         GPIOB
#define RW_Pin               GPIO_PIN_2
#define RW_GPIO_Port         GPIOB
#define E_Pin                GPIO_PIN_10
#define E_GPIO_Port          GPIOB
#define DB0_Pin              GPIO_PIN_11
#define DB0_GPIO_Port        GPIOB
#define DB1_Pin              GPIO_PIN_12
#define DB1_GPIO_Port        GPIOB
#define DB2_Pin              GPIO_PIN_13
#define DB2_GPIO_Port        GPIOB
#define DB3_Pin              GPIO_PIN_14
#define DB3_GPIO_Port        GPIOB
#define DB4_Pin              GPIO_PIN_15
#define DB4_GPIO_Port        GPIOB
#define DB5_Pin              GPIO_PIN_8
#define DB5_GPIO_Port        GPIOA
#define DB6_Pin              GPIO_PIN_9
#define DB6_GPIO_Port        GPIOA
#define DB7_Pin              GPIO_PIN_10
#define DB7_GPIO_Port        GPIOA
//----------------------------------------






#define RS_SET     HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
#define RS_RESET   HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
#define RW_SET     HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_SET);
#define RW_RESET   HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
#define E_SET      HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
#define E_RESET    HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
#define DB0_SET    HAL_GPIO_WritePin(DB0_GPIO_Port, DB0_Pin, GPIO_PIN_SET);
#define DB0_RESET  HAL_GPIO_WritePin(DB0_GPIO_Port, DB0_Pin, GPIO_PIN_RESET);
#define DB1_SET    HAL_GPIO_WritePin(DB1_GPIO_Port, DB1_Pin, GPIO_PIN_SET);
#define DB1_RESET  HAL_GPIO_WritePin(DB1_GPIO_Port, DB1_Pin, GPIO_PIN_RESET);
#define DB2_SET    HAL_GPIO_WritePin(DB2_GPIO_Port, DB2_Pin, GPIO_PIN_SET);
#define DB2_RESET  HAL_GPIO_WritePin(DB2_GPIO_Port, DB2_Pin, GPIO_PIN_RESET);
#define DB3_SET    HAL_GPIO_WritePin(DB3_GPIO_Port, DB3_Pin, GPIO_PIN_SET);
#define DB3_RESET  HAL_GPIO_WritePin(DB3_GPIO_Port, DB3_Pin, GPIO_PIN_RESET);
#define DB4_SET    HAL_GPIO_WritePin(DB4_GPIO_Port, DB4_Pin, GPIO_PIN_SET);
#define DB4_RESET  HAL_GPIO_WritePin(DB4_GPIO_Port, DB4_Pin, GPIO_PIN_RESET);
#define DB5_SET    HAL_GPIO_WritePin(DB5_GPIO_Port, DB5_Pin, GPIO_PIN_SET);
#define DB5_RESET  HAL_GPIO_WritePin(DB5_GPIO_Port, DB5_Pin, GPIO_PIN_RESET);
#define DB6_SET    HAL_GPIO_WritePin(DB6_GPIO_Port, DB6_Pin, GPIO_PIN_SET);
#define DB6_RESET  HAL_GPIO_WritePin(DB6_GPIO_Port, DB6_Pin, GPIO_PIN_RESET);
#define DB7_SET    HAL_GPIO_WritePin(DB7_GPIO_Port, DB7_Pin, GPIO_PIN_SET);
#define DB7_RESET  HAL_GPIO_WritePin(DB7_GPIO_Port, DB7_Pin, GPIO_PIN_RESET);

// RS bits
#define INSTRUCTION_BIT 0x00
#define DATA_BIT        0x01
//--------


#define DB0_BIT_MASK 0x01
#define DB1_BIT_MASK 0x02
#define DB2_BIT_MASK 0x04
#define DB3_BIT_MASK 0x08
#define DB4_BIT_MASK 0x10
#define DB5_BIT_MASK 0x20
#define DB6_BIT_MASK 0x40
#define DB7_BIT_MASK 0x80
#define CLEAR_DISPLAY_BIT_MASK            0x01
#define RETURN_HOME_BIT_MASK              0x02
#define ENTRY_MODE_BIT_MASK               0x40
#define DISPLAY_CONTROL_BIT_MASK          0x08
#define CURSOR_DISPLAY_SHIFT_BIT_MASK     0x10
#define FUNCTION_SET_BIT_MASK             0x20
#define SET_SGRAM_ADDRESS_BIT_MASK        0x40
#define SET_DDRAM_ADDRESS_BIT_MASK        0x80

#define CLEAR_ON   0x01
#define CLEAR_OFF  0x00




#define SHIFT_DISPLAY_OFF       0x00
#define SHIFT_DISPLAY_ON        0x01
#define SHIFT_DISPLAY_RIGHT     0x00
#define SHIFT_DISPLAY_LEFT      0x01

#define DISPLAY_OFF             0x00
#define DISPLAY_ON              0x04
#define CURSOR_OFF              0x00
#define CURSOR_ON               0x02
#define BLINKING_OFF            0x00
#define BLINKING_ON             0x01

#define SHIFT_CURSOR						0x00
#define SHIFT_SCREEN						0x01
#define SHIFT_LEFT							0x00
#define SHIFT_RIGHT							0x01





#define DATA_LENGTH_4BIT   0x00
#define DATA_LENGTH_8BIT   0x01
#define ONE_LINE  				 0x00
#define TWO_LINE           0x01
#define FONT_5X8           0x00
#define FONT_5X10          0x01









void write_operation (uint8_t rs_bit, uint8_t data);
void wh0802_clear_display (void);
void wh0802_return_home (void);
void wh0802_entry_mode_set (uint8_t ID, uint8_t S);
void wh0802_display_control (uint8_t D, uint8_t C, uint8_t B);
void wh0802_function_set (uint8_t DL, uint8_t N, uint8_t F);
void wh0802_init (void);
void wh0802_set_ddram_address (uint8_t ddram_address);
void wh0802_write_data_to_ram (uint8_t data);
void wh0802_cursor_or_display_shift (uint8_t SC, uint8_t RL);
void wh0802_write_to_display (uint8_t ddram_address, char *data, uint8_t clear_state);


#endif
