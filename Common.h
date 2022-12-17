#ifndef _COMMON_H_
#define _COMMON_H_

#define Data1  (*((volatile unsigned long*)0x40005040)) //PB4 Data pin for shift reg 1-2
#define Data2  (*((volatile unsigned long*)0x40005080)) //PB5 Data pin for shift reg 3-4
#define Data3  (*((volatile unsigned long*)0x40005100)) //PB6 Data pin for shift reg 5-6
#define Data4  (*((volatile unsigned long*)0x40005200)) //PB7 Data pin for shift reg 7-8
#define Latch1 (*((volatile unsigned long*)0x40005004)) //PB0 Latch pin for shift reg 1-2
#define Latch2 (*((volatile unsigned long*)0x40005008)) //PB1 Latch pin for shift reg 3-4
#define Latch3 (*((volatile unsigned long*)0x40005010)) //PB2 Latch pin for shift reg 5-6
#define Latch4 (*((volatile unsigned long*)0x40005020)) //PB3 Latch pin for shift reg 7-8
#define Clock  (*((volatile unsigned long*)0x40004010)) //PA2 Clock pin for all shift regs
#define P1_Button_Clock  (*((volatile unsigned long*)0x40007010)) //PD2 Clock pin player 1 shift reg
#define P1_Button_Load   (*((volatile unsigned long*)0x40007020)) //PD3 Load pin for player 1 shift reg
#define P1_Button_Data 	 (*((volatile unsigned long*)0x40007100)) //PD6 Data pin for player 1 shift reg
#define P2_Button_Clock  (*((volatile unsigned long*)0x40004020)) //PA3 Clock pin player 2 shift reg
#define P2_Button_Load   (*((volatile unsigned long*)0x40004040)) //PA4 Load pin for player 2 shift reg
#define P2_Button_Data 	 (*((volatile unsigned long*)0x40004080)) //PA5 Data pin for player 2 shift reg
#define SSD_Clock  			 (*((volatile unsigned long*)0x40024080)) //PE5 Clock pin for SSDs
#define SSDP1_Data  		 (*((volatile unsigned long*)0x40007200)) //PD7 Data pin for SSD P1
#define SSDP1_Latch  	 	 (*((volatile unsigned long*)0x40024008)) //PE1 Latch pin for SSD P1
#define SSDP2_Data  		 (*((volatile unsigned long*)0x40024020)) //PE3 Data pin for SSD P2
#define SSDP2_Latch  		 (*((volatile unsigned long*)0x40024040)) //PE4 Latch pin for SSD P2
	
//Values for setting Latch and Clock pins of shift registers for solenoids
#define LATCH1_HIGH 0x01 
#define LATCH2_HIGH 0x02
#define LATCH3_HIGH 0x04
#define LATCH4_HIGH 0x08
#define LATCH_LOW  0x00
#define CLOCK_HIGH 0x04
#define CLOCK_LOW  0x00

#define SSD_CLOCK_HIGH 0x20
#define SSD_CLOCK_LOW  0x00
#define P1_SSD_LATCH_HIGH 0x02
#define P1_SSD_LATCH_LOW  0x00
#define P2_SSD_LATCH_HIGH 0x10
#define P2_SSD_LATCH_LOW  0x00
//Values for setting Latch and Clock pins of shift registers for buttons
#define P1BUTTON_LATCH_HIGH 0x08
#define P1BUTTON_LATCH_LOW  0x00
#define P1BUTTON_CLOCK_HIGH 0x04
#define P1BUTTON_CLOCK_LOW  0x00

#define P2BUTTON_LATCH_HIGH 0x10
#define P2BUTTON_LATCH_LOW  0x00
#define P2BUTTON_CLOCK_HIGH 0x08
#define P2BUTTON_CLOCK_LOW  0x00

#define NVIC_ST_CTRL_COUNT      0x00010000  // Count flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode

//defintions for ball, buttons, scoreboard, paddle values
#define BALL_STARTING 5000000
#define EASY_MODE_SPEED 7000000
#define MEDIUM_MODE_SPEED 5000000
#define HARD_MODE_SPEED 2000000
#define EASY 0
#define INTERMEDIATE 1
#define HARD 2
#define PLAYER1_HIT 1
#define PLAYER2_HIT 2
#define SW1 0x80
#define SW2 0x40
#define SW3 0x20
#define SW4 0x10
#define SW5 0x08
#define SW6 0x04
#define SW7 0x02
#define SW8 0x01
#define ALL_SW 0xFF
#define P2_MODE 0
#define P1_MODE 1
#define P1_PADDLE_LEFTBOUND 0x8000
#define P1_PADDLE_RIGHTBOUND 0x0100
#define P2_PADDLE_LEFTBOUND 0x0080
#define P2_PADDLE_RIGHTBOUND 0x0001

