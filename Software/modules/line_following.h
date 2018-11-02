/*
*	@author: T.T. Ouzounellis Kavlakonis
*	Date: 18 October 2018
*	Project: Part 1B Engineering Tripos Integrated Design Project
*/

/*
 * This header file holds all the functions needed for line following. Those include two different
 * sets of turn left and turn right functions (one set rotates both wheels and the other keeps one
 * of them stationary and rotates the other one) and one move straight functions which includes
 * parameters for controlling (if wanted) the time to move forward and whether or not to ignore lines.
 * A demonstation of all those function is implemented in the test_line_following file in the "test" folder. 
 */


#include "parameters.h"
#include <iostream>

using namespace std;

stopwatch testwatch;
stopwatch motorwatch;

//states of the line following sensors for reference (first 3 bits of the output)
/*
	000=0 --> bbb
	001=1 --> bbw
	010=2 --> bwb
	011=3 --> bww
	100=4 --> wbb
	101=5 --> wbw
	110=6 --> wwb
	111=7 --> www
*/
#define LFSTATE_BBB 240 //11110000
#define LFSTATE_BBW 241 //11110001
#define LFSTATE_BWB 242 //11110010
#define LFSTATE_BWW 243 //11110011
#define LFSTATE_WBB 244 //11110100
#define LFSTATE_WBW 245 //11110101
#define LFSTATE_WWB 246 //11110110
#define LFSTATE_WWW 247 //11110111

//define the default motor turning speed
#define TURNING_SPEED 65
#define MOTOR_LEFT_GO MOTOR_2_GO
#define MOTOR_RIGHT_GO MOTOR_1_GO


void stopMovement()
{
	rlink.command(BOTH_MOTORS_GO_SAME, 0);
}

//function to 
int getBlockState(int state)
{
	//store IR bit
	return (state & 0b00001000) >> 3;
}

int getLineState(int state)
{
	//set 4th bit (BLOCK IR)to 0 to match the defined states
	return (state & 0b00000111) | 0b11110000;
}

//function to move the robot straight for a period of time or indefinetely (with or without ignoring corners)
void moveStraight(int timeLen, bool skipCornersWhileTurning )
{
	stopwatch tmpStopWatch; //stopwatch to move straight
	int cornerCounter = 0; //integer to hold the number of corners encountered
	tmpStopWatch.start(); //start the stopwatch
	int prevState = LFSTATE_BWB;
	
	while(tmpStopWatch.read()<=timeLen || timeLen == -1) //if we want to move indefinetely or for a fixed period of time
	{
		//read the output from the chip
		int state = rlink.request(READ_PORT_5);
		state = getLineState(state);
		cout << state << endl;
		
		// corner detection and reaction
		if(state!=LFSTATE_WWW && cornerCounter>2){
			// if cornerCounter is larger than 2, then a corner is actually detected
			cout << "meet a corner" << endl;
			if(!skipCornersWhileTurning) break;
		}
		else if(state!=LFSTATE_WWW && cornerCounter<=2){
			cornerCounter=0; // reset cornerCounter if WWW is a miss detection
		}
		
		// move straight feedback from line followers
		if(state==LFSTATE_BWB)
		{
			//move forwards
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, DEFAULT_SPEED);
		}
		else if(state==LFSTATE_BBW)
		{
			//turn a bit to the right
			//speed down the left wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES + DEFAULT_SPEED);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED*0.8);
		}
		else if(state==LFSTATE_BWW)
		{
			//turn a bit to the right
			//speed down the left wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES + DEFAULT_SPEED);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED*0.9);
			
		}
		else if(state==LFSTATE_WWB)
		{
			//turn a bit to the left
			//speed down right wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES+DEFAULT_SPEED*0.8);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED);
		}
		else if(state==LFSTATE_WBB)
		{
			//turn a bit to the left
			//speed down right wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES+DEFAULT_SPEED*0.6);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED);
		}
		else if(state==LFSTATE_WWW)
		{
			if(prevState==state){
				cornerCounter++;
			}
		}
		else
		{
			//go backwards until it reaches a known state
			cout << "panic" <<endl;
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, REVERSE_STHRES + DEFAULT_SPEED);
		}
	
		// store previous state
		prevState=state;
	}
}

void moveBackSimple(int timeLen){
	stopwatch tmpStopWatch; //stopwatch to move straight
	tmpStopWatch.start(); //start the stopwatch
	while(tmpStopWatch.read()<=timeLen){
		rlink.command(BOTH_MOTORS_GO_OPPOSITE, REVERSE_STHRES + DEFAULT_SPEED);	
	}
}

void moveBack(int timeLen){
	stopwatch tmpStopWatch; //stopwatch to move straight
	tmpStopWatch.start(); //start the stopwatch

	while(tmpStopWatch.read()<=timeLen || timeLen == -1) //if we want to move indefinetely or for a fixed period of time
	{
		//read the output from the chip
		int state = rlink.request(READ_PORT_5);
		
		// move straight feedback from line followers
		if(state==LFSTATE_BWB)
		{
			//move backwards
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, REVERSE_STHRES + DEFAULT_SPEED);
		}
		else if(state==LFSTATE_BBW)
		{
			//move back towards right a bit
			//speed down the left wheel
			rlink.command(MOTOR_LEFT_GO, DEFAULT_SPEED*0.6);
			rlink.command(MOTOR_RIGHT_GO, REVERSE_STHRES + DEFAULT_SPEED);
		}
		else if(state==LFSTATE_BWW)
		{
			//move back towards right a small bit
			//speed down the left wheel
			rlink.command(MOTOR_LEFT_GO, DEFAULT_SPEED*0.8);
			rlink.command(MOTOR_RIGHT_GO, REVERSE_STHRES + DEFAULT_SPEED);
			
		}
		else if(state==LFSTATE_WWB)
		{
			//turn a small bit to the left
			//speed down right wheel
			rlink.command(MOTOR_LEFT_GO, DEFAULT_SPEED);
			rlink.command(MOTOR_RIGHT_GO, REVERSE_STHRES+DEFAULT_SPEED*0.9);
		}
		else if(state==LFSTATE_WBB)
		{
			//turn a big bit to the left
			//speed down right wheel
			rlink.command(MOTOR_LEFT_GO, DEFAULT_SPEED*0.6);
			rlink.command(MOTOR_RIGHT_GO, REVERSE_STHRES+DEFAULT_SPEED*0.8);
		}
		else if(state==LFSTATE_BBB){
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, DEFAULT_SPEED);
		}
	
	}
}

