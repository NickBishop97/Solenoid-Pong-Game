#include "Port_Init.h"
#include "Common.h"
#include "tm4c123gh6pm.h"

/*
Port A Initialization
PA2 Output- Clock pin shared between all solenoid shift registers
PA3 Output- Clock pin for Player 2 Shift Reg
PA4 Output- Latch pin for Player 2 Shift Reg
PA5 Input - Data pin for Player 2 Shift Reg
*/
void GPIOPortA_Init(void){volatile unsigned long delay; 
	SYSCTL_RCGC2_R |= 0x01;
	delay = SYSCTL_RCGC2_R;       // delay
	GPIO_PORTA_AMSEL_R &= ~0x04;  // disable analog function
	GPIO_PORTA_DIR_R |= 0x1C; 		// make PA2,3,4 output
	GPIO_PORTA_DIR_R &= ~0x20; 		// make PA5, input
	GPIO_PORTA_AFSEL_R &= ~0x04;	// disable alt funct 
	GPIO_PORTA_DEN_R |= 0x3C; 		// enable digital I/O
}
/*
Port B Initialization
PB0 Output - Latch pin for Shift Reg 1-2 for solenoids
PB1 Output - Latch pin for Shift Reg 3-4 for solenoids
PB2 Output - Latch pin for Shift Reg 5-6 for solenoids
PB3 Output - Latch pin for Shift Reg 7-8 for solenoids
PB4 Output - Data pin for Shift Reg 1-2 for solenoids
PB5 Output - Data pin for Shift Reg 3-4 for solenoids
PB6 Output - Data pin for Shift Reg 5-6 for solenoids
PB7 Output - Data pin for Shift Reg 7-8 for solenoids
*/
void GPIOPortB_Init(void){volatile unsigned long delay; 
	SYSCTL_RCGC2_R |= 0x02;
	delay = SYSCTL_RCGC2_R;       // delay
	GPIO_PORTB_AMSEL_R &= ~0xFF;  // disable analog function
	GPIO_PORTB_DIR_R |= 0xFF; 		// make PB0-7 outputs
	GPIO_PORTB_AFSEL_R &= ~0xFF;  // disable alt funct 
	GPIO_PORTB_DEN_R |= 0xFF; 		// enable digital I/O
}

/*
Port D Initialization
PD2 Output - Clock pin for Player 1 Shift Reg
PD3 Output - Latch pin for Player 1 Shift Reg
PD6 Input - Data pin for Player 1 Shift Reg
*/

void PortD_InIt(void) {
	SYSCTL_RCGC2_R |= 0x00000008; 	  // activate clock for port D
	GPIO_PORTD_LOCK_R =  0x4C4F434B;
	GPIO_PORTD_CR_R |= 0xCC;          // allow changes to PD2,3,6,7
	GPIO_PORTD_DIR_R |= 0x8C;    		  // make PD2,3,7 outputs
	GPIO_PORTD_DIR_R &= ~0x40;    	  // make PD6 inputs
	GPIO_PORTD_AFSEL_R &= ~0xCC;  	  // disable alt funct on PD2,3,6,7
	GPIO_PORTD_DEN_R |= 0xCC;     	  // enable digital I/O on PD2,3,6,7
	GPIO_PORTD_PCTL_R &= ~0xFF00FF00; // configure PD2,3,6,7 as GPIO
	GPIO_PORTD_AMSEL_R &= ~0xCC; 		  // disable analog functionality on PD2,3,6,7
}
void PortE_Init(void) {
	//SYSCTL_RCGC2_R |= 0x00000010; 	  // activate clock for port D 1,3,4,5
	GPIO_PORTE_AMSEL_R &= ~0x39; 		  // disable analog functionality on PD2,3,6
	GPIO_PORTE_DIR_R |= 0x39;    		  // make PD2,3 outputs
	GPIO_PORTE_AFSEL_R &= ~0x39;  	  // disable alt funct on PD2,3,6
	GPIO_PORTE_DEN_R |= 0x39;     	  // enable digital I/O on PD2,3,6
}
/*
Initialization of SysTick for use as a timer
Input:
	period reload value for Systick, will determine how often
				 SysTick_Handler will be called
*/
void Sound_Init(unsigned long period){
  NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2      
  NVIC_ST_CTRL_R = 0x0007;  // enable SysTick with core clock and interrupts
}
