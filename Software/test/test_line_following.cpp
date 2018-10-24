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
int test_time = 600;

int nCrosses[4] = {1, 0, 1, 0};
int nTurn = 0;

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
		moveStraight(-1, false);
		//turn left and be sure to ignore 1 line crossing
		turnLeft(nCrosses[nTurn%4]);
		nTurn++;
	}
	return 0;
}



