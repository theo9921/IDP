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
	#else //setup for use over wifi
		if (!rlink.initialise(ROBOT_NUM))
		{
			rlink.print_errs("	");
			return -1;	
		}
	#endif
	rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);
	moveStraight(-1, false);
	moveStraightLittleBitRight(1800);
	rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);
	rlink.command(WRITE_PORT_4, ACTUATORS_FULLEXT);
	moveStraightLittleBitRight(1500);
	collect();
	stopMovement();
	stopwatch watch;
	watch.start();
	/*while(watch.read()<=3000)
	{
		rlink.command(MOTOR_3_GO, PLATFORM_SPEED);
	}*/
	sleep(1000);
	rlink.command(WRITE_PORT_4, ACTUATORS_FULLEXT);
	moveStraightLittleBitRight(2500);
	collect();
	stopMovement();
	watch.start();
	cout << "moving platform up" << endl;
	while(watch.read()<=10000)
	{
		rlink.command(MOTOR_3_GO, REVERSE_STHRES + PLATFORM_SPEED);
	}
	rlink.command(MOTOR_3_GO, 0);
	rlink.command(WRITE_PORT_4, ACTUATORS_FULLEXT);
	
	
	//INSERT STRATEGY AND OVERALL FUNCTION
}


