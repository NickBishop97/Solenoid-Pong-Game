#include "Common.h"

#include <stdlib.h>
#include <time.h>
/*
typedef struct Player{
unsigned int leftpress;
	unsigned int rightpress;
	unsigned int leftone;
	unsigned int rightone;
}player;
*/
Player player1 = {0, 0, 0, 0};
Player player2 = {0, 0, 0, 0};
unsigned long long value = 0;
unsigned long long value1 = 0x0000;
unsigned long long value2 = 0x0000;
unsigned long long value3 = 0x0000;
unsigned long long value4 = 0x0000;
unsigned long win_screen = 0; //flag for displaying win screen
unsigned long int SSD_Value = 0;
unsigned int p1_score = 0;
unsigned int p2_score = 0;
unsigned int p1_score_hex = 0;
unsigned int p2_score_hex = 0;
//Stores values to be sent to shift registers for solenoids, one bit at a time
unsigned long regs1[16];
unsigned long regs2[16];
unsigned long regs3[16];
unsigned long regs4[16];
unsigned long SSDReg[16];
//Holds boundaries of where paddles can move, as well as current positions of the paddles and ball
unsigned int 			 playerOne_BoundLeft = 0x80;
unsigned int 			 playerOne_BoundRight = 0x01;			
unsigned int 			 playerTwo_BoundLeft = 0x80;
unsigned int 			 playerTwo_BoundRight = 0x01;	
unsigned long long ball_Position = 0x0000001000000000;
unsigned long long	playerTwo_MiddlePad = 0x0010;
unsigned long long	playerOne_MiddlePad = 0x1000;
unsigned long long	playerTwo_CurrentPosition = 0x0038;
unsigned long long	playerOne_CurrentPosition = 0x3800;
unsigned long 		 ball_Position_x = 0;
unsigned long 		 player1_paddle_x = 0;
unsigned long 		 player2_paddle_x = 0;
//Flag that is set to 1 when players press buttons corresponding to moving the paddles left and right
unsigned int			 player1_leftpress = 0 ;
unsigned int			 player1_rightpress = 0;
unsigned int			 player2_leftpress = 0;
unsigned int			 player2_rightpress = 0;
//Flags to make sure paddles instantly move when button is pressed
unsigned int p1_leftone = 0;
unsigned int p1_rightone= 0;
unsigned int p2_leftone = 0;
unsigned int p2_rightone= 0;
//Variables that increment when players are constantly holding down buttons for paddle movement, creates delay
unsigned long long p1_leftbutton_count = 0;
unsigned long long p1_rightbutton_count = 0;
unsigned long long p2_leftbutton_count = 0;
unsigned long long p2_rightbutton_count = 0;
//delay between paddle movement if button is constantly held
unsigned long button_delay = 10; 
unsigned int p1_button_data; //holds button information from Parallel In - Serial Out Shift Reg
unsigned int p2_button_data;

unsigned long int seed_counter = 0; //value that will be used to set the seed for srand
																		//likely will use a sensor to get a random value to be used for this

//Determining direction ball will move in, which paddle the ball hit, which wall the ball bounced off of
unsigned int direction = 0;
unsigned int paddle_hit = 0;
unsigned int rightwall = 0;
unsigned int leftwall = 0;
//Flags used determining which player scored, allowing other player to receive ball to be launched
unsigned int p1_scored = 0;
unsigned int p2_scored = 0;
//Flag which will be used to determine when game is started
unsigned int start_game = 0;
//Flag for launching the ball
unsigned int launch_ball = 0;
unsigned int long initial_ball_speed = HARD_MODE_SPEED;//1 sec period for SysTick
unsigned int Truevalue = 0;
unsigned int mode = 0;
unsigned int long AI_delay = 0;
unsigned int difficulty = 0;
unsigned int pause = 0;
unsigned int temp_pause = 0;
unsigned int restart = 0;
unsigned int difficulty_press = 0;
unsigned int temp_restart = 0;
unsigned int mode_press = 0;
unsigned int right_sec_hex;
unsigned int left_sec_hex;
unsigned int end_game = 0;
unsigned int professor_mode = 0;
unsigned int professor_delay = 0;
unsigned int win_delay = 0;
unsigned long long  standby_delay = 0;
unsigned int standby_mode = 0;
unsigned int standby_game_start = 0;
unsigned int P1_mode = 0;
unsigned int P1_AI_delay = 0;
int mode_select = 0;
int AI_select = 0;
int score_select = 0;
int max_score = 3;
int score_index = 0;
int launch_temp = 0;
int one_press = 0;
int select_press = 0;
int score_press = 0;
int scores[4] = {3, 5, 7, 9};


void Delay(void){
	unsigned long volatile time;
  time = (100000);  
  while(time){
		time--;
  }
}

void Delay2(void){unsigned long volatile time;
 time = 1000;
  while(time){
		time--;
  }
}
/*
Function for creating a pseudorandom number
Input:
	min minimum number
	max maximum number
Output:
	returns number in the range between min and max
*/
int random_int(int min, int max)
{
	 return min + rand() % (max+1 - min);
}

