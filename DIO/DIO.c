#include "DIO.h"
void digitalPinMode(MODE Mode, PORT Port, PIN Pin, RESISTYPE ResisType)
{
		//Calculate the port num from the port address
		uint8_t portNum = (Port % PORTA_BASE) / (0x1000);
		if(Port == PORTE)
			portNum = 4;
		else if (Port == PORTF)
			portNum = 5;
		//Enable the clock to the port by setting the appropriate bits in the RCGCGPIO register.
		SET_BIT(SYSCTL_RCGCGPIO_R,portNum);
		//waiting until the clock connected.
		while( BIT_IS_CLEAR( SYSCTL_PRGPIO_R , portNum) ) {}
		//Unlock the port .
		ADDRESS(Port,GPIO_LOCK_OFFEST) = GPIO_LOCK_OFFEST ;
		//The GPIO commit control registers provide a layer of protection against accidental programming of 
		//critical hardware peripherals.
		SET_BIT( ADDRESS(Port,GPIO_CR_OFFSET), Pin);
		//Set the appropriate DEN bit in the GPIODEN register to enable GPIO pins as digital I/Os.
		SET_BIT ( ADDRESS(Port,GPIO_DEN_OFFEST), Pin) ;
		//Clear the GPIOAMSEL bit in the GPIOAMSEL register to disble GPIO pins to their analog function.
		CLEAR_BIT ( ADDRESS(Port,GPIO_AMSEL_OFFEST) , Pin );
		//Configure the GPIOAFSEL register to program the appropriate bit as a GPIO Pin.
		CLEAR_BIT ( ADDRESS(Port,GPIO_AFSEL_OFFEST) , Pin );
		//Choose the Function of the Pin
		if(Mode == OUTPUT)
			SET_BIT ( ADDRESS(Port,GPIO_DIR_OFFSET) , Pin) ;
		else
			CLEAR_BIT ( ADDRESS(Port,GPIO_DIR_OFFSET) , Pin) ;
		//The GPIOPCTL register is used in conjunction with the GPIOAFSEL register and selects the specific
		//peripheral signal for each GPIO pin when using the alternate function mode.
		ADDRESS(Port,GPIO_PCTL_OFFSET) =  ADDRESS(Port,GPIO_PCTL_OFFSET) & !(0x0000000F << Pin);
		//Selecting the Resistor type 
		switch(ResisType) {
			case PUR :
				ADDRESS(Port,GPIO_PUR_OFFSET) 	|= (1<<Pin);
				ADDRESS(Port,GPIO_PDR_OFFSET) 	&= ~(1<<Pin);
				break;
			case PDR :
				ADDRESS(Port,GPIO_PUR_OFFSET) 	&= ~(1<<Pin);
				ADDRESS(Port,GPIO_PDR_OFFSET) 	|= (1<<Pin);
				break;
		}
		//To prevent false interrupts :
		//Mask the corresponding port by clearing the IME field in the GPIOIM register.
		CLEAR_BIT( ADDRESS(Port,GPIO_IM_OFFSET),Pin); 
		//Configure the IS field in the GPIOIS register
		CLEAR_BIT ( ADDRESS(Port,GPIO_IS_OFFSET) , Pin) ;
		//Clear the GPIORIS register
		CLEAR_BIT ( ADDRESS(Port,GPIO_RIS_OFFSET) , Pin) ;
		//Unmask the port by setting the IME field in the GPIOIM register.
		SET_BIT ( ADDRESS(Port,GPIO_IM_OFFSET) , Pin) ;
}
void digitalPinWrite(PORT Port, PIN Pin, bool Value)
{
	if(Value)
		SET_BIT ( ADDRESS(Port,GPIO_DATA_OFFSET) , Pin ) ;
	else
		CLEAR_BIT ( ADDRESS(Port,GPIO_DATA_OFFSET) , Pin);
}
bool digitalPinRead(PORT Port, PIN Pin)
{
	return ADDRESS(Port,GPIO_DATA_OFFSET) & (1<<Pin);
}
uint8_t digitalPortRead(PORT Port)
{
	return (uint8_t)ADDRESS(Port,GPIO_DATA_OFFSET);
}
void digitalPortWrite(PORT Port, uint8_t Value)
{
	ADDRESS(Port,GPIO_DATA_OFFSET) = ( ADDRESS(Port,GPIO_DATA_OFFSET) & (0xFFFFFF00) ) | ( (uint32_t) Value ) ;
}