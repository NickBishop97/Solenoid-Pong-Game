#include "ball.h"
#include "Controller.h"
#include "Common.h"
#include "tm4c123gh6pm.h"


enum FSMSTATE State = STARTING;
void BallCoordinates(void) {
	if(ball_Position & 0x0080808080808000) {
		ball_Position_x = 8;
	}
	else if(ball_Position & 0x0040404040404000) {
		ball_Position_x = 7;
	}
	else if(ball_Position & 0x0020202020202000) {
		ball_Position_x = 6;
	}
	else if(ball_Position & 0x0010101010101000) {
		ball_Position_x = 5;
	}
	else if(ball_Position & 0x0008080808080800) {
		ball_Position_x = 4;
	}
	else if(ball_Position & 0x0004040404040400) {
		ball_Position_x = 3;
	}
	else if(ball_Position & 0x0002020202020200) {
		ball_Position_x = 2;
	}
	else if(ball_Position & 0x0001010101010100) {
		ball_Position_x = 1;
	}
}

enum FSMSTATE ballDirection(int hit, int num) {
	if(hit == 1) {
		if(num == 1) {
			return MOVEUP;
		}
		else if(num == 2) {
			return MOVEDIAGLEFT;
		}
		else if(num == 3) {
			return MOVEDIAGRIGHT;
				}
	}
	else if(hit == 2) {
		if(num == 1) {
			return MOVEDOWN;
		}
		else if(num == 2) {
			return MOVEDIAGLEFT;
		}
		else if(num == 3){
			return MOVEDIAGRIGHT;
			}
	}
}


/*
SysTick Handler periodically updates the position of the ball based on its current state
*/

