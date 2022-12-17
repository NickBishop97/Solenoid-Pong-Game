#include "Solenoid.h"
#include "Common.h"
#include "ShiftRegInit.h"
#include "ball.h"


void updateGame(void) {
	if(end_game == 0) {
	//sets position of the ball in front of the middle of the paddle of 
	//player who was scored on
		if(p1_scored  == 1) {
			ball_Position = playerTwo_MiddlePad << 8;
		}
		else if(p2_scored == 1) {	
			ball_Position = playerOne_MiddlePad << 40;
		}
		//64 bit value is set with the positions of player paddles and ball, then seperated into 4 variables that
		//each take 16 bits from this value for easy access when used in write_reg function
		value = ((0xFFFFU & playerOne_CurrentPosition)<<48) | (0xFFFFU & playerTwo_CurrentPosition) | (ball_Position);
		value1 = 0xFFFF &(value >> 48);
		value2 = 0xFFFF &(value >> 32);
		value3 = 0xFFFF &(value >> 16);
		value4 = 0xFFFF & value;    
		
		for(int i=0;i<16;i++){
			regs1[i] = (value1 >> i) & 1;
			regs2[i] = (value2 >> i) & 1;
			regs3[i] = (value3 >> i) & 1;
			regs4[i] = (value4 >> i) & 1;
			Delay2();
			write_reg();	
		}
	}
	
	else if(end_game == 1) {
		win_screen ^= (0xFFFF);
		if(p1_score == max_score) {
			 for(int i=0;i<16;i++){
				 if(win_delay == 200) {
					regs1[i] = (win_screen >> i) & 1;
					regs2[i] = (0 >> i) & 1;
					regs3[i] = (0 >> i) & 1;
					regs4[i] = (0 >> i) & 1;
					win_delay = 0;
					write_reg();
				 }
				 else{
					 win_delay += 1;
				 }
			 }
		 }
	
		else if(p2_score == max_score) {
			 for(int i=0;i<16;i++){
				 if(win_delay == 200) {
					regs1[i] = (0 >> i) & 1;
					regs2[i] = (0 >> i) & 1;
					regs3[i] = (0 >> i) & 1;
					regs4[i] = (win_screen >> i) & 1;
					 win_delay = 0;
					//Delay(); 
					write_reg(); 
				 }
				 else{
					 win_delay += 1;
				 }
			}
		}
	}
}

