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


#include <parameters.h>
#include <iostream>

using namespace std;

robot_link rlink;
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
#define TURNING_SPEED 60
#define MOTOR_LEFT_GO MOTOR_2_GO
#define MOTOR_RIGHT_GO MOTOR_1_GO


//8-bit number with 3 LSB's being the sensors
int state;

//function to move the robot straight for a period of time or indefinetely (with or without ignoring corners)
void moveStraight(int timeLen, bool skipCorners)
{
	stopwatch tmpStopWatch; //stopwatch to move straight
	int cornerCounter = 0; //integer to hold the number of corners encountered
	tmpStopWatch.start(); //start the stopwatch
	while(tmpStopWatch.read()<=timeLen|| timeLen == -1) //if we want to move indefinetely or for a fixed period of time
	{
		//read the output from the chip
		state = rlink.request(READ_PORT_5);
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
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED*0.6);
		}
		else if(state==LFSTATE_BWW)
		{
			//turn a bit to the right
			//speed down the left wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES + DEFAULT_SPEED);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED*0.75);
			
		}
		else if(state==LFSTATE_WWB)
		{
			//turn a bit to the left
			//speed down right wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES+DEFAULT_SPEED*0.75);
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
			if(!skipCorners) break;
			cornerCounter++;
		}
		else
		{
			//go backwards until it reaches a known state
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, REVERSE_STHRES + DEFAULT_SPEED);
		}
	}
}

//turn left by making a wider turn and by going half way pass the junction
void turnLeft(int nCross)
{
	motorwatch.start();
	cout << "Turning Left" << endl;
	int prevState;
	int nWWB = 0;
	//move straight until robots centre is at the junction
	moveStraight(2300, true);
	
	//turn to the left while ignoring as many lines as necessary until it aligns with the line
	while(true)
	{
		rlink.command(MOTOR_LEFT_GO, 0);
		rlink.command(MOTOR_RIGHT_GO, TURNING_SPEED);
		//read the output from the chip
		state = rlink.request(READ_PORT_5);
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
	int prevState;
	int nWWB = 0;
	//move straight until robots centre is at the junction
	moveStraight(2300, true);
	
	//turn to the right while ignoring as many lines as necessary until it aligns with the line
	while(true)
	{
		rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES + TURNING_SPEED);
		rlink.command(MOTOR_RIGHT_GO, 0);
		//read the output from the chip
		state = rlink.request(READ_PORT_5);
		if(state==LFSTATE_WWB && prevState != state)
		{
			nWWB++; 
		}
		if(nWWB > nCross) 
			break;
		prevState = state;
	}
}

//Turning left by aligning wheels with the junction and rotating
void turnLeftBackup()
{
	//turn left by moving forward a bit first
	motorwatch.start();
	cout << "Turning Left" << endl;
	while(true)
	{
		//go forwards until wheels align with junction
		while(motorwatch.read()<=4650)
		{
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, DEFAULT_SPEED);
		}
		//rotate until the sensors read the BWB state (i.e aligned with line)
		rlink.command(BOTH_MOTORS_GO_SAME, TURNING_SPEED);
		//read the output from the chip
		state = rlink.request(READ_PORT_5);
		if(state==LFSTATE_WBB) break;
	}
}

//Turning right by aligning wheels with the junction and rotating
void turnRighBackup()
{
	//turn right by moving forward a bit first
	motorwatch.start();
	cout << "Turning Right" << endl;
	while(true)
	{
		while(motorwatch.read()<=4650)
		{
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, DEFAULT_SPEED);
		}
		rlink.command(BOTH_MOTORS_GO_SAME, REVERSE_STHRES + TURNING_SPEED);
		//read the output from the chip
		state = rlink.request(READ_PORT_5);
		if(state==LFSTATE_BBW) break;
	}
}

