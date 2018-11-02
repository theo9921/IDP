/*
@author: T.T. Ouzounellis Kavlakonis (tto21@cam.ac.uk)
Credits: CUED
Date: 08 October 2018
*/

//Time taken to go fully down/up : 9700

#include <iostream>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <stopwatch.h>
#include "../modules/parameters.h"

#define ROBOT_NUM 9
#define PLATFORM_SPEED 75
stopwatch watch;

int main()
{
	if (!rlink.initialise(ROBOT_NUM))
	{
		cout << "Cannot initialize link" << endl;
		rlink.print_errs("	");
		return -1;	
	}
	while(true)
	{
		int key;
		cin >> key
		if(key == 24) rlink.command(MOTOR_3_GO, PLATFORM_SPEED);
		else if(key == 25) rlink.command(MOTOR_3_GO, REVERSE_STHRES + PLATFORM_SPEED);
		else break;
	}
	while(true)
	{
		cout << "moving motor" << endl;
		watch.start();
		
		while(watch.read()<=9000)
		{
			rlink.command(MOTOR_3_GO, PLATFORM_SPEED);
		}
		rlink.command(MOTOR_3_GO, 0);
		watch.start();
		while(watch.read() <= 500){}
		watch.start();
		while(watch.read()<=9000)
		{
			rlink.command(MOTOR_3_GO, PLATFORM_SPEED);
		}
		rlink.command(MOTOR_3_GO, 0);
		
	}
	return -1;
}
