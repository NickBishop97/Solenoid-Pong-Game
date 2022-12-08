#include "ShiftRegInit.h"
#include "Common.h"

/*
Function for sending data to shift registers and in turn powering solenoids
How it works:
	Latch for all shift registers are set LOW so that no data is sent into the solenoids yet
	With there being 4 sets of two 8 bit shift registers daisy chained together, we need to feed data
	into each set 16 times, hence the for loop that iterates 16 times
	In the for loop, we start with clock being low, then we feed data into each SER or data pin 
	of the first shift register in the daisy chained sets
	CLOCK_HIGH will then shift the current value in Data into Bit 0 of the shift register, 
	as well as shift the previous bits in any of the pins to the left by 1
	So if the shift register were currently holding 0000 0000 0011 1101 and we send a 0 to the Data pin,
	it will now hold 0000 0000 0111 1010
	Latch High will then store the values from shift register into the Latch register which then 
	sends values to the solenoids determining which will turn on
*/
void write_reg(void){
		Latch1 = LATCH_LOW; //turns off latch
		Latch2 = LATCH_LOW;
		Latch3 = LATCH_LOW;
		Latch4 = LATCH_LOW;
		for(int j=0; j<16;j++) //
		{
			Clock = CLOCK_LOW;  //clock low
			Data1 = regs1[j]<<4;//feeds data into 1st set of shift registers
			Data2 = regs2[j]<<5;//feeds data into 2nd set of shift registers
			Data3 = regs3[j]<<6;//feeds data into 3rd set of shift registers
			Data4 = regs4[j]<<7;//feeds data into 4th set of shift registers
			Clock = CLOCK_HIGH; //clock high, shifts bits into shift registers
		}
		Latch1 = LATCH1_HIGH; //sets latch which copies data to storage register
		Latch2 = LATCH2_HIGH;
		Latch3 = LATCH3_HIGH;
		Latch4 = LATCH4_HIGH;
}

void ShiftReg_SSD(void){
		SSDP1_Latch = P1_SSD_LATCH_LOW; //turns off latch
		SSDP2_Latch = P2_SSD_LATCH_LOW;
		for(int j=0; j<16;j++) //
		{
			SSD_Clock = SSD_CLOCK_LOW; //clock low
			SSDP1_Data = SSDReg[j]<<7;//feeds data into shift register
			SSDP2_Data = SSDReg[j]<<3;
			SSD_Clock = SSD_CLOCK_HIGH; //clock high, shifts bits into shift register
		}
		SSDP1_Latch = P1_SSD_LATCH_HIGH; //sets latch which copies data to storage register
		SSDP2_Latch = P2_SSD_LATCH_HIGH;
}

/*
Function for receiving data from player 1 controller and returning it as an 
8 bit value which can then be used for determining which buttons were pressed and what 
action to perform from this information
How it works:
	When Latch is low, data from shift register cannot be shifted in, so we set it to low then high
	with a small delay in between. We then enter a for loop where set the current value from the data pin
	of the shift reg to controller_value, and shift it to the left by 1 bit. This will make it so eventually
	the entire 8 bits being received a bit at a time will be an 8 bit value which we will return to be used for
	determining which button was pressed on the controller. 
*/
int p1_button_write_reg(void){
	unsigned int p1_controller_value = 0;
	P1_Button_Load = P1BUTTON_LATCH_LOW;//allows data to be read
	Delay2();
	P1_Button_Load = P1BUTTON_LATCH_HIGH;
	Delay2();
	
	for (int i = 0; i < 8; i++) {
		P1_Button_Clock = P1BUTTON_CLOCK_LOW;
    p1_controller_value |= P1_Button_Data<<i;
		P1_Button_Clock = P1BUTTON_CLOCK_HIGH; // Shift out the next bit
  }
	p1_controller_value >>= 6 ;

	return p1_controller_value;
}

/*
Function for receiving data from player 2 controller and returning it as an 
8 bit value which can then be used for determining which buttons were pressed and what 
action to perform from this information
How it works:
	When Latch is low, data from shift register cannot be shifted in, so we set it to low then high
	with a small delay in between. We then enter a for loop where set the current value from the data pin
	of the shift reg to controller_value, and shift it to the left by 1 bit. This will make it so eventually
	the entire 8 bits being received a bit at a time will be an 8 bit value which we will return to be used for
	determining which button was pressed on the controller. 
*/
int p2_button_write_reg(void){
	int p2_controller_value = 0;
	P2_Button_Load = P2BUTTON_LATCH_LOW;
	Delay2();
	P2_Button_Load = P2BUTTON_LATCH_HIGH;
	Delay2();

	for (int i = 0; i < 8; i++) {
    p2_controller_value |= P2_Button_Data<<i;
    P2_Button_Clock = P2BUTTON_CLOCK_HIGH; // Shift out the next bit
    P2_Button_Clock = P2BUTTON_CLOCK_LOW;
  }
	p2_controller_value >>= 5 ;
	return p2_controller_value;
}
