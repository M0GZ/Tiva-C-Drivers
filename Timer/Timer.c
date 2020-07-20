#include "Timer.h"
void systick_delayus(uint32_t usec)
{
	//Disable the systick
	CLEAR_BIT(ST_CTRL_R,0); 
	//Clear the Current Count Register
	ST_CURRENT_R &= 0xFF000000;
	//Put the value of ticks count in reload register
	ST_RELOAD_R =  ( ST_RELOAD_R & 0xFF000000 ) | ( ( ( CLK_FREQ_MHZ * usec   ) & 0x00FFFFFF )  - 1) ;
	//Enable systick
	SET_BIT(ST_CTRL_R,0);
	//Enable clock
	SET_BIT(ST_CTRL_R,2);
	//Waiting untill the flag is set
	while (BIT_IS_CLEAR(ST_CTRL_R,16)){}
}
/* millisecond delay using one-shot mode */
void timer0_delayms(uint32_t msec)
{
	//Enable clock to Timer Block 0 
	SET_BIT(SYSCTL_RCGCTIMER_R,0);
	//Disable Timer before initialization
  CLEAR_BIT(TIMER0_CTL_R,0);
	//32-bit option 
	TIMER0_CFG_R  = 0x00000004 ;
	//Select one-shot mode and down-counter
	TIMER0_TAMR_R = 0x00000001 ;
	//Timer A interval load value register 
	TIMER0_TAILR_R = CLK_FREQ_MHZ * msec * 1000 -1 ;
	//Set the Prescaler to 250
	//TIMER0_TAPR_R = 8;
	//Clear the TimerA timeout flag
	TIMER0_ICR_R = 0x00000001; 
	//enable Timer A after initialization
	SET_BIT(TIMER0_CTL_R,0); 
	//Wait for TimerA timeout flag to set
	while ( (TIMER0_RIS_R & 0x00000001) == 0 ){}
	//Clear the TimerA timeout flag
	TIMER0_ICR_R = 0x00000001;  
}


