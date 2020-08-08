#include "SPI.h"
SSI_PinType SCLK,SS,MISO,MOSI;
uint8_t port=0;
void SetPin(SSI_Module Module)
{
	switch(Module) 
	{
		case SSI_Module_0 :
			SCLK = SSI_PINA2;
			SS= SSI_PINA3;
		  MOSI=SSI_PINA4;
			MISO=SSI_PINA5;
		  port=0;
			break;
		case SSI_Module_1 :
			SCLK = SSI_PINF2;
			SS= SSI_PINF3;
		  MOSI=SSI_PINF0;
			MISO=SSI_PINF1;
			port=5;
			break;
		case SSI_Module_2 :
			SCLK = SSI_PINB4;
			SS= SSI_PINB5;
		  MOSI=SSI_PINB6;
			MISO=SSI_PINB7;
			port=1;
			break;
		case SSI_Module_3 :
		SCLK = SSI_PIND0;
	  SS= SSI_PIND1;
		  MOSI=SSI_PIND2;
			MISO=SSI_PIND3;
		port=3;
			break;	
	}
}
void SSI_Master_init (SSI_Module Module,SSI_MODE mode)
{
	SetPin(Module);
	
	(*SYS_RCGCSSI) |= (1<<Module);
	(*SYSCTL_RCGCGPIO)|=(1<<port);
	
	Memory(PORTA_BASE+port*0x1000,GPIO_AFSEL_OFFEST) =((1<<SCLK)|(1<<SS) |(1<<MISO) |(1<<MOSI) );
	Memory(PORTA_BASE+port*0x1000,GPIO_DEN_OFFEST) = ((1<<SCLK)|(1<<SS) |(1<<MISO) |(1<<MOSI) );
	
	Memory(PORTA_BASE+port*0x1000,GPIO_AMSEL_OFFEST) &=~(0xFF<<SCLK*4);
//  Memory(PORTA_BASE+port*0x1000,GPIO_PUR_OFFSET	)=((1<<SCL)|(1<<SDL));
//	Memory(PORTA_BASE+port*0x1000,GPIO_ODR_OFFSET)=(1<<SDL);
	
  Memory(PORTA_BASE+port*0x1000,GPIO_PCTL_OFFSET) &=~(0xFFFF<<SCLK*4);
	Memory(PORTA_BASE+port*0x1000,GPIO_PCTL_OFFSET) |= (0x2222<<SCLK*4);
	
	(*SYSCTL_RCGCGPIO)|=(1<<4);
	Memory(PORTA_BASE+4*0x1000,GPIO_DEN_OFFEST) |= (1<<0);
	Memory(PORTA_BASE+4*0x1000,GPIO_DIR_OFFSET) |= (1<<0);
	Memory(PORTA_BASE+4*0x1000,GPIO_DATA_OFFSET) |= (1<<0);
	
	Memory(SSI0_BASE_ADDRESS+Module*0x1000,SSICC) =0;
	
	Memory(SSI0_BASE_ADDRESS+Module*0x1000,SSICR1) &=~(1<<1);
	
	Memory(SSI0_BASE_ADDRESS+Module*0x1000,SSICR1) &=~(1<<2);
	Memory(SSI0_BASE_ADDRESS+Module*0x1000,SSICPSR) =10;
	Memory(SSI0_BASE_ADDRESS+Module*0x1000,SSICR0) = ( 49 << 8 ) | (0x7) | (mode<<6);
	
	Memory(SSI0_BASE_ADDRESS+Module*0x1000,SSICR1) |=(1<<1);
}
void SSI_Write_Byte  (SSI_Module Module, uint8_t Data)
{
	Memory(PORTA_BASE+4*0x1000,GPIO_DATA_OFFSET) &= ~(1<<0);
	while( (Memory(SSI0_BASE_ADDRESS+Module*0x1000,SSISR) & 0x02) == 0);
	Memory(SSI0_BASE_ADDRESS+Module*0x1000,SSIDR) = Data ;
	while( (Memory(SSI0_BASE_ADDRESS+Module*0x1000,SSISR) & 0x10) == 0);
	Memory(PORTA_BASE+4*0x1000,GPIO_DATA_OFFSET) |= (1<<0);
}