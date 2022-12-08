#include "Paddles.h"
#include "Common.h"

/*
Function for updating the current positions of the player paddles
*/
void updatePaddle(void) {
		//player 1 paddle hasnt reached the left wall, player pressed left move button, and this is first occurrence
		//of the left button being pressed since previous read. Allows paddle to immediately move left
		if((((value1 )&0x8000)==0)&&(player1_leftpress == 1) && (p1_leftone == 0)) {
			playerOne_CurrentPosition <<= 1;																					
			playerOne_MiddlePad <<= 1;
			p1_leftone = 1;
		}
		//if player 1 is still holding down the move left button after first occurrence
		//increments a counter, otherwise reset counter to 0
		if(player1_leftpress == 1 && p1_leftone == 1) {
			p1_leftbutton_count += 1;
		}
		else {
			p1_leftbutton_count =0;
		}
		//player 1 paddle hasnt reached the left wall, player pressed left move button, and counter has reached 
		//desired value, paddle moves left. Creates delay between paddle movement if button is constantly
		//held
		if((((value1 )&0x8000)==0)&&(player1_leftpress == 1) && (p1_leftbutton_count == button_delay)) { //move left
			playerOne_CurrentPosition <<= 1;
			playerOne_MiddlePad <<= 1;
			p1_leftbutton_count = 0;
		}
		else if(p1_leftbutton_count == button_delay){
			p1_leftbutton_count =0;
		}
		//player 1 paddle hasnt reached the right wall, player pressed right move button, and this is first occurrence
		//of the right button being pressed since previous read. Allows paddle to immediately move right
		if((((value1 )&0x0100)==0)&&(player1_rightpress == 1) && (p1_rightone == 0)) {
			playerOne_CurrentPosition >>= 1;
			playerOne_MiddlePad >>= 1;
			p1_rightone = 1;
		}
		//if player 1 is still holding down the move right button after first occurrence
		//increments a counter, otherwise reset counter to 0
		if(player1_rightpress == 1 && p1_rightone == 1) {
			p1_rightbutton_count += 1;
		}
		else {
			p1_rightbutton_count =0;
		}
		//player 1 paddle hasnt reached the right wall, player pressed right move button, and counter has reached 
		//desired value, paddle moves right. Creates delay between paddle movement if button is constantly
		//held
		if((((value1 )&0x0100)==0)&&(player1_rightpress == 1) && (p1_rightbutton_count == button_delay)) { //move left
			playerOne_CurrentPosition >>= 1;
			playerOne_MiddlePad >>= 1;
			p1_rightbutton_count = 0;
		}
		else if(p1_rightbutton_count == button_delay){
			p1_rightbutton_count =0;
		}
		//if(mode == 1) {
		//player 2 paddle hasnt reached the left wall, player pressed left move button, and this is first occurrence
		//of the left button being pressed since previous read. Allows paddle to immediately move left
			if((((value4 )&0x0080)==0)&&(player2_leftpress == 1) && (p2_leftone == 0)) {
				playerTwo_CurrentPosition <<= 1;
				playerTwo_MiddlePad <<= 1;
				p2_leftone = 1;
				
			}
			//if player 2 is still holding down the move left button after first occurrence
			//increments a counter, otherwise reset counter to 0
			if(player2_leftpress == 1 && p2_leftone == 1) {
				p2_leftbutton_count += 1;
			}
			else {
				p2_leftbutton_count =0;
			}
			//player 2 paddle hasnt reached the left wall, player pressed left move button, and counter has reached 
			//desired value, paddle moves left. Creates delay between paddle movement if button is constantly
			//held
			if((((value4 )&0x0080)==0)&&(player2_leftpress == 1) && (p2_leftbutton_count == button_delay)) { //move left
				playerTwo_CurrentPosition <<= 1;
				playerTwo_MiddlePad <<= 1;
				p2_leftbutton_count = 0;
			}
			else if(p2_leftbutton_count == button_delay){
				p2_leftbutton_count =0;
			}
			//player 2 paddle hasnt reached the right wall, player pressed right move button, and this is first occurrence
			//of the right button being pressed since previous read. Allows paddle to immediately move right
			if((((value4 )&0x0001)==0)&&(player2_rightpress == 1) && (p2_rightone == 0)) {
				playerTwo_CurrentPosition >>= 1;
				playerTwo_MiddlePad >>= 1;
				p2_rightone = 1;
				
			}
			//if player 2 is still holding down the move right button after first occurrence
			//increments a counter, otherwise reset counter to 0
			if(player2_rightpress == 1 && p2_rightone == 1) {
				p2_rightbutton_count += 1;
			}
			else {
				p2_rightbutton_count =0;
			}
			//player 2 paddle hasnt reached the right wall, player pressed right move button, and counter has reached 
			//desired value, paddle moves right. Creates delay between paddle movement if button is constantly
			//held
			if((((value4 )&0x0001)==0)&&(player2_rightpress == 1) && (p2_rightbutton_count == button_delay)) { //move left
				playerTwo_CurrentPosition >>= 1;
				playerTwo_MiddlePad >>= 1;
				p2_rightbutton_count = 0;
			}
			else if(p2_rightbutton_count == button_delay){
				p2_rightbutton_count =0;
			}
		//}
	}


unsigned int PaddleCoordinates(unsigned long long MiddlePad) {
	unsigned int paddle_x;
	switch(MiddlePad) {
		case 0x02:
			paddle_x = 2;
			break;
		case 0x04:
			paddle_x = 3;
			break;
		case 0x08:
			paddle_x = 4;
			break;
		case 0x10:
			paddle_x = 5;
			break;
		case 0x20:
			paddle_x = 6;
			break;
		case 0x40:
			paddle_x = 7;
			break;
	}
	return paddle_x;
}
