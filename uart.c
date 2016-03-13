////=============================================================
///		Code by: Muneeb Abid
//		Dated: 22 Feb 2015
///		Description: UART Basic Functions
////=============================================================


#include <stdint.h>
#include "inc\tm4c123gh6pge.h"


//UART Initialization
void Init_UART(){
	SYSCTL_RCGC1_R |= 0x00000007;  // activate UART1 UART2
  SYSCTL_RCGC2_R |= 0x0000000C;  // activate port C & D
	GPIO_PORTC_AMSEL_R = 0x00;
	GPIO_PORTD_AMSEL_R = 0x00;
	
	GPIO_PORTD_LOCK_R = 0X4C4F434B;
	GPIO_PORTD_CR_R = 0xFF;
	
	SYSCTL_RCGCUART_R|= 0X00000007;
	
	//115200 bps
	UART1_CTL_R &= ~0x00000001;    // disable UART
	UART1_CTL_R &= ~0x00000010;     // clear HSE
  UART1_IBRD_R = 21;     // IBRD = 27
  UART1_FBRD_R = 45;     // FBRD = 26
  UART1_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs
  UART1_CTL_R |= 0x00000001;     // enable UART
	
	//4800 bps
	UART2_CTL_R &= ~0x00000001;    // disable UART
	UART2_CTL_R &= ~0x00000010;     // clear HSE
  UART2_IBRD_R = 520;     // IBRD = 651
  UART2_FBRD_R = 53;     // FBRD = 3
  UART2_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs
  UART2_CTL_R |= 0x00000001;     // enable UART

  GPIO_PORTC_AFSEL_R |= 0x30;    // enable alt funct on PC5-4
  GPIO_PORTD_AFSEL_R |= 0xC0;    // enable alt funct on PD7-6
	
	
	GPIO_PORTC_DEN_R |= 0x30;      // configure PC5-4 as UART1
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;
	
	GPIO_PORTD_DEN_R |= 0xC0;      // configure PD7-6 as UART2
	GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0x00FFFFFF)+0x11000000;
	
	GPIO_PORTC_AMSEL_R &= ~0x30;   // disable analog on PC5-4
	GPIO_PORTD_AMSEL_R &= ~0xC0;   // disable analog on PD7-6
  
}


// Wait for new input, then return ASCII code
unsigned char UARTn_RxCh(int n){
	volatile uint32_t* uart_fr;
	volatile uint32_t* uart_dr;
	
	switch(n){
case 0:
uart_fr = &UART0_FR_R;
uart_dr = &UART0_DR_R;
break;

case 1:
uart_fr = &UART1_FR_R;
uart_dr = &UART1_DR_R;
break;

case 2:
uart_fr = &UART2_FR_R;
uart_dr = &UART2_DR_R;
break;

case 3:
uart_fr = &UART3_FR_R;
uart_dr = &UART3_DR_R;
break;

case 4:
uart_fr = &UART4_FR_R;
uart_dr = &UART4_DR_R;
break;

case 5:
uart_fr = &UART5_FR_R;
uart_dr = &UART5_DR_R;
break;

case 6:
uart_fr = &UART6_FR_R;
uart_dr = &UART6_DR_R;
break;

case 7:
uart_fr = &UART7_FR_R;
uart_dr = &UART7_DR_R;
break;
}
	
  while(((*uart_fr)&0x0010) != 0);      // wait until RXFE is 0
  return((unsigned char)((*uart_dr)&0xFF));
}


// Wait for buffer to be not full, then output
void UARTn_TxCh(int n,unsigned char data){
	volatile uint32_t* uart_fr;
	volatile uint32_t* uart_dr;
	
	switch(n){
case 0:
uart_fr = &UART0_FR_R;
uart_dr = &UART0_DR_R;
break;

case 1:
uart_fr = &UART1_FR_R;
uart_dr = &UART1_DR_R;
break;

case 2:
uart_fr = &UART2_FR_R;
uart_dr = &UART2_DR_R;
break;

case 3:
uart_fr = &UART3_FR_R;
uart_dr = &UART3_DR_R;
break;

case 4:
uart_fr = &UART4_FR_R;
uart_dr = &UART4_DR_R;
break;

case 5:
uart_fr = &UART5_FR_R;
uart_dr = &UART5_DR_R;
break;

case 6:
uart_fr = &UART6_FR_R;
uart_dr = &UART6_DR_R;
break;

case 7:
uart_fr = &UART7_FR_R;
uart_dr = &UART7_DR_R;
break;
}

  while(((*uart_fr)&0x0020) != 0);      // wait until TXFF is 0
  *uart_dr = data;
}



// Output string to UART
void UARTn_TxStr(int n,char* string){
	int i = 0;
	for(i=0;string[i]!='\0';i++){  
		UARTn_TxCh(n,string[i]);
	}
}


// Immediately return input or 0 if no input
unsigned char UARTn_RxChNonBlocking(int n){
  	
	volatile uint32_t* uart_fr;
	volatile uint32_t* uart_dr;
	
	switch(n){
case 0:
uart_fr = &UART0_FR_R;
uart_dr = &UART0_DR_R;
break;

case 1:
uart_fr = &UART1_FR_R;
uart_dr = &UART1_DR_R;
break;

case 2:
uart_fr = &UART2_FR_R;
uart_dr = &UART2_DR_R;
break;

case 3:
uart_fr = &UART3_FR_R;
uart_dr = &UART3_DR_R;
break;

case 4:
uart_fr = &UART4_FR_R;
uart_dr = &UART4_DR_R;
break;

case 5:
uart_fr = &UART5_FR_R;
uart_dr = &UART5_DR_R;
break;

case 6:
uart_fr = &UART6_FR_R;
uart_dr = &UART6_DR_R;
break;

case 7:
uart_fr = &UART7_FR_R;
uart_dr = &UART7_DR_R;
break;
}
	
	if(((*uart_fr)&UART_FR_RXFE) == 0){
    return((unsigned char)((*uart_dr)&0xFF));
  } else{
    return 0;
  }
}
