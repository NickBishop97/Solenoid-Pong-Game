#include "UART_Debug.h"
#include "UART.h"
#include "tm4c123gh6pm.h"
#include "Common.h"
#include "ball.h"

#include "string.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
Function for displaying the entire 8x8 grid of solenoids and their values
on a serial terminal using UART.
*/
void showPosition(void) {
	char row9[80];
	char row8[80];
	char row7[80];
	char row6[80];
	char row5[80];
	char row4[80];
	char row3[80];
	char row2[80];
	char row1[80];
	
	UART0_OutString("\x1b[H");
	UART0_OutString("8x8 Grid Positions");
	OutCRLF();
  
	
	sprintf(row8, "%llx", (0xFF & (value>>0)));
	HexToBin2(row8);
	sprintf(row7, "%llx", (0xFF & (value>>8)));
	HexToBin2(row7);
	sprintf(row6, "%llx", (0xFF & (value>>16)));
	HexToBin2(row6);
	sprintf(row5, "%llx", (0xFF & (value>>24)));
	HexToBin2(row5);
	sprintf(row4, "%llx", (0xFF & (value>>32)));
	HexToBin2(row4);
	sprintf(row3, "%llx", (0xFF & (value>>40)));
	HexToBin2(row3);
	sprintf(row2, "%llx", (0xFF & (value>>48)));
	HexToBin2(row2);
	sprintf(row1, "%llx", (0xFF & (value>>56)));
	HexToBin2(row1);
	sprintf(row9, "%x", (p1_button_data));
	HexToBin2(row9);
	//(standby_delay);
	
	/*
	for(int i= 0;i < 64;i = i+8) {
	sprintf(a, "%llx", (0xFF & (value>>i)));
	HexToBin2(a);
	*/
	
	OutCRLF();
	//UART0_OutUDec(State);
	OutCRLF();
	//Delay2();
}
/*
Function for converting a hexadecimal value into a binary number
Input:
	*row_value - a pointer to a character
Output:
	Outputs temp onto serial terminal
*/
void HexToBin2(char* row_value) {
	char temp[100];
	if(row_value[1] == '\0') {
		UART0_OutString("0000");
	}
	long int i = 0;
	while((row_value[i])) 
    {
        switch(row_value[i])
        {
            case '0':
                strcat(temp, "0000");
                break;
            case '1':
                strcat(temp, "0001");
                break;
            case '2':
                strcat(temp, "0010");
                break;
            case '3':
                strcat(temp, "0011");
                break;
            case '4':
                strcat(temp, "0100");
                break;
            case '5':
                strcat(temp, "0101");
                break;
            case '6':
                strcat(temp, "0110");
                break;
            case '7':
                strcat(temp, "0111");
                break;
            case '8':
                strcat(temp, "1000");
                break;
            case '9':
                strcat(temp, "1001");
                break;
            case 'a':
            case 'A':
                strcat(temp, "1010");
                break;
            case 'b':
            case 'B':
                strcat(temp, "1011");
                break;
            case 'c':
            case 'C':
                strcat(temp, "1100");
                break;
            case 'd':
            case 'D':
                strcat(temp, "1101");
                break;
						case 'e':
            case 'E':
                strcat(temp, "1110");
                break;
            case 'f':
            case 'F':
                strcat(temp, "1111");
                break;
            default:
                
						break;
					}
					i++;
				}	
		UART0_OutString(temp);
		OutCRLF();
		*temp = NULL;
}

