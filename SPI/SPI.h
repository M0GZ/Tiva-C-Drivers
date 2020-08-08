#ifndef _SSI_
#define _SSI_
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SYS_RCGCSSI    							((volatile uint32_t*)0x400FE61C)
#define SYSCTL_RCGCGPIO 						((volatile uint32_t*)0x400FE608)
#define RCGC2_REG_GPIO			    			((volatile uint32_t *)0x400FE108)	
#define	PORTA_BASE 						  		  0x40004000    //Data offset not equal 0x000 as data sheet  
#define GPIO_DATA_OFFSET            	0x3FC 
#define GPIO_LOCK_OFFEST							0x520
#define GPIO_CR_OFFSET								0x524
#define GPIO_AFSEL_OFFEST							0x420
#define GPIO_PCTL_OFFSET							0x52C
#define GPIO_AMSEL_OFFEST							0x528
#define GPIO_DEN_OFFEST 							0x51C
#define GPIO_DIR_OFFSET             	0x400
#define GPIO_PUR_OFFSET								0x510
#define GPIO_ODR_OFFSET               0x50C
#define GPIO_PDR_OFFSET								0x514
#define GPIO_IM_OFFSET               	0x410
#define GPIO_IS_OFFSET              	0x404
#define GPIO_RIS_OFFSET               0x414
#define UNLOCK				              	0x4C4F434B
#define SSI0_BASE_ADDRESS              0x40008000
#define System_Clock_Freq             50000000
#define Memory(X,Y)			 	(*((volatile uint32_t*)(((uint32_t)X)+((uint32_t)Y))))

typedef enum {
SSI_Module_0,
SSI_Module_1,
SSI_Module_2,
SSI_Module_3,
}SSI_Module;
typedef enum {
	
 SSICR0 = 0x000,
 SSICR1 = 0x004 ,
 SSIDR =0x008,
 SSISR =0x00C,
 SSICPSR= 0x010,
 SSIIM =0x014,
 SSIRIS= 0x018,
 SSIMIS =0x01C,
 SSIICR =0x020,
 SSIDMACTL= 0x024,
 SSICC =0xFC8,
 SSIPeriphID4 =0xFD0,
 SSIPeriphID5 =0xFD4 ,
 SSIPeriphID6 =0xFD8 ,
 SSIPeriphID7 =0xFDC ,
 SSIPeriphID0 =0xFE0,
 SSIPeriphID1 =0xFE4,
 SSIPeriphID2 =0xFE8 ,
 SSIPeriphID3 =0xFEC,
 SSIPCellID0 =0xFF0,
 SSIPCellID1 =0xFF4
}SSI_REG;
typedef enum {
	SSI_PINA2=2,
	SSI_PINA3=3,
	SSI_PINA4=4,
	SSI_PINA5=5,
	SSI_PINB4=4,
	SSI_PINB5=5,
	SSI_PINB6=6,
	SSI_PINB7=7,
	SSI_PIND0=0,
	SSI_PIND1=1,
	SSI_PIND2=2,
	SSI_PIND3=3,
	SSI_PINF0=0,
	SSI_PINF1=1,
	SSI_PINF2=2,
	SSI_PINF3=3,
}SSI_PinType;

typedef enum {
SSI_RRCF=0,
SSI_RFCR=2,
SSI_RRCR=1,
SSI_RFCF=3
}SSI_MODE;
	



 





void SSI_Master_init (SSI_Module Module,SSI_MODE mode);
void SSI_Write_Byte  (SSI_Module Module, uint8_t Data);








#endif