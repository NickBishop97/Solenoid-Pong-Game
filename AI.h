#ifndef _AI_H_
#define _AI_H_

#include "Common.h"

void ProfessorMode(void);//AI mode for player 1, can be turned on during game. Functions as regular AI during standby
void AI_Mode(void);//behavior of p2 paddle when AI mode is turned on
void AI_Behavior(int player_scored, int diff, Player *player);
#endif
