#include "SSD.h"
#include "Common.h"
#include "ShiftRegInit.h"

/*
Functiion for converting decimal value into a hexadecimal value to be set on a seven segment display
*/
unsigned long decoder(unsigned long integerVal) {
	int hex_value_temp;
	switch(integerVal) {
		case 0:
			hex_value_temp = SSD_0;
			break;
		case 1:
			hex_value_temp = SSD_1;
			break;
		case 2:
			hex_value_temp = SSD_2;
			break;
		case 3:
			hex_value_temp = SSD_3;
			break;
		case 4:
			hex_value_temp = SSD_4;
			break;
		case 5:
			hex_value_temp = SSD_5;
			break;
		case 6:
			hex_value_temp = SSD_6;
			break;
		case 7:
			hex_value_temp = SSD_7;
			break;
		case 8:
			hex_value_temp = SSD_8;
			break;
		case 9:
			hex_value_temp = SSD_9;
			break;
		case d:
			hex_value_temp = SSD_D;
			break;
		case P:
			hex_value_temp = SSD_P;
			break;
		}
	return hex_value_temp;
}

/*
Updates information displayed on scoreboard by converting integer into hexadecimal value,
and sending those values to a Serial-In Parallel-Out Shift Register
*/
void updateScore(int p1_score, int p2_score) {
	p1_score_hex = decoder(p1_score);
	p2_score_hex = decoder(p2_score);
	SSD_Value = (0xFFUL & p1_score_hex) | ((0xFFUL & p2_score_hex) << 8);
	for(int i=0;i<16;i++){
		SSDReg[i] = (SSD_Value >> i) & 1;
		ShiftReg_SSD();
	}
} 