void SysTick_Handler(void){
	switch(State) {
		case STARTING:
		//	NVIC_ST_RELOAD_R = initial_ball_speed;
			paddle_hit = random_int(1,2);
			direction = random_int(1,3);
			if(start_game == 1) {
				State = ballDirection(paddle_hit, direction);
			}
			else if(standby_game_start == 1) {
				State = ballDirection(paddle_hit, direction);
			}
			break;
		case MOVEUP:
			//NVIC_ST_RELOAD_R = initial_ball_speed;// reload value
			if((ball_Position&(playerTwo_CurrentPosition<<8))||(ball_Position&(playerTwo_CurrentPosition))){//about to hit bounce off player 2 paddle
				paddle_hit = 2;//player 2 paddle was last hit
				direction = random_int(1,3);
				changeSpeed();
				State = ballDirection(paddle_hit,direction);
			}
			else if((ball_Position & 0x00000000000000FF) == 0){//ball has not reached player 2's paddle row
				ball_Position >>= 8; //ball position shifted to next row going up to player 2
			}			
			else {//player 1 scored a point
				p1_scored = 1;
				State = POINTMADE;
			}
			break;
		case MOVEDOWN:
			//NVIC_ST_RELOAD_R = initial_ball_speed;// reload value
			if((ball_Position&(playerOne_CurrentPosition<<40))||(ball_Position&(playerOne_CurrentPosition<<48))){//ball about to bounce off player 1 paddle
				paddle_hit = 1;//player 1 paddle was last hit
				direction = random_int(1,3);
				changeSpeed();
				State = ballDirection(paddle_hit,direction);
				
			}
			else if((ball_Position & 0xFF00000000000000) == 0){//ball hasnt reached player 1's paddle row
				ball_Position <<= 8; //ball position shifted to next row going down to player 1
			}			
			else {//player 2 scored a point
				p2_scored = 1;
				State = POINTMADE;
			}
			break;
		case MOVEDIAGLEFT:
		//	NVIC_ST_RELOAD_R = initial_ball_speed;// reload value
			if(((ball_Position&(playerTwo_CurrentPosition<<8))||(ball_Position&(playerTwo_CurrentPosition)))&&(paddle_hit == 1)){//about to hit the player 2 paddle
				paddle_hit = 2;
				direction = random_int(1,3);
				changeSpeed();
				State = ballDirection(paddle_hit,direction);
				
			}
			else if(((ball_Position&(playerOne_CurrentPosition<<40))||(ball_Position&(playerOne_CurrentPosition<<48)))&&(paddle_hit == 2)){//about to hit player 1 paddle
				paddle_hit = 1;
				direction = random_int(1,3);
				changeSpeed();
				State = ballDirection(paddle_hit,direction);
				
			}		
			else if((paddle_hit == 2) && (ball_Position & 0x0080808080808000)) {//ball bounced off left wall
				//NVIC_ST_RELOAD_R /= 2;// reload value
				ball_Position <<= 7;
				ball_Position_x >>= 1;
				State = MOVEDIAGRIGHT;		
			}
			else if((paddle_hit == 1) && (ball_Position & 0x0080808080808000)) {//ball bounced off left wall
				//NVIC_ST_RELOAD_R /= 2;// reload value
				ball_Position >>= 9;
				ball_Position_x >>= 1;
				State = MOVEDIAGRIGHT;
			}	
			else if((paddle_hit == 1) && ((ball_Position & 0x00000000000000FF)!=0)) {//player 1 scored a point
				p1_scored = 1;
				State = POINTMADE;
			}
			else if((paddle_hit == 2) && ((ball_Position & 0xFF00000000000000)!=0)) {//player 2 scored a point
				p2_scored = 1;
				State = POINTMADE;
			}
			else if(paddle_hit == 1) {//ball travels diagonally left towards player 2
				ball_Position >>= 7;
				ball_Position_x <<= 1; 
			}
			else if(paddle_hit == 2) {//ball travels diagonally left towards player 1
				ball_Position <<= 9;
				ball_Position_x <<= 1;
			}
			break;
		case MOVEDIAGRIGHT:
			//NVIC_ST_RELOAD_R = initial_ball_speed;// reload value
			if(((ball_Position&(playerTwo_CurrentPosition<<8))||(ball_Position&(playerTwo_CurrentPosition)))&&(paddle_hit == 1)){//about to hit player 2 paddle
				paddle_hit = 2;
				direction = random_int(1,3);
				changeSpeed();
				State = ballDirection(paddle_hit,direction);
				
			}
			else if(((ball_Position&(playerOne_CurrentPosition<<40))||(ball_Position&(playerOne_CurrentPosition<<48)))&&(paddle_hit == 2)){//about to hit player 1 paddle
				paddle_hit = 1;
				direction = random_int(1,3);
				changeSpeed();
				State = ballDirection(paddle_hit,direction);		
			}
			else if((paddle_hit == 2) && (ball_Position & 0x0001010101010100)) {//ball bounced off right wall
				//NVIC_ST_RELOAD_R /= 2;// reload value
				ball_Position <<= 9;
				ball_Position_x <<= 1;
				State = MOVEDIAGLEFT;
			}
			else if((paddle_hit == 1) && (ball_Position & 0x0001010101010100)) {//ball bounced off right wall
			//	NVIC_ST_RELOAD_R /= 2;// reload value
				ball_Position >>= 7;
				ball_Position_x <<= 1;
				State = MOVEDIAGLEFT;
			}
			else if((paddle_hit == 1) && ((ball_Position & 0x00000000000000FF)!=0)) {//player 1 scored
				p1_scored = 1;
				State = POINTMADE;
			}
			else if((paddle_hit == 2) && ((ball_Position & 0xFF00000000000000)!=0)) {//player 2 scored
				p2_scored = 1;
				State = POINTMADE;
			}
			else if(paddle_hit == 1) {//ball travels diagonally right towards player 2
				ball_Position >>= 9;
				ball_Position_x >>= 1;
			}
			else if(paddle_hit == 2) {//ball travels diagonally right towards player 1
				ball_Position <<= 7;
				ball_Position_x >>= 1;
			}
			break;
		case POINTMADE:
			NVIC_ST_CTRL_R = 0;
			NVIC_ST_RELOAD_R = BALL_STARTING;// reload current initial value
			NVIC_ST_CURRENT_R = 0;      // any write to current clears it
			NVIC_ST_CTRL_R = 0x0007;
			if((p1_score == 2) || (p2_score == 2)) {
				end_game = 1;
				State = ENDGAME;
			}
			else if((p1_scored  == 1)&&(paddle_hit == 1)) {
				p1_score += 1;
				paddle_hit = 2;
				direction = random_int(1,3);
			}
			else if((launch_ball == 1)&&(p1_scored == 1)) {//player 2 has pressed button to launch the ball
				State = ballDirection(paddle_hit,direction);
				p1_scored = 0;
				launch_ball = 0;
			}
			
			else if((p2_scored == 1)&&(paddle_hit == 2)) {
				p2_score += 1;
				paddle_hit = 1;
				direction = random_int(1,3);
			}
			else if((launch_ball== 1)&&(p2_scored == 1)) {//player 1 has pressed button to launch the ball
				State = ballDirection(paddle_hit,direction);
				p2_scored = 0;
				launch_ball = 0;
			}
			
			break;
		case ENDGAME:
			if(standby_game_start == 1) {
				restart = 1;
				Restart();
				standby_delay = 1000;
			}
			else {
				NVIC_ST_CTRL_R = 0;
			}
			break;
	}
}

void changeSpeed(void) {
	if (NVIC_ST_RELOAD_R >= 2000000) {
		NVIC_ST_CTRL_R = 0;
		NVIC_ST_RELOAD_R -= 400000;// reload current initial value
		NVIC_ST_CURRENT_R = 0;      // any write to current clears it
		NVIC_ST_CTRL_R = 0x0007;
	}
}
