#include "wh0802.h"
#include "stm32f1xx_hal.h"

#include "string.h"




void write_operation (uint8_t rs_bit, uint8_t data)
{
	RW_RESET;
	if(rs_bit == INSTRUCTION_BIT) {RS_RESET;}
	else {RS_SET;}
	
	if ( (data & DB0_BIT_MASK)==DB0_BIT_MASK ) {DB0_SET;}
	else {DB0_RESET;}
	
	if ( (data & DB1_BIT_MASK)==DB1_BIT_MASK ) {DB1_SET;}
	else {DB1_RESET;}
	
	if ( (data & DB2_BIT_MASK)==DB2_BIT_MASK ) {DB2_SET;}
	else {DB2_RESET;}
	
	if ( (data & DB3_BIT_MASK)==DB3_BIT_MASK ) {DB3_SET;}
	else {DB3_RESET;}
	
	if ( (data & DB4_BIT_MASK)==DB4_BIT_MASK ) {DB4_SET;}
	else {DB4_RESET;}
	
	if ( (data & DB5_BIT_MASK)==DB5_BIT_MASK ) {DB5_SET;}
	else {DB5_RESET;}
	
	if ( (data & DB6_BIT_MASK)==DB6_BIT_MASK ) {DB6_SET;}
	else {DB6_RESET;}
	
	if ( (data & DB7_BIT_MASK)==DB7_BIT_MASK ) {DB7_SET;}
	else {DB7_RESET;}

	E_SET;
#ifdef CMSIS_OS
	if(osKernelRunning()==1) {osDelay(1);}
	else {HAL_Delay(1);}
#else
	HAL_Delay(1);
#endif
	E_RESET;
#ifdef CMSIS_OS
	if(osKernelRunning()==1) {osDelay(1);}
	else {HAL_Delay(1);}
#else
	HAL_Delay(1);
#endif
}


void wh0802_clear_display (void)
{
	write_operation( INSTRUCTION_BIT, CLEAR_DISPLAY_BIT_MASK);
}

void wh0802_return_home (void)
{
	write_operation( INSTRUCTION_BIT, RETURN_HOME_BIT_MASK);
}


void wh0802_entry_mode_set (uint8_t ID, uint8_t S)
{
	write_operation( INSTRUCTION_BIT, ENTRY_MODE_BIT_MASK|ID|S);
}


void wh0802_display_control (uint8_t D, uint8_t C, uint8_t B)
{
	write_operation( INSTRUCTION_BIT, DISPLAY_CONTROL_BIT_MASK|D|C|B);
}

void wh0802_cursor_or_display_shift (uint8_t SC, uint8_t RL)
{
	write_operation( INSTRUCTION_BIT, CURSOR_DISPLAY_SHIFT_BIT_MASK|SC|RL);
}



void wh0802_function_set (uint8_t DL, uint8_t N, uint8_t F)
{
	write_operation( INSTRUCTION_BIT, FUNCTION_SET_BIT_MASK|DL|N|F);
}

void wh0802_set_cgram_address (uint8_t cgram_address)
{
	write_operation( INSTRUCTION_BIT, SET_SGRAM_ADDRESS_BIT_MASK|cgram_address);
}

void wh0802_set_ddram_address (uint8_t ddram_address)
{
	write_operation( INSTRUCTION_BIT, SET_DDRAM_ADDRESS_BIT_MASK|ddram_address);
}

void wh0802_write_data_to_ram (uint8_t ram_data)
{
	write_operation( DATA_BIT, ram_data);
}


void wh0802_init (void)
{
#ifdef CMSIS_OS
	if(osKernelRunning()==1) {osDelay(50);}
	else {HAL_Delay(50);}
#else
	HAL_Delay(50);
#endif
	wh0802_function_set(0x10,0x08,0x04);
#ifdef CMSIS_OS
	if(osKernelRunning()==1) {osDelay(1);}
	else {HAL_Delay(1);}
#else
	HAL_Delay(1);
#endif
	wh0802_display_control(DISPLAY_ON,CURSOR_OFF,BLINKING_OFF);
#ifdef CMSIS_OS
	if(osKernelRunning()==1) {osDelay(1);}
	else {HAL_Delay(1);}
#else
	HAL_Delay(1);
#endif
	wh0802_clear_display();
#ifdef CMSIS_OS
	if(osKernelRunning()==1) {osDelay(1);}
	else {HAL_Delay(1);}
#else
	HAL_Delay(1);
#endif
	wh0802_entry_mode_set(0x02,0x01);
}


void wh0802_write_to_display (uint8_t ddram_address, char *data, uint8_t clear_state)
{
	if(clear_state == CLEAR_ON)
	{
		wh0802_clear_display();
	}
	uint8_t i;
	uint8_t j=0;
	if(ddram_address<=0x07)
	{
		for(i=0; i<strlen(data); i++)
		{
			if((ddram_address+i)<=0x07)
			{
				j++;
				wh0802_set_ddram_address(ddram_address+i);
				wh0802_write_data_to_ram(*(data+i));
			}
			else
			{
				ddram_address=0x40;
				wh0802_set_ddram_address(ddram_address+i-j);
				wh0802_write_data_to_ram(*(data+i));
			}
		}
	}
	else
	{
		for(i=0; i<strlen(data); i++)
		{
			wh0802_set_ddram_address(ddram_address+i);
			wh0802_write_data_to_ram(*(data+i));
		}
	}
}



