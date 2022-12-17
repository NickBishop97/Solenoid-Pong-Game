#include "Gamesettings.h"
#include "Common.h"
#include "SSD.h"

void ScoreSetting(void) {
	if(((p1_button_data & SW3) == 0)&&(select_press == 0)){
			score_select = 1;
			select_press = 1;
		}
		else if((player1.rightpress)&&(one_press == 0)) {
			score_index = (score_index + 1) % 4;
			max_score = scores[score_index];
			one_press = 1;
		}
		else if(player1.rightpress == 0){
			one_press = 0;
		}
		if((p1_button_data & SW3) != 0){
			select_press = 0;
		}
}
void GameSettings(void) {
	if((mode_select == 0 || AI_select == 0 || score_select == 0) && standby_mode == 0) {
		if(mode == P2_MODE && mode_select == 0) {
			updateScore(2, P);
		
			if(((p1_button_data & SW3) == 0)&&(select_press == 0)){
				mode_select = 1;
				AI_select = 1;
				select_press = 1;
			}
			else if((player1.rightpress)&&(one_press == 0)) {
				mode = (mode+1)%2;
				one_press = 1;
			}
			else if(player1.rightpress == 0){
				one_press = 0;
			}
			if((p1_button_data & SW3) != 0){
				select_press = 0;
			}
		}
		else if(mode == P1_MODE && mode_select == 0) {
			updateScore(1, P);
		
			if(((p1_button_data & SW3) == 0)&&(select_press == 0)){
				mode_select = 1;
				select_press = 1;
			}
			else if((player1.rightpress)&&(one_press == 0)) {
				mode = (mode+1) %2;
				one_press = 1;
			}
			else if(player1.rightpress == 0){
				one_press = 0;
			}
			if((p1_button_data & SW3) != 0){
				select_press = 0;
			}
		}
		else if(mode == P1_MODE && mode_select == 1 && AI_select == 0) {
			if(difficulty == EASY) {
				updateScore(d, 1);
				if(((p1_button_data & SW3) == 0)&&(select_press == 0)){
					AI_select = 1;
					select_press = 1;
				}
				else if((player1.rightpress)&&(one_press == 0)) {
					difficulty = (difficulty +1) %3;
					one_press = 1;
				}
				else if(player1.rightpress == 0){
					one_press = 0;
				}
				if((p1_button_data & SW3) != 0){
					select_press = 0;
			}
			}
			else if(difficulty == INTERMEDIATE) {
				updateScore(d, 2);
				if(((p1_button_data & SW3) == 0)&&(select_press == 0)){
					AI_select = 1;
					select_press = 1;
				}
				else if((player1.rightpress)&&(one_press == 0)) {
					difficulty = (difficulty +1) %3;
					one_press = 1;
				}
				else if(player1.rightpress == 0){
					one_press = 0;
				}
				if((p1_button_data & SW3) != 0){
					select_press = 0;
				}
				
			}
			else if(difficulty == HARD) {
				updateScore(d, 3);
				if(((p1_button_data & SW3) == 0)&&(select_press == 0)){
					AI_select = 1;
					select_press = 1;
				}
				else if((player1.rightpress)&&(one_press == 0)) {
					difficulty = (difficulty +1) %3;
					one_press = 1;
				}
				else if(player1.rightpress == 0){
					one_press = 0;
				}
				if((p1_button_data & SW3) != 0){
					select_press = 0;
				}
			}
		}
		else if(score_select == 0) {
			if(max_score == 3) {
				updateScore(P, 3);
				ScoreSetting();
			}
			else if(max_score == 5) {
				updateScore(P, 5);
				ScoreSetting();
			}
			else if(max_score == 7) {
				updateScore(P, 7);
				ScoreSetting();
			}
			else if(max_score == 9) {
				updateScore(P, 9);
				ScoreSetting();
			}
		}
	}
	else if(mode_select == 1 && AI_select == 1 && score_select == 1) {
		start_game = 1;
		one_press = 0;
		select_press = 0;
		score_press = 0;
	}

}
