#include "AI.h"
#include "Common.h"
/*
Function for turning on AI mode for player 1. Pressing SW6 and SW3 simmultaneusly will turn professor
mode on where it will follow the ball on its own. if standby mode is activated, professor mode will act
as a normal AI where it can miss the ball. Pressing SW2 turns professor mode off
*/

void ProfessorMode() {
	if(professor_mode == 1) {//clears button press information to prevent data from being read twice
		player1_rightpress = 0;
		p1_rightone = 0;
		player1_leftpress = 0;
		p1_leftone = 0;
	}
	//delay between paddle following ball reached and standby mode is off
	if((professor_mode == 1) && (professor_delay == 5) && (standby_mode == 0)) {
			professor_delay = 0;
			if(ball_Position_x > player1_paddle_x) {//ball is to the left of paddle
				player1_leftpress = 1;
			}
				
			else if(ball_Position_x < player1_paddle_x) {//ball is to the right of paddle
				player1_rightpress = 1;
			}
			else{										//this means ball is coming directly to paddle, so no movement
				player1_leftpress = 0;
				player1_rightpress = 0;
			}
			if(p2_scored == 1) {  //launches ball automatically when scored on
				launch_ball = 1;
			}
	}
	else if(difficulty == 2 && professor_delay == 15) {//
			professor_delay = 0;
			if((paddle_hit == 2)&&(ball_Position&0x0000000000FFFFFF)==0) {
					if(ball_Position_x > player1_paddle_x) {
							player1_leftpress = 1;
					}
						
					else if(ball_Position_x < player1_paddle_x) {
							player1_rightpress = 1;
					}
					else{
							player1_leftpress = 0;
							player1_rightpress = 0 ;
					}
						
			}
			else{
				player1_leftpress = random_int(0,1);
				player1_rightpress = random_int(0,1);
			}
			if(p2_scored == 1) {
					launch_ball = 1;
			}
		}		
	
	else if(professor_mode == 1){
		professor_delay += 1;
	}
	else{
		professor_delay = 0;
	}
}


void AI_Mode(void) {
	if(mode == 1) {
		player2_rightpress = 0;
		p2_rightone = 0;
		player2_leftpress = 0;
		p2_leftone = 0;
	}
	if((mode == 1)&&(AI_delay == 15)){
			AI_delay = 0;
			if(difficulty == 0) {
			if((paddle_hit == 1)&&(ball_Position&0xFFFFFFFFFFF00000)==0) {
					if(ball_Position_x > player2_paddle_x) {
							player2_leftpress = 1;
					}
						
					else if(ball_Position_x < player2_paddle_x) {
							player2_rightpress = 1;
					}
					else{
							player2_leftpress = 0;
							player2_rightpress = 0 ;
					}
				}
				else{
					player2_leftpress = random_int(0,1);
					player2_rightpress = random_int(0,1);
				}
				if(p1_scored == 1) {
					launch_ball = 1;
				}	
			}
			else if(difficulty == 1) {
					if((paddle_hit == 1)&&(ball_Position&0xFFFFFFFF00000000)==0) {
						if(ball_Position_x > player2_paddle_x) {
								player2_leftpress = 1;
						}
							
						else if(ball_Position_x < player2_paddle_x) {
								player2_rightpress = 1;
						}
						else{
								player2_leftpress = 0;
								player2_rightpress = 0 ;
						}
					}
					else{
						player2_leftpress = random_int(0,1);
						player2_rightpress = random_int(0,1);
					}
					if(p1_scored == 1) {
						launch_ball = 1;
					}		
				
			}			
			else if(difficulty == 2) {
				if((paddle_hit == 1)&&(ball_Position&0xFFFFFF0000000000)==0) {
						if(ball_Position_x > player2_paddle_x) {
								player2_leftpress = 1;
						}
							
						else if(ball_Position_x < player2_paddle_x) {
								player2_rightpress = 1;
						}
						else{
								player2_leftpress = 0;
								player2_rightpress = 0 ;
						}
							
				}
				else{
					player2_leftpress = random_int(0,1);
					player2_rightpress = random_int(0,1);
				}
				if(p1_scored == 1) {
						launch_ball = 1;
				}
			}		
	}
	else if(mode == 1){
		AI_delay += 1;
	}
	else{
		AI_delay = 0;
	}
}

