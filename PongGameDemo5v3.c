/*
PongGameDemo5Ver3.c
Source code for Pong Game
Most functionalities of the game have been implemented, these include
Sending data to solenoids, receiving data from buttons, paddles moving, ball moving
based on current state
Still need to implement seven segment display into design for the scoreboard, a pause or start menu
playing against an AI, 

This Version: added in random functionality using sensor

*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//#include <time.h>
#include <string.h>
#include "tm4c123gh6pm.h"
#include "UART.h"
#include "ADCSWTrigger.h"
#include "Common.h"
#include "ShiftRegInit.h"
#include "SSD.h"
#include "ball.h"
#include "Controller.h"
#include "Port_Init.h"
#include "AI.h"
#include "UART_Debug.h"
#include "Paddles.h"
#include "Solenoid.h"

extern void EnableInterrupts(void);
extern void WaitForInterrupt(void);
extern void DisableInterrupts(void);		

void GameSettings(void);
int one_press = 0;
int select_press = 0;
void GameSettings(void) {
	if((mode_select == 0 || AI_select == 0) && standby_mode == 0) {
		if(mode == 0) {
			updateScore(P, 2);
		
			if(((p1_button_data & 0x20) == 0)&&(select_press == 0)){//&&(total >= 7)) {
				mode_select = 1;
				AI_select = 1;
				select_press = 1;
			}
			else if((player1_rightpress)&&(one_press == 0)) {
				mode = (mode+1)%2;
				one_press = 1;
			}
			else if(player1_rightpress == 0){
				one_press = 0;
			}
			if((p1_button_data & 0x20) != 0){//SW1
				select_press = 0;
			}
		}
		else if(mode == 1 && mode_select == 0) {
			updateScore(P,1);
		
			if(((p1_button_data & 0x20) == 0)&&(select_press == 0)){//&&(total >= 7)) {
				mode_select = 1;
				select_press = 1;
			}
			else if((player1_rightpress)&&(one_press == 0)) {
				mode = (mode+1) %2;
				one_press = 1;
			}
			else if(player1_rightpress == 0){
				one_press = 0;
			}
			if((p1_button_data & 0x20) != 0){//SW1
				select_press = 0;
			}
		}
		else if(mode == 1 && mode_select == 1 && AI_select == 0) {
			if(difficulty == 0) {
				updateScore(1, d);
				if(((p1_button_data & 0x20) == 0)&&(select_press == 0)){//&&(total >= 7)) {
					AI_select = 1;
					select_press = 1;
				}
				else if((player1_rightpress)&&(one_press == 0)) {
					difficulty = (difficulty +1) %3;
					one_press = 1;
				}
				else if(player1_rightpress == 0){
					one_press = 0;
				}
				if((p1_button_data & 0x20) != 0){//SW1
					select_press = 0;
			}
			}
			else if(difficulty == 1) {
				updateScore(2, d);
				if(((p1_button_data & 0x20) == 0)&&(select_press == 0)){//&&(total >= 7)) {
					AI_select = 1;
					select_press = 1;
				}
				else if((player1_rightpress)&&(one_press == 0)) {
					difficulty = (difficulty +1) %3;
					one_press = 1;
				}
				else if(player1_rightpress == 0){
					one_press = 0;
				}
				if((p1_button_data & 0x20) != 0){//SW1
					select_press = 0;
				}
				
			}
			else if(difficulty == 2) {
				updateScore(3, d);
				if(((p1_button_data & 0x20) == 0)&&(select_press == 0)){//&&(total >= 7)) {
					AI_select = 1;
					select_press = 1;
				}
				else if((player1_rightpress)&&(one_press == 0)) {
					difficulty = (difficulty +1) %3;
					one_press = 1;
				}
				else if(player1_rightpress == 0){
					one_press = 0;
				}
				if((p1_button_data & 0x20) != 0){//SW1
					select_press = 0;
				}
			}
		}
	}
	else if(mode_select == 1 && AI_select == 1) {
		start_game = 1;
		one_press = 0;
		select_press = 0;
	}
	/*
	Starts with the SSD displaying 2P
	In player vs player mode
	
	From here you can press button to confirm
	and start the game, 
	
	or you can press right button to cycle to next option which is AI mode
	
	if AI mode is selected, itll go to the next option of display D1
	which is difficululty 1, which can be selected to choose that difficulty level an start the game
	
	or cycle to D2 or D3 to start the game in those difficulties
	
	*/
}

int main(void){
	DisableInterrupts();
	GPIOPortA_Init();
	GPIOPortB_Init();
	PortD_InIt();
	ADC0_InitSWTriggerSeq3_Ch1();
	UART_Init();
	srandSeed();
	srand(Truevalue); 
	Sound_Init(BALL_STARTING);
	mode = 0;
	ball_Position = 0x0000001000000000;
	playerTwo_MiddlePad = 0x0010;
	playerOne_MiddlePad = 0x1000;
	playerTwo_CurrentPosition = 0x0038;
	playerOne_CurrentPosition = 0x3800;
	updateGame(); //updates entire 8x8 grid
	updateScore(p1_score, p2_score);
	updatePaddle(); //updates paddles based on button data
	EnableInterrupts();
	while(1) {
		UART0_OutUDec(Truevalue);
		p1_button_data = p1_button_write_reg();//receives button data
		p2_button_data = p2_button_write_reg();//receives button data
		p1_Button_Data();
		p2_Button_Data();
		pauseMode();
		GameSettings();
		if((pause == 0)&&(start_game == 1)) {
			BallCoordinates();
			player1_paddle_x = PaddleCoordinates(playerOne_MiddlePad>>8);
			player2_paddle_x = PaddleCoordinates(playerTwo_MiddlePad);
			ProfessorMode();
			AI_Mode();
			updateGame(); //updates entire 8x8 grid
			updateScore(p1_score, p2_score);
			updatePaddle(); //updates paddles based on button data
			OutCRLF();
			//showPosition(); //updates 8x8 grid on serial terminal
			OutCRLF();
		}
		else if((start_game == 0)&&(standby_mode == 1)&&(standby_delay == 1000)) {
			standby_game_start = 1;
			mode = 1;
			difficulty = 2;
			professor_mode = 1;
			BallCoordinates();
			player1_paddle_x = PaddleCoordinates(playerOne_MiddlePad>>8);
			player2_paddle_x = PaddleCoordinates(playerTwo_MiddlePad);
			ProfessorMode();
			AI_Mode();
			updateGame(); //updates entire 8x8 grid
			updateScore(p1_score, p2_score);
			updatePaddle(); //updates paddles based on button data
			OutCRLF();
			//showPosition(); //updates 8x8 grid on serial terminal
			OutCRLF();
			
		}
		else if(((p1_button_data & 0xFF) == 0xFF)&&(standby_delay < 1000)){
			standby_delay += 1;
		}
		else{
			standby_delay = 0;
		}
	}	
}

