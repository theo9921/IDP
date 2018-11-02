/*
*	@author: T.T. Ouzounellis Kavlakonis
*	Date: 21 October 2018
*	Project: Part 1B Engineering Tripos Integrated Design Project
*/

#include "../modules/line_following.h"
#include "../modules/mapping.h"
#include "../modules/handling.h"
#include <iostream>

using namespace std;

//duration of test in seconds
int test_time = 600;

//define primitive map
int nCrosses[4] = {1, 0, 1, 0};
int nTurn = 0;

//define a global stopwatch to keep track of the total time the robot is running
stopwatch globalWatch;

int main()
{
	#ifdef __arm__  //setup for local hardware
		if (!rlink.initialise()){} 
	#else //setup for use over wifif
		if (!rlink.initialise(ROBOT_NUM))
		{
			rlink.print_errs("	");
			return -1;	
		}
	#endif

	// adjust the platform hieght back to level
	rlink.command(MOTOR_3_GO, REVERSE_STHRES + PLATFORM_SPEED);
	sleep(10000);
	rlink.command(MOTOR_3_GO, 0);
	
	// retract the arm
	rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);
	sleep(1000);
	
	// lower the arm to its lowest
	stopwatch timer;
	timer.start();
	while(timer.read() <= 8000)
	{
		rlink.command(MOTOR_3_GO, PLATFORM_SPEED);
	}
	rlink.command(MOTOR_3_GO, 0);
	
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);
	moveStraight(-1, false);
	stopMovement();
	// deal with the first block
	moveBackSimple(500);
	scanCollect(0b11111111, 0);
	// pick up the following two
	scanCollect(0b11111111, 0);
	scanCollect(0b11111111, 0);

	
	// go to the first lorry and dump
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);
	
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);
	
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);
	
	// drop boxes
	drop();
	
	// go back to the start of C2
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnRightFull(0);
	
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);
	
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);
	
	// reset the platform level to the lowest
	rlink.command(MOTOR_3_GO, PLATFORM_SPEED);
	sleep(8000);
	rlink.command(MOTOR_3_GO, 0);
	
	// go to the third position and start the second round
	moveStraight(-1, false);
	moveStraight(-1, false);
	
	// collect the last two stacks
	scanCollect(0b11111111, 0);
	scanCollect(0b11111111, 0);
	
	
	// go to lorry 2 and dump
	moveStraight(-1, false);
	turnLeftFull(0);
	
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);
	
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);
	
	// drop boxes
	drop();
	
	// go back to start
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnRightFull(0);
	
	moveStraight(-1, false);
	moveStraight(-1, false);
	
	stopMovement();
	
	cout << "completed round" << endl;
	
	return 0;
	//INSERT STRATEGY AND OVERALL FUNCTION
}


