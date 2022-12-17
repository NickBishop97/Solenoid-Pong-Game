/*
PongGameFinalVer1.c
This project contains the entire source code for implementing a game of a pong on an 8x8 grid of solenoids. 
The code consists of the logic for implementing various functionalities which include:
Paddles that can be moved using buttons from a custom PCB controller
A ball that is controlled by a FSM with being able to travel across the grid, bounce of paddles and walls, have its speed changed
A SSD within the PCB for the controller which displays the score and other information
An AI mode which allows players to play against an AI
Standby mode for two AIs to play against each other 


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
#include "Gamesettings.h"

extern void EnableInterrupts(void);
extern void WaitForInterrupt(void);
extern void DisableInterrupts(void);		







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
	updateGame(); //updates entire 8x8 grid
	updateScore(p1_score, p2_score);
	updatePaddle(); //updates paddles based on button data
	EnableInterrupts();
	while(1) {
		//UART0_OutUDec(Truevalue);
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
		else if((start_game == 0)&&(standby_mode == 1)&&(standby_delay == 2000)) {
			standby_game_start = 1;
			mode = P1_MODE;
			difficulty = HARD;
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
		else if(((p1_button_data & ALL_SW) == 0xFF)&&(standby_delay < 2000)){
			standby_delay += 1;
		}
		else{
			standby_delay = 0;
		}
	}	
}

