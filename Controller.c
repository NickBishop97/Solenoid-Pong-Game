#include "Controller.h"
#include "ball.h"
#include "Port_Init.h"
#include "SSD.h"
#include "Common.h"
#include "Paddles.h"
#include "Solenoid.h"
#include "tm4c123gh6pm.h"

void Restart(void) {
	if(restart == 1) {
		State = STARTING;
		value = 0;
		value1 = 0x0000;
		value2 = 0x0000;
		value3 = 0x0000;
		value4 = 0x0000;
		SSD_Value = 0;
		p1_score = 0;
		p2_score = 0;
		ball_Position = 0x0000001000000000;
		playerTwo_MiddlePad = 0x0010;
		playerOne_MiddlePad = 0x1000;
		playerTwo_CurrentPosition = 0x0038;
		playerOne_CurrentPosition = 0x3800;
		ball_Position_x = 0;
		player2_paddle_x = 0;
		player1_leftpress = 0 ;
		player1_rightpress = 0;
		player2_leftpress = 0;
		player2_rightpress = 0;
		p1_leftone = 0;
		p1_rightone= 0;
		p2_leftone = 0;
		p2_rightone= 0;
		p1_leftbutton_count = 0;
		p1_rightbutton_count = 0;
		p2_leftbutton_count = 0;
		p2_rightbutton_count = 0;
		seed_counter = 0; 
		direction = 0;
		paddle_hit = 0;
		rightwall = 0;
		leftwall = 0;
		p1_scored = 0;
		p2_scored = 0;
		start_game = 0;
		launch_ball = 0;
		Sound_Init(BALL_STARTING);
		Truevalue = 0;
		mode = 0;
		AI_delay = 0;
		difficulty = 0;
		pause = 0;
		temp_pause = 0;
		restart = 0;
		difficulty_press = 0;
		temp_restart = 0;
		mode_press = 0;
		end_game = 0;
		NVIC_ST_CTRL_R =  0x0007;
		player1_paddle_x = 0;
		professor_mode = 0;
		professor_delay = 0;
		win_delay = 0;
		standby_delay = 0;
		standby_game_start = 0;
		standby_mode = 0;
		mode_select = 0;
		AI_select = 0;

		updateGame(); //updates entire 8x8 grid
		updateScore(2, 2);
		updatePaddle(); //updates paddles based on button data
	}
}


void pauseMode(void) {
	if(pause == 1) {
		NVIC_ST_CTRL_R = 0x0000;  // enable SysTick with core clock and interrupts
	}
	else{
		NVIC_ST_CTRL_R = 0x0007;  // enable SysTick with core clock and interrupts
	}
}


void p1_Button_Data(void) {
	if(((p1_button_data & 0xFF)== 0xFF)&&(standby_delay == 1000))  {
		standby_mode = 1;
	}
	else if(((p1_button_data & 0xFF) != 0xFF)&&(standby_mode == 1)){
		restart = 1;
		Restart();
	}
	
	if(start_game == 1) {
		if(((p1_button_data & 0x80) == 0)&&(temp_pause == 0)){
			pause = (pause+1)%2;
			temp_pause = 1;
		
		}
		else if(((p1_button_data & 0x80) != 0)&&(temp_pause == 1)){//SW1
			temp_pause = 0;
			
		}
	}
	if(pause == 0) {
		if(((p1_button_data & 0x20) == 0) && ((p1_button_data & 0x04) == 0)) { 
			professor_mode = 1;
		}
		
		if((p1_button_data & 0x40) == 0){//SW2
			professor_mode = 0;
		}
		if(((p1_button_data & 0x01) == 0)&&(temp_restart == 0)){
			restart = 1;
			temp_restart = 1;
			Restart();
			
		}
		else if(((p1_button_data & 0x01) != 0)&&(temp_restart == 1)){//SW8
			temp_restart = 0;
			restart = 0;
		}
		

		if(((p1_button_data & 0x02) == 0)&&(player1_leftpress != 1)&&(professor_mode == 0)){
			player1_rightpress = 1;
		}
		else if(((p1_button_data & 0x04) == 0)&&(player1_rightpress != 1)&&(professor_mode == 0)){ //SW6
			player1_leftpress = 1;
		}

		else if(((p1_button_data & 0x20) == 0)&&(p2_scored == 1)){//&&(total >= 7)) {
			launch_ball = 1;
		}
		else if(professor_mode == 0) {
			player1_rightpress = 0;
			p1_rightone = 0;
			player1_leftpress = 0;
			p1_leftone = 0;
		}	
	
	}		
}

void p2_Button_Data(void) {
	if(mode == 0 && start_game == 1) {
		if(((p2_button_data & 0x04) == 0)&&(player2_leftpress != 1)){
			player2_rightpress = 1;
		}
		else if(((p2_button_data & 0x02) == 0)&&(player2_rightpress != 1)){
			player2_leftpress = 1;
		}

		else if(((p2_button_data & 0x20) == 0)&&(p1_scored == 1)){//&&(total >= 7)) {
			launch_ball = 1;
		}
		else {
			player2_rightpress = 0;
			p2_rightone = 0;
			player2_leftpress = 0;
			p2_leftone = 0;
		}
	}
}

