#ifndef _PWM_h
#define _PWM_h

/*---------------------INCLUDES----------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
//#include "tm4c123gh6pm.h"
#include "common_macros.h"
/*-----------------------TYPEDEFs---------------------*/
typedef uint16_t FREQ;
typedef enum {
	PWM0,
	PWM1
}PWM_MODULE;

typedef enum {
	GEN0,
	GEN1,
	GEN2,
	GEN3
}PWM_GEN;

typedef enum {
	DIV_1,
	DIV_2  = 0x0,
	DIV_4  = 0x1,
	DIV_8  = 0x2,
	DIV_16 = 0x3,
	DIV_32 = 0x4,
	DIV_64 = 0x7
}PWM_DIV;
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
/*-----------------------STRUCTs-----------------------*/
struct{


}PWM0_GEN0_PB6;
struct{


}PWM0_GEN2_PE5;
struct{


}PWM1_GEN0_PD0;
struct{


}PWM1_GEN2_PF1;

/*------------------------DEFINES----------------------*/
#define ADDRESS(BASE,OFFSET)				(*((volatile uint32_t*)(((uint32_t)BASE)+((uint32_t)OFFSET))))
#define	PORTA_BASE 									  0x40004000
#define	PORTB_BASE 										0x40005000
#define	PORTC_BASE 										0x40006000
#define	PORTD_BASE 										0x40007000
#define	PORTE_BASE  									0x40024000
#define	PORTF_BASE  									0x40025000
#define GPIO_DATA_OFFSET            	0x3FC       // NOTE : Data offset not equal 0x000 as data sheet         
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
#define GPIO_RIS_OFFSET               0x414
	
/*-----------------FUNCTIONS PROTOTYPES----------------*/
void PWM_Init(PWM_MODULE PWMmodule ,PWM_DIV div ,FREQ freq,PORT port,PIN pin);


#endif