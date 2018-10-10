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
	//Spin the motor
	watch.start();
	while(watch.read() <= 1500)
	{
		rlink.command(BOTH_MOTORS_GO_SAME, 70);
		cout << "Turning left" << endl;
	}
	//restart watch
	watch.start();
	while(watch.read() <= 1000)
	{
		rlink.command(BOTH_MOTORS_GO_OPPOSITE, 198);
		cout << "Going forwards" << endl;
	}
	cout << "Going back to initial position" << endl;
	watch.start();
	while(watch.read() <= 1500)
	{
		rlink.command(BOTH_MOTORS_GO_OPPOSITE, 70);
		cout << "Going backwards" << endl;
	}
	//restart watch
	watch.start();
	while(watch.read() <= 1000)
	{
		rlink.command(BOTH_MOTORS_GO_SAME, 198);
		cout << "Turning right" << endl;
	}
	cout << "Stopped Spinning motors" << endl;
	return -1;
}
