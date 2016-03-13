#include <stdint.h>
#include "inc/tm4c123gh6pge.h"
#include "inc/SysTick.h"

#define USR_LED				(*((volatile uint32_t *)0x40026010))

uint32_t d;
void dac_init(){
SYSCTL_RCGC2_R |= 0x00000100;			//PORTJ Clock
	delay_ms(5);      
  GPIO_PORTJ_LOCK_R = 0X4C4F434B;
	GPIO_PORTJ_CR_R = 0xFF;
	GPIO_PORTJ_AMSEL_R = 0x00;
	GPIO_PORTJ_PCTL_R = 0x00000000;
	GPIO_PORTJ_AFSEL_R = 0x00;
	GPIO_PORTJ_DEN_R = 0xFF;
	GPIO_PORTJ_DIR_R = 0xFF;
	
	SYSCTL_RCGCGPIO_R |= 0x00001000;			//PORTN Clock
	delay_ms(5);      
  GPIO_PORTN_LOCK_R = 0X4C4F434B;
	GPIO_PORTN_CR_R = 0xFF;
	GPIO_PORTN_AMSEL_R = 0x00;
	GPIO_PORTN_PCTL_R = 0x00000000;
	GPIO_PORTN_AFSEL_R = 0x00;
	GPIO_PORTN_DEN_R = 0xFF;
	GPIO_PORTN_DIR_R = 0xFF;
	
	GPIO_PORTJ_DATA_R |= 0x80; 		// PD = PJ7 always high
}

void dac_dataOut(short int data){
		// PD = PJ7 always high
		// LDAC = PJ6
		// WE = PJ5
		// CS = PJ4
		// D0-3 = PJ0-3
		// D4-11 = PN0-7
		
	// data .. CS = 0 .. WE = 0 .. wait 13ns .. WE = 1 .. LDAC = 0 .. wait 25ns .. CS = 1 .. LDAC = 1
	
			GPIO_PORTJ_DATA_R |= 0x20; 			// WE= 1
	GPIO_PORTJ_DATA_R &= ~0x40; 		// LDAC = 0
	
	GPIO_PORTJ_DATA_R |= 0x50; 			// CS = 1, LDAC = 1
		for (int c=0; c<55; c++){}
	
	
	GPIO_PORTJ_DATA_R &= ~0x30; 		// CS = 0, WE= 0
	for (int c=0; c<5; c++){}
	GPIO_PORTJ_DATA_R = GPIO_PORTJ_DATA_R & (0xF0 | (data & 0x0F));		//set D0-3
	GPIO_PORTN_DATA_R = data >> 4;																		//set D4-11
	d=(GPIO_PORTN_DATA_R<<4)| (GPIO_PORTJ_DATA_R &0x0F);
	
 	for (int c=0; c<55; c++){}
}
