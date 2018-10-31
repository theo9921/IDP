/*
*	@author: T.T. Ouzounellis Kavlakonis
*	Date: 21 October 2018
*	Project: Part 1B Engineering Tripos Integrated Design Project
*/

#include <iostream>
using namespace std;

#define ACTUATORS_FULLEXT  0b11000000 //value of actuator bit for full extension
#define ACTUATORS_HALFEXT  0b01000000 //value of actuator bit for half extension
#define ACTUATORS_NOEXT 0b00000000 //value of actuator bit for no extension

//function to collect the box. I controls to actuators in series to move the arm in 3 different locations.
//Those are: fully extended retracted halfway and full retracted. 

#define PLATFORM_SPEED 75

void movePlatform(float position) //move platform up and down by a certain distance
{
	float currentPosition = 0;
	if(position < currentPosition)
	{
		rlink.command(MOTOR_3_GO, PLATFORM_SPEED); //move down
		sleep(9000);
	}
	else if(position > currentPosition)
	{
		rlink.command(MOTOR_3_GO, REVERSE_STHRES + PLATFORM_SPEED); //move up
		sleep(9000);
	}
	else
	{
		cout << "Robot is already at the desired position" << endl; 
	}
} 

void collect()
{
	rlink.command(WRITE_PORT_4, ACTUATORS_FULLEXT);
	sleep(1000);
	rlink.command(WRITE_PORT_4, ACTUATORS_HALFEXT);
	sleep(300);
	rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);
}
void cancelCollect(){} //basically not collect
void drop()
{
	rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);
	sleep(50);
	rlink.command(WRITE_PORT_4, ACTUATORS_HALFEXT);
	sleep(50);
	rlink.command(WRITE_PORT_4, ACTUATORS_FULLEXT);	
	sleep(1000);
	rlink.command(WRITE_PORT_4, ACTUATORS_HALFEXT);
	sleep(50);
	rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);	
} 

//int scan(){}  //return the block type
