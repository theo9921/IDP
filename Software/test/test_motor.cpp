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
	int val;
	if (!rlink.initialise(ROBOT_NUM))
	{
		cout << "Cannot initialize link" << endl;
		rlink.print_errs("	");
		return -1;	
	}
	//Spin the motor
	watch.start();
	while(watch.read() <= 3000)
	{
		rlink.command(BOTH_MOTORS_GO_SAME, 60);
		cout << "Spinning motor" << endl;
	}
	cout << "Stopped Spinning motor" << endl;
}
