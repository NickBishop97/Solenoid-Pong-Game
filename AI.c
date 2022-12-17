#include "AI.h"
#include "Common.h"

/*
Function for turning on AI mode for player 1. Pressing SW6 and SW3 simmultaneusly will turn professor
mode on where it will follow the ball on its own. if standby mode is activated, professor mode will act
as a normal AI where it can miss the ball. Pressing SW2 turns professor mode off
*/

void ProfessorMode() {
	if(professor_mode == 1) {//clears button press information to prevent data from being read twice
		player1.rightpress = 0;
		player1.rightone = 0;
		player1.leftpress = 0;
		player1.leftone = 0;
	}
	//delay between paddle following ball reached and standby mode is off
	if((professor_mode == 1) && (professor_delay == 5) && (standby_mode == 0)) {
		professor_delay = 0;
		if(ball_Position_x > player1_paddle_x) {//ball is to the left of paddle
			player1.leftpress = 1;
		}
		else if(ball_Position_x < player1_paddle_x) {//ball is to the right of paddle
			player1.rightpress = 1;
		}
		else{										//this means ball is coming directly to paddle, so no movement
			player1.leftpress = 0;
			player1.rightpress = 0;
		}
		if(p2_scored == 1) {  //launches ball automatically when scored on
			launch_ball = 1;
		}
	}
	else if(difficulty == 2 && professor_delay == 15) {//behavior of player 1 AI during standby mode
		professor_delay = 0;
		if((paddle_hit == 2)&&(ball_Position&0x0000000000FFFFFF)==0) {
				if(ball_Position_x > player1_paddle_x) {
						player1.leftpress = 1;
				}
				else if(ball_Position_x < player1_paddle_x) {
						player1.rightpress = 1;
				}
				else{
						player1.leftpress = 0;
						player1.rightpress = 0 ;
				}
		}
		else{//sets paddle movement to random value
			player1.leftpress = random_int(0,1);
			player1.rightpress = random_int(0,1);
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

/*
Function for the settings of player 2 AI
*/
void AI_Mode(void) {
	if(mode == 1) {
		player2.rightpress = 0;
		player2.rightone = 0;
		player2.leftpress = 0;
		player2.leftone = 0;
	}
	if((mode == 1)&&(AI_delay == 15)){
		AI_delay = 0;
		AI_Behavior(p1_scored, difficulty, &player2);
	}
	else if(mode == 1){
		AI_delay += 1;
	}
	else{
		AI_delay = 0;
	}
}

/*
Function for setting the behavior of the AI based on difficulty setting set. 
AI tracks the ball based on the balls current location and x coordinates
*/

void AI_Behavior(int player_scored, int diff, Player *player) {
	int ballApproach = 0;
	
	if(diff == EASY) {
		ballApproach = ((paddle_hit == PLAYER1_HIT)&&(ball_Position&0xFFFFFFFFFFF00000)==0);
	}
	else if(diff == INTERMEDIATE) {
		ballApproach = ((paddle_hit == PLAYER1_HIT)&&(ball_Position&0xFFFFFFFF00000000)==0);
	}
	else if(diff == HARD) {
		ballApproach = ((paddle_hit == PLAYER1_HIT)&&(ball_Position&0xFFFFFF0000000000)==0);
	}
	if(ballApproach) {
		if(ball_Position_x > player2_paddle_x) {
			player -> leftpress = 1;
		}
		else if(ball_Position_x < player2_paddle_x) {
			player -> rightpress  = 1;
		}
		else{
			player -> leftpress = 0;
			player -> rightpress = 0 ;
		}
	}
	else{
		player -> leftpress  = random_int(0,1);
		player -> rightpress = random_int(0,1);
	}
	if(player_scored == 1) {
		launch_ball = 1;
	}
}