void moveStraightLittleBitRight(int timeLen, bool skipBlock)
{
	stopwatch tmpStopWatch; //stopwatch to move straight
	tmpStopWatch.start(); //start the stopwatch
	int prevBlockBit = 0;
	
	while(tmpStopWatch.read()<=timeLen || timeLen == -1) //if we want to move indefinetely or for a fixed period of time
	{
		//read the output from the chip
		int state = rlink.request(READ_PORT_5);
		
		int blockBit = getBlockState(state);
		state = getLineState(state);
		
		// move straight feedback from line followers
		if(state==LFSTATE_WWB)
		{
			//move forwards
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, DEFAULT_SPEED);
		}
		else if(state==LFSTATE_BWW)
		{
			//turn a bit to the right
			//speed down the left wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES + DEFAULT_SPEED);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED*0.8);
		}
		else if(state==LFSTATE_BWB)
		{
			//turn a small bit to the right
			//speed down the left wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES + DEFAULT_SPEED);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED*0.9);
			
		}
		else if(state==LFSTATE_WBB)
		{
			//turn a small bit to the left
			//speed down right wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES+DEFAULT_SPEED*0.8);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED);
		}
		else if(state==LFSTATE_BBB)
		{
			//turn a bit to the left
			//speed down right wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES+DEFAULT_SPEED*0.6);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED);
		}
		
		if(blockBit == 0 && prevBlockBit == 1 && skipBlock == 0)
		{
			stopMovement();
			break;
		}
		// store previous state
		prevBlockBit = blockBit; 
	}
}

//turn left move the centre to the junction and make a rotation about the center
void turnLeftFull(int nCross)
{
	motorwatch.start();
	cout << "Turning Left" << endl;
	int prevState;
	int nWWB = 0;
	//move straight until robots centre is at the junction
	moveStraight(1150, true);
	
	//turn to the left while ignoring as many lines as necessary until it aligns with the line
	while(true)
	{
		rlink.command(MOTOR_LEFT_GO, TURNING_SPEED);
		rlink.command(MOTOR_RIGHT_GO, TURNING_SPEED*0.5);
		//read the output from the chip
		int state = rlink.request(READ_PORT_5);
		state = getLineState(state);
		if(state==LFSTATE_WBB && prevState != state)
		{
			nWWB++; 
		}
		if(nWWB > nCross) 
			break;
		prevState = state;
	}
}

//turn left move the centre to the junction and make a rotation about the center
void turnRightFull(int nCross)
{
	motorwatch.start();
	cout << "Turning Right" << endl;
	int prevState;
	int nBWW = 0;
	//move straight until robots centre is at the junction
	moveStraight(1150, true);
	
	//turn to the left while ignoring as many lines as necessary until it aligns with the line
	while(true)
	{
		rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES + TURNING_SPEED * 0.5);
		rlink.command(MOTOR_RIGHT_GO, REVERSE_STHRES + TURNING_SPEED);
		//read the output from the chip
		int state = rlink.request(READ_PORT_5);
		state = getLineState(state);
		if(state==LFSTATE_BWW && prevState != state)
		{
			nBWW++; 
		}
		if(nBWW > nCross) 
			break;
		prevState = state;
	}
}

//turn left by making a wider turn and by going half way pass the junction
void turnLeft(int nCross)
{
	motorwatch.start();
	cout << "Turning Left" << endl;
	int prevState;
	int nWWB = 0;
	
	//turn to the left while ignoring as many lines as necessary until it aligns with the line
	rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES + TURNING_SPEED*1/2);
	rlink.command(MOTOR_RIGHT_GO, TURNING_SPEED*3.1/2);
	while(true)
	{
		//read the output from the chip
		int state = rlink.request(READ_PORT_5);
		state = getLineState(state);
		if(state==LFSTATE_WWB && prevState != state)
		{
			nWWB++; 
		}
		if(nWWB > nCross) 
			break;
		prevState = state;
	}
}

//turn right by making a wider turn and by going half way pass the junction
void turnRight(int nCross)
{
	motorwatch.start();
	cout << "Turning Left" << endl;
	int prevState = LFSTATE_BWB;
	int nWWB = 0;
	//move straight until robots centre is at the junction
	moveStraight(1150, true);
	
	//turn to the right while ignoring as many lines as necessary until it aligns with the line
	while(true)
	{
		rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES + TURNING_SPEED);
		rlink.command(MOTOR_RIGHT_GO, 0);
		//read the output from the chip
		int state = rlink.request(READ_PORT_5);
		if(state==LFSTATE_WWB && prevState != state)
		{
			nWWB++; 
		}
		if(nWWB > nCross) 
			break;
		prevState = state;
	}
}

