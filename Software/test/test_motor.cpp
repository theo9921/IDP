/*
@author: T.T. Ouzounellis Kavlakonis (tto21@cam.ac.uk)
Credits: CUED
Date: 08 October 2018
*/

#include <iostream>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <stopwatch.h>

#define ROBOT_NUM 9
robot_link rlink;
stopwatch watch;

int main()
{
	if (!rlink.initialise(ROBOT_NUM))
	{
		cout << "Cannot initialize link" << endl;
		rlink.print_errs("	");
		return -1;	
	}
	//Turn to the left
	watch.start();
	cout << "Turning left" << endl;
	while(watch.read() <= 1500)
	{
		rlink.command(BOTH_MOTORS_GO_SAME, 70);
	}

	//Go forwards
	watch.start();
	cout << "Going forwards" << endl;
	while(watch.read() <= 1000)
	{
		rlink.command(BOTH_MOTORS_GO_OPPOSITE, 198);
	}
	cout << "Going back to initial position" << endl;

	//go backward
	watch.start();
	cout << "Going backwards" << endl;
	while(watch.read() <= 1500)
	{
		rlink.command(BOTH_MOTORS_GO_OPPOSITE, 70);
	}

	//Turn to the right
	watch.start();
	cout << "Turning right" << endl;
	while(watch.read() <= 1000)
	{
		rlink.command(BOTH_MOTORS_GO_SAME, 198);
	}
	cout << "Stopped Spinning motors" << endl;
	return -1;
}
