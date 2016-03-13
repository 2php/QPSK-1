////========================================================================
///		Code by: Muneeb Abid
//		Dated: 22 Feb 2015
///		Description: Vessel Management System. (UART and LCD Operational)
////========================================================================



/*************************
50MHz system frequency

Connections:

GSM:
Dev kit PC4 - GSM Tx
Dev kit PC5 - GSM Rx
Dev kit GND - GSM GND

LCD 16x2:
Dev kit PF0 - LCD RS
Dev kit PF1 - LCD RW
Dev kit PF2 - LCD EN
Dev kit PF4 - LCD D4
Dev kit PF5 - LCD D5
Dev kit PF6 - LCD D6
Dev kit PF7 - LCD D7
**************************/

//----------
// Includes
//----------
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/tm4c123gh6pge.h"
#include "inc/SysTick.h"
#include "inc/lcd.h"
#include "inc/uart.h"
#include "inc/gps.h"
#include "inc/fsk.h"
#include "inc/dac.h"
//#include "inc/sinewave.h"
//#include <math.h>

//-------------------------
// Preprocessor directives
//-------------------------
#define USR_LED				(*((volatile uint32_t *)0x40026010))
#define SYSDIV2 4

#define replicatingFactor 20
#define jumpSize 					80

//---------------------
// Function prototypes
//---------------------

//General
void PLL_Init(void);
char* stringAppend(char* dst,char* src);
int len(char* str);
//GPS
void GPS_GetData(int i);
//FSK
void stringToSymbols(char* str);
int bitFuser(char, int);
int getNextSample(void);
int cosine(int);
void symbolLookUp(int,int[]);
void symbolsReplicate(int[]);

//------------------
// Global Variables
//------------------
char* str;
char temp[30];

char GPStime[8][12];
char GPSlat[8][12];
char GPSlong[8][12];
char GPSquality[8][3];
char GPSsat[8][5];
char GPSdop[8][5];
char GPSalt[8][10];

char msg[160]="hello\0";    ////////////////////////////////////////////

volatile double t;

uint32_t u;
char v, w[430];
uint8_t state;

signed int Symbols[1000][2];
int symbolsTable[4][2]={{-1,-1},{-1,1} ,{1,-1}, {1,1}};
volatile uint16_t dacout = 0;
int totalSymbols = 0;	
bool isSampleAvail, isSampleSent;
//static
int currentSymbol=0, curIndex=0;
	 int xi, xq, xdac, cosxi, cosxq, cosxqamp;

//---------------
// Main Function
//---------------

int main(){
	//
	//variables
	//Enable PortG GPIO PIN 0-7
	SYSCTL_RCGC2_R |= 0x00000040;
	GPIO_PORTG_AMSEL_R = 0x00;
	GPIO_PORTG_PCTL_R = 0x00000000;
	GPIO_PORTG_AFSEL_R = 0x00;
	GPIO_PORTG_DEN_R |= 0xFF;
	GPIO_PORTG_DIR_R |= 0xFF;
	
	//------------------
	//	Initializations
	//------------------	
//////	PLL_Init();
	SysTick_Init();
	fsk_init();	
	dac_init();
	USR_LED=0xFF;
		
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


///	TIMER0A Handler for FSK

void TIMER0A_Handler(void)
{
	TIMER0_ICR_R |= (1<<0);
	if (!isSampleSent)
	{
		dac_dataOut(dacout);
		isSampleSent=true;
	}
		
}

int bitFuser(char ch, int x)
{
	int num;
	switch(x)
	{
		case 0:
		{
			num = ch & 0x03;
			break;
		}	
		case 2:
		{
			num = (ch & 0x0C)>>2;
			break;
		}
		case 4:
		{
			num= (ch & 0x30)>>4;
			break;
		}
		case 6:
		{
			num=(ch & 0xC0)>>6;
			break;
		}
	}
	return num;
}

void symbolLookUp(int SYM,int SYMARRAY[])
{
	SYMARRAY[0]= symbolsTable[SYM][0];
	SYMARRAY[1]= symbolsTable[SYM][1];
}

void symbolsReplicate(int SYMARRAY[])
{
	for (int i=0; i<replicatingFactor; i++)
	{
		Symbols[totalSymbols][0]= SYMARRAY[0];
		Symbols[totalSymbols][1]= SYMARRAY[1];
		totalSymbols++;
	}
}
		
		
void stringToSymbols(char* str)
{
	int symArray[2], i=0, sym;
	for (i=0; str[i]!=0; i++)
	{
		for (int index=0; index<8; index+=2)
		{
			sym= bitFuser(str[i],index);
			symbolLookUp(sym, symArray);
			symbolsReplicate( symArray);
		}
	}
}

int getNextSample()
{
	//static 
	if (currentSymbol<=totalSymbols)
	{
		cosxi=(cosine(curIndex%SIN_SAMPLES) );
		cosxq=(cosine((curIndex+SIN_SAMPLES/4)%SIN_SAMPLES));
		cosxqamp=(curIndex+SIN_SAMPLES/4)%SIN_SAMPLES;
		xi=Symbols[currentSymbol][0] * (cosine(curIndex%SIN_SAMPLES));
		xq=Symbols[currentSymbol][1] * (cosine((curIndex+SIN_SAMPLES/4)%SIN_SAMPLES));
		xdac=( xi-xq+4096-1200)/1.414;
  		currentSymbol++;
		curIndex+=jumpSize;
 		isSampleAvail=true;
	}
	else
		isSampleAvail=false;
	return xdac;
}
int cosine(int x)
{
	int s;
	if (x>SIN_SAMPLES/2)
	{
		x=x-SIN_SAMPLES/2;
		s=-1;
	}
	else
		s=1;
	return (x<SIN_SAMPLES/4)? s*SineWave[x] : s*SineWave[SIN_SAMPLES/2 -1 - x];
	
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
