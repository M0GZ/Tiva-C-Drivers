#include "GPIO.h"
void digitalPinMode(MODE Mode, PORT Port, PIN Pin, RESISTYPE ResisType)
{
		uint32_t portNum = (Port % PORTA_BASE) / (0x1000);
		if(Port == PORTE)
			portNum = 4;
		else if (Port == PORTF)
			portNum = 5;
		
		SYSCTL_RCGCGPIO_R |= (1<<portNum);
		while(  !(SYSCTL_PRGPIO_R &= (1<<portNum) ) ){}
		ADDRESS(Port,GPIO_LOCK_OFFEST) = GPIO_LOCK_KEY ;
		ADDRESS(Port,GPIO_CR_OFFSET) |= (1<<Pin);
		ADDRESS(Port,GPIO_AMSEL_OFFEST) &= ~(1<<Pin);
		ADDRESS(Port,GPIO_PCTL_OFFSET) 	&= ~(uint32_t)(0x000F << Pin);
		ADDRESS(Port,GPIO_AMSEL_OFFEST) &= ~(1<<Pin);
		ADDRESS(Port,GPIO_DEN_OFFEST) 	|= (1<<Pin);
		switch(Mode) {
			case OUTPUT :
				ADDRESS(Port,GPIO_DIR_OFFSET) 	|= (1<<Pin);
				break;
			case INPUT :
				ADDRESS(Port,GPIO_DIR_OFFSET) 	&= ~(1<<Pin);
				break;
		}
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
		ADDRESS(Port,GPIO_IM_OFFSET) 	&= ~(uint32_t)(0xFF);
		ADDRESS(Port,GPIO_IS_OFFSET) 	&= ~(uint32_t)(0xFF);
}
void digitalPinWrite(PORT Port, PIN Pin, bool Value)
{
	if(Value)
		ADDRESS(Port,GPIO_DATA_OFFSET) |= (1<<Pin);
	else
		ADDRESS(Port,GPIO_DATA_OFFSET) &= ~(1<<Pin);
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
int main ()
{
	digitalPinMode(OUTPUT,PORTF,P2,PDR);
	digitalPinWrite(PORTF,P2,1);
	return 0 ;
}
