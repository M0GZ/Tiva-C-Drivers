#ifndef _TIM_H
#define _TIM_H
/*---------------------INCLUDES----------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "common_macros.h"
/*--------------------DEFINES------------------------*/
#define CLK_FREQ_MHZ        200000
#define ST_CTRL_R				(*((volatile uint32_t *)0xE000E010))
#define ST_RELOAD_R			(*((volatile uint32_t *)0xE000E014))
#define ST_CURRENT_R		(*((volatile uint32_t *)0xE000E018))
	
/*-------------------FUNCTIONS PROTOTYPES----------------------*/
void systick_delayus(uint32_t usec);
void timer0_delayms(uint32_t msec);

#endif
