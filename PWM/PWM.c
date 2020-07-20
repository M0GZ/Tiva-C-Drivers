#include "PWM.h"
#include "TM4C123GH6PM.h"
/*
void PWM_Init(PWM_MODULE PWMmodule ,PWM_DIV div ,FREQ freq,PORT port,PIN pin)
{
uint8_t module_num = 0;
	if(PWMmodule == 1)
		module_num = 1 ;
	uint8_t portNum = (port % PORTA_BASE) / (0x1000);
	if(port == PORTE)
		portNum = 4;
	else if (port == PORTF)
		portNum = 5;
	//Enable Peripheral Clocks
	//Enable clock to PWMx
	SET_BIT(SYSCTL_RCGCPWM_R,module_num);
	//Pre-divide for PWM clock
	if(div == DIV_1)
		CLEAR_BIT(SYSCTL_RCC_R,20);
	else
	{
		SET_BIT(SYSCTL_RCC_R,20);
		SYSCTL_RCC_R = ( SYSCTL_RCC_R & 0xFFF8FFFF) | ( div << 17 ) ;
	}
	//Enable the clock to the port by setting the appropriate bits in the RCGCGPIO register.
	SET_BIT(SYSCTL_RCGCGPIO_R,portNum);
	//waiting until the clock connected.
	while( BIT_IS_CLEAR( SYSCTL_PRGPIO_R , portNum) ) {}
	//Configure the GPIOAFSEL register to program the appropriate bit as a PWM output Pin.
	SET_BIT( ADDRESS(port,GPIO_AFSEL_OFFEST) , pin );
	//The GPIOPCTL register is used in conjunction with the GPIOAFSEL register and selects the specific
	//peripheral signal for each GPIO pin when using the alternate function mode.
	ADDRESS(port,GPIO_PCTL_OFFSET) =  ( ADDRESS(port,GPIO_PCTL_OFFSET) & ~0x0000F000  ) |( 0x00000005  << pin);
	//Set the appropriate DEN bit in the GPIODEN register to enable GPIO pins as digital I/Os.
	SET_BIT ( ADDRESS(port,GPIO_DEN_OFFEST), pin) ;
	PWM1_3_CTL_R = 0 ;
	PWM1_3_GENB_R = 0x0000008C;
	PWM1_3_LOAD_R = 16000;
	PWM1_3_CMPA_R = 8000;
	PWM1_3_CTL_R = 0 ;
	PWM1_ENABLE_R = 0x80;
	while(1);

}*/
/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n)
{
	int i, j;
	for(i = 0 ; i < n; i++)
	for(j = 0; j < 31800; j++)
	{} /* do nothing for 1 ms */
}

int main(void)
{
	int x = 0xFFFE;
	/* Enable Peripheral Clocks */
	SYSCTL->RCGCPWM |= 2; /* enable clock to PWM1 */
	SYSCTL->RCGCGPIO |= 0x20; /* enable clock to PORTF */
	SYSCTL->RCC |= 0x00100000; /* use pre-divide for PWM clock */
	SYSCTL->RCC |= 0x000E0000; /* set 64 for pre-divide for PWM */
	/* Enable port PF3 for PWM1 M1PWM7 */
	GPIOF->AFSEL = 8; /* PF3 uses alternate function */
	GPIOF->PCTL &= ~0x0000F000; /* make PF3 PWM output pin */
	GPIOF->PCTL |= 0x00005000;
	GPIOF->DEN |= 8; /* pin digital */
	PWM1->_3_CTL = 0; /* stop counter */
	PWM1->_3_GENB = 0x0000008C; /* M1PWM7 output set when reload, */
	/* clear when match PWMCMPA */
	PWM1->_3_LOAD = 0xFFFF; /* set load value with max value */
	PWM1->_3_CMPA = x; /* set duty cycle to 50% */
	PWM1->_3_CTL = 1; /* start timer */
	PWM1->ENABLE = 0x80; /* start PWM1 ch7 */
	for(;;)
{
x = x - 1000;
if (x <= 0) x = 0xFFFE;
PWM1->_3_CMPA = x;
delayMs(300);
}
}

//int main ()
//{
//	SYSCTL_RCGCPWM_R |= 2; /* enable clock to PWM1 */
//	SYSCTL_RCGCGPIO_R |= 0x20; /* enable clock to PORTF */
//	SYSCTL_RCC_R &= ~0x00100000; /* no pre-divide for PWM clock */
//	/* Enable port PF3 for PWM1 M1PWM7 */
//	ADDRESS(PORTF,GPIO_AFSEL_OFFEST) = 8; /* PF3 uses alternate function */
//	ADDRESS(PORTF,GPIO_PCTL_OFFSET) &= ~0x0000F000; /* make PF3 PWM output pin */
//	ADDRESS(PORTF,GPIO_PCTL_OFFSET) |= 0x00005000;
//	ADDRESS(PORTF,GPIO_DEN_OFFEST) |= 8; /* pin digital */
//	PWM1_3_CTL_R  = 0; /* stop counter */
//	PWM1_3_GENB_R = 0x0000008C; /* M1PWM7 output set when reload, */
//	/* clear when match PWMCMPA */
//	PWM1_3_LOAD_R = 16000; /* set load value for 1kHz (16MHz/16000) */
//	PWM1_3_CMPA_R = 16000; /* set duty cycle to 50% */
//	PWM1_3_CTL_R = 1; /* start timer */
//	PWM1_ENABLE_R = 0x80; /* start PWM1 ch7 */
//	for(;;) { }

