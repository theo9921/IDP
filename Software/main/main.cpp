/*
*	@author: T.T. Ouzounellis Kavlakonis
*	Date: 21 October 2018
*	Project: Part 1B Engineering Tripos Integrated Design Project
*/

#include "../modules/parameters.h"
#include "../modules/line_following.h"
#include "../module/handling.h"
#include "../modules/mapping.h"
#include <iostream>

using namespace std;

//initialize robot link
robot_link rlink;

//duration of test in seconds
int test_time = 600;

//define primitive map
int nCrosses[4] = {1, 0, 1, 0};
int nTurn = 0;

//define a global stopwatch to keep track of the total time the robot is running
stopwatch globalWatch;

int main()
{
	if (!rlink.initialise(ROBOT_NUM))
	{
		rlink.print_errs("	");
		return -1;	
	}
	
	
}


