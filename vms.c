
/*************************
16MHz system frequency
*************************/

//----------
// Includes
//----------
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/tm4c123gh6pge.h"
#include "inc/SysTick.h"
#include "inc/psk.h"
#include "inc/dac.h"

//-------------------------
// Preprocessor directives
//-------------------------
#define USR_LED				(*((volatile uint32_t *)0x40026010))
#define SYSDIV2 4


//---------------------
// Function prototypes
//---------------------
void portG_init(void);
void PLL_Init(void);
char* stringAppend(char* dst,char* src);

//------------------
// Global Variables
//------------------
char msg[160]="hello world\0";    ////////////////////////////////////////////
volatile uint16_t dacout = 0;


//---------------
// Main Function
//---------------

int main(){
//	msg[0]=0xFF;msg[1]=0xFF;msg[2]=0xFF;msg[3]=0xFF;msg[4]=0xFF;

	//------------------
	//	Initializations
	//------------------	
//PLL_Init();
	portG_init();
	USR_LED=0xFF;
	SysTick_Init();
	psk_init();	
	dac_init();
	
	while(1)
	{
		stringToSymbols(msg);
		dacout=getNextSample();
		TIMER0_ENABLE;
		while(isSampleAvail)
		{
			isSampleSent=false;
			while(!isSampleSent)
			{}
			dacout=getNextSample();
		}
		TIMER0_DISABLE;
		
	}
}//end main



void portG_init()
{	//Enable PortG GPIO PIN 0-7
	SYSCTL_RCGC2_R |= 0x00000040;
	GPIO_PORTG_AMSEL_R = 0x00;
	GPIO_PORTG_PCTL_R = 0x00000000;
	GPIO_PORTG_AFSEL_R = 0x00;
	GPIO_PORTG_DEN_R |= 0xFF;
	GPIO_PORTG_DIR_R |= 0xFF;
}

void PLL_Init(void){
  
  SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
 
  SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;

  SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;  
  SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;
  SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;
 
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
  
  SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400; 
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) + (SYSDIV2<<22);        
  while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}


//----------------------
// Function definitions
//----------------------


///	TIMER0A Handler for PSK
void TIMER0A_Handler(void)
{
	TIMER0_ICR_R |= (1<<0);
	if (!isSampleSent)
	{
		dac_dataOut(dacout);
		isSampleSent=true;
	}
		
}


char* stringAppend(char* dst,char* src){
	int n,i;
	for(n=0;dst[n]!='\0';n++){
	}
	
	for(i=0;(src[i]!='\0');i++){
		dst[n]=src[i];
		n++;
	}	
	dst[n]='\0';	
	
	return dst;
}
