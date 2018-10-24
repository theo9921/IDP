/*
*	@author: T.T. Ouzounellis Kavlakonis
*	Date: 21 October 2018
*	Project: Part 1B Engineering Tripos Integrated Design Project
*/

#include "parameters.h"
#include "line_following.h"
#include <iostream>
using namespace std;

#define ACTUATORS_FULLEXT = 0b11000000 //value of actuator bit for full extension
#define ACTUATORS_HALFEXT = 0b01000000 //value of actuator bit for half extension
#define ACTUATORS_NOEXT = 0b00000000 //value of actuator bit for no extension

robot_link rlink;

//function to collect the box. I controls to actuators in series to move the arm in 3 different locations.
//Those are: fully extended retracted halfway and full retracted. 

void collect()
{
	rlink.command(WRITE_PORT_4, ACTUATORS_FULLEXT);
	sleep(1000);
	rlink.command(WRITE_PORT_4, ACTUATORS_HALFEXT);
	sleep(300);
	rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);
}
void cancelCollect(){} //basically not collect
void drop(){} 
void movePlatform(float distance){} //move platform up and down by a certain distance
int scan(){}  //return the block type