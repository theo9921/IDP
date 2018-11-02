/*
*	@author: T.T. Ouzounellis Kavlakonis
*	Date: 11 October 2018
*	Project: Part 1B Engineering Tripos Integrated Design Project
*/

#include <iostream>
using namespace std;
#include "../modules/line_following.h"
#include "../modules/handling.h"

/*
	MOTOR_2 is right wheel 
	MOTOR_1 is left wheel (needs reverse to go forward)
*/



//duration of test in seconds
int test_time = 600;

int main()
{
	cout << "start testing" << endl;
	if (!rlink.initialise(ROBOT_NUM))
	{
		rlink.print_errs("	");
		return -1;	
	}
	
	//testwatch.start();
	
	//moveBack(10000);
	
	/*moveStraightLittleBitRight(-1);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);
	moveStraight(-1, false);
	turnLeftFull(0);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);*/
	
	while(true)
	{
		cout << "running" << endl;
		cout << getLineState(rlink.request(READ_PORT_5)) <<endl;
	}
	return 0;
}



