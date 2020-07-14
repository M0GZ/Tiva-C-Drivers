#include "Timer.h"
void systickDlay(uint32_t usec)
{
	//Disable the systick
	CLEAR_BIT(ST_CTRL_R,0); 
	//Clear the Current Count Register
	ST_CURRENT_R &= 0xFF000000;
	//Put the value of ticks count in reload register
	ST_RELOAD_R =  ( ST_RELOAD_R & 0xFF000000 ) | ( ( ( CLK_FREQ * usec   ) & 0x00FFFFFF )  - 1) ;
	//Enable systick
	SET_BIT(ST_CTRL_R,0);
	//Enable clock
	SET_BIT(ST_CTRL_R,2);
	//Waiting untill the flag is set
	while (BIT_IS_CLEAR(ST_CTRL_R,16)){}
	
}
