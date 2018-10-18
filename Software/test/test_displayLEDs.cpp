/*
*	@author: T.T. Ouzounellis Kavlakonis
*	Date: 11 October 2018
*	Project: Part 1B Engineering Tripos Integrated Design Project
*/

#include <iostream>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <stopwatch.h>

#define ROBOT_NUM 9
robot_link rlink;
stopwatch timer;

int main()
{
	if (!rlink.initialise(ROBOT_NUM))
	{
		rlink.print_errs("	");
		return -1;	
	}
	rlink.command(WRITE_PORT_5, 0b11100000);
}