#define SSD_0 ~0xFC
#define SSD_1 ~0x60 
#define SSD_2 ~0xDA
#define SSD_3 ~0xF2
#define SSD_4 ~0x66
#define SSD_5 ~0xB6
#define SSD_6 ~0xBE
#define SSD_7 ~0xE0
#define SSD_8 ~0xFE
#define SSD_9 ~0xF6
#define SSD_A ~0xEE
#define SSD_B ~0x3E
#define SSD_C ~0x9C
#define SSD_D ~0x7A
#define SSD_E ~0x9E
#define SSD_F ~0x8E
#define SSD_P ~0xCE

#define d 20
#define P 21
#define S 22

typedef struct{
	unsigned int leftpress;
	unsigned int rightpress;
	unsigned int leftone;
	unsigned int rightone;
} Player;

extern Player player1;
extern Player player2;
//Holds 8x8 Information and is seperated into four 16 bit values for sending to each set of 2 shift registers
extern unsigned long long value;
extern unsigned long long value1;
extern unsigned long long value2;
extern unsigned long long value3;
extern unsigned long long value4;
extern unsigned long win_screen; //flag for displaying win screen
extern unsigned long int SSD_Value;
extern unsigned int p1_score;
extern unsigned int p2_score;
extern unsigned int p1_score_hex;
extern unsigned int p2_score_hex;
//Stores values to be sent to shift registers for solenoids, one bit at a time
extern unsigned long regs1[16];
extern unsigned long regs2[16];
extern unsigned long regs3[16];
extern unsigned long regs4[16];
extern unsigned long SSDReg[16];
//Holds boundaries of where paddles can move, as well as current positions of the paddles and ball
extern unsigned int 			 playerOne_BoundLeft;
extern unsigned int 			 playerOne_BoundRight;			
extern unsigned int 			 playerTwo_BoundLeft;
extern unsigned int 			 playerTwo_BoundRight;
extern unsigned long long playerOne_MiddlePad;											
extern unsigned long long playerTwo_MiddlePad;	
extern unsigned long long playerOne_CurrentPosition;											
extern unsigned long long playerTwo_CurrentPosition;	
extern unsigned long long ball_Position;
extern unsigned long 		 ball_Position_x;
extern unsigned long 		 player1_paddle_x;
extern unsigned long 		 player2_paddle_x;
//Flag that is set to 1 when players press buttons corresponding to moving the paddles left and right
extern unsigned int			 player1_leftpress;
extern unsigned int			 player1_rightpress;
extern unsigned int			 player2_leftpress;
extern unsigned int			 player2_rightpress;
//Flags to make sure paddles instantly move when button is pressed
extern unsigned int p1_leftone;
extern unsigned int p1_rightone;
extern unsigned int p2_leftone;
extern unsigned int p2_rightone;
//Variables that increment when players are constantly holding down buttons for paddle movement, creates delay
extern unsigned long long p1_leftbutton_count;
extern unsigned long long p1_rightbutton_count;
extern unsigned long long p2_leftbutton_count;
extern unsigned long long p2_rightbutton_count;
//delay between paddle movement if button is constantly held
extern unsigned long button_delay; 
extern unsigned int p1_button_data; //holds button information from Parallel In - Serial Out Shift Reg
extern unsigned int p2_button_data;

extern unsigned long int seed_counter; //value that will be used to set the seed for srand
																		//likely will use a sensor to get a random value to be used for this

//Determining direction ball will move in, which paddle the ball hit, which wall the ball bounced off of
extern unsigned int direction;
extern unsigned int paddle_hit;
extern unsigned int rightwall;
extern unsigned int leftwall;
//Flags used determining which player scored, allowing other player to receive ball to be launched
extern unsigned int p1_scored;
extern unsigned int p2_scored;
//Flag which will be used to determine when game is started
extern unsigned int start_game;
//Flag for launching the ball
extern unsigned int launch_ball;
extern unsigned int long initial_ball_speed;//1 sec period for SysTick
extern unsigned int Truevalue;
extern unsigned int mode;
extern unsigned int long AI_delay;
extern unsigned int difficulty;
extern unsigned int pause;
extern unsigned int temp_pause;
extern unsigned int restart;
extern unsigned int difficulty_press;
extern unsigned int temp_restart;
extern unsigned int mode_press;
extern unsigned int right_sec_hex;
extern unsigned int left_sec_hex;
extern unsigned int end_game;
extern unsigned int professor_mode;
extern unsigned int professor_delay;
extern unsigned int win_delay;
extern unsigned long long  standby_delay;
extern unsigned int standby_mode;
extern unsigned int standby_game_start;
extern unsigned int P1_mode;
extern unsigned int P1_AI_delay;
extern int mode_select;
extern int AI_select;
extern int score_select;
extern int max_score;
extern int score_index;
extern int launch_temp;
extern unsigned int *player1_leftpress_ptr;
extern int one_press;
extern int select_press;
extern int score_press;
extern int scores[4];

extern void Delay(void);
extern void Delay2(void);
extern int random_int(int min, int max);//gets random number in range specified "ball"
#endif 
