/*
*	@author: T.T. Ouzounellis Kavlakonis
*	Date: 11 October 2018
*	Project: Part 1B Engineering Tripos Integrated Design Project
*/

#include <iostream>
using namespace std;
#include "../modules/parameters.h"
#include "../modules/line_following.h"

/*
	MOTOR_2 is right wheel 
	MOTOR_1 is left wheel (needs reverse to go forward)
*/



//duration of test in seconds
int test_time = 40;

//Define boolean variables (0/1) to hold the readings of the 3 line following sensors
bool sens1=0, sens2=0, sens3=0;


int main()
{
	if (!rlink.initialise(ROBOT_NUM))
	{
		rlink.print_errs("	");
		return -1;	
	}
	
	testwatch.start();
	while(testwatch.read()<=test_time*1000)
	{
		//read the output from the chip
		state = rlink.request(READ_PORT_5);
		if(state==LFSTATE_BWB)
		{
			//move forwards
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, DEFAULT_SPEED);
		}
		else if(state==LFSTATE_BBW || state==LFSTATE_BWW)
		{
			//turn a bit to the right
			//speed down the left wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES + DEFAULT_SPEED);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED*0.8);
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
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES+DEFAULT_SPEED*0.65);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED);
		}
		else if(state==LFSTATE_WWW)
		{
			//turnRight();
			//turnLeft();
			turnLeftTmp();
		}
		else
		{
			motorwatch.start();
			while(motorwatch.read()<= 1000 && state==LFSTATE_BBB)
			{
				rlink.command(BOTH_MOTORS_GO_OPPOSITE, REVERSE_STHRES + DEFAULT_SPEED);
			}
			
		}
		
		
	}
	return 0;
}



