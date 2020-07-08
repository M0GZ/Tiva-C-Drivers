#ifndef GPIO_H_
#define GPIO_H_

/*---------------------INCLUDES----------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
//#include "F:\Tiva-C-Drivers\GPIO\common_macros"

/*-----------------------TYPEDEFs---------------------*/
typedef enum {
	INPUT,
	OUTPUT
}MODE;

typedef enum {
	PORTA = 0x40004000,
	PORTB = 0x40005000,
	PORTC = 0x40006000,
	PORTD = 0x40007000,
	PORTE = 0x40024000,
	PORTF = 0x40025000
}PORT;

typedef enum {
	P0,P1,P2,P3,P4,P5,P6,P7
}PIN;
typedef enum {
	PUR,
	PDR
}RESISTYPE;

/*------------------------DEFINES----------------------*/
#define	PORTA_BASE 									  0x40004000
#define	PORTB_BASE 										0x40005000
#define	PORTC_BASE 										0x40006000
#define	PORTD_BASE 										0x40007000
#define	PORTE_BASE  									0x40024000
#define	PORTF_BASE  									0x40025000
#define GPIO_DATA_OFFSET            	0x000               
#define GPIO_LOCK_OFFEST							0x520
#define GPIO_CR_OFFSET								0x524
#define GPIO_AFSEL_OFFEST							0x420
#define GPIO_PCTL_OFFSET							0x52C
#define GPIO_AMSEL_OFFEST							0x528
#define GPIO_DEN_OFFEST 							0x51C
#define GPIO_DIR_OFFSET             	0x400
#define GPIO_PUR_OFFSET								0x510
#define GPIO_PDR_OFFSET								0x514
#define GPIO_IM_OFFSET               	0x410
#define GPIO_IS_OFFSET              	0x404


#define ADDRESS(BASE,OFFSET)  ( *( (volatile uint32_t*) ( ( (uint32_t)BASE ) + ( (uint32_t) OFFSET ) ) ))

/*-----------------FUNCTIONS PROTOTYPES----------------*/

void digitalPinMode(MODE Mode, PORT Port, PIN Pin, RESISTYPE ResisType);
void digitalPinWrite(PORT Port, PIN Pin, bool Value);
bool digitalPinRead(PORT Port, PIN Pin);
uint8_t digitalPortRead(PORT Port);
void digitalPortWrite(PORT Port, uint8_t Value);

#endif
