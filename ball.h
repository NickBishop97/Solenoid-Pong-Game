#ifndef _BALL_H_
#define _BALL_H_

extern void BallCoordinates(void);//makes note of current position of ball and assigns an x coordinate value
enum FSMSTATE  ballDirection(int hit, int num);//function for determining next state for ball
enum FSMSTATE{STARTING, MOVEUP, MOVEDOWN, MOVEDIAGLEFT, MOVEDIAGRIGHT, POINTMADE, ENDGAME};
//extern enum FSMSR State;
extern enum FSMSTATE State;
extern void changeSpeed(void);//changes speed of the ball


#endif
