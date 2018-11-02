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

void sleep(float milliseconds)
{
	stopwatch timer;
	timer.start();
	while(timer.read() <= milliseconds);
}

void movePlatform(float position) //move platform up and down by a certain distance
{
	float currentPosition = 0;
	if(position < currentPosition)
	{
		rlink.command(MOTOR_3_GO, PLATFORM_SPEED); //move down
	}
	else if(position > currentPosition)
	{
		rlink.command(MOTOR_3_GO, PLATFORM_SPEED); //move up
	}
	else
	{
		cout << "Robot is already at the desired position" << endl; 
	}
} 

void collect()
{/*
	moveStraightLittleBitRight(2500);
	rlink.command(WRITE_PORT_4, ACTUATORS_HALFEXT);
	sleep(300);
	rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);
	*/
}
//void cancelCollect(){} //basically not collect


void drop()
{
	moveStraight(-1, false);
	stopMovement();
	
	moveBackSimple(500);
	moveStraightLittleBitRight(1000, true);
	stopMovement();
	
	// lift up the platform
	stopwatch timer;
	timer.start();
	while(timer.read() <= 15000)
	{
		rlink.command(MOTOR_3_GO, REVERSE_STHRES + PLATFORM_SPEED);
	}
	
	// extend the arm
	rlink.command(WRITE_PORT_4, ACTUATORS_HALFEXT);
	sleep(500);
	rlink.command(WRITE_PORT_4, ACTUATORS_FULLEXT);	
	sleep(1000);
	
	// move back and retract the arm
	moveBackSimple(1500);
	stopMovement();
	rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);	
	sleep(1000);
}

int getBlockColour()
{
	int none, white, blue, red, LEN=100;
	
	// read none light
	rlink.command(WRITE_PORT_5, 0b11111111);
	none = 0;
	for(int i=0; i<LEN; i++){
		none += rlink.request(ADC2);
	}
	none /= LEN;
	
	// read white light
	rlink.command(WRITE_PORT_5, 0b11101111);
	white = 0;
	for(int i=0; i<LEN; i++){
		white += rlink.request(ADC2);
	}
	white /= LEN;
	
	// read blue light
	rlink.command(WRITE_PORT_5, 0b11011111);
	blue = 0;
	for(int i=0; i<LEN; i++){
		blue += rlink.request(ADC2);
	}
	blue /= LEN;
	
	// read red light
	rlink.command(WRITE_PORT_5, 0b10111111);
	red = 0;
	for(int i=0; i<LEN; i++){
		red += rlink.request(ADC2);
	}
	red /= LEN;
	
	// output normalized
	cout << "w: " << white-none << " r: " << red-none << " b: " << blue-none << endl;
	return 1;
}

void scanCollect(int collectColour, int timeLen) //return the block type
{
	moveStraightLittleBitRight(timeLen,true);
	// stop all movement
	stopMovement();

	// extend the arm
	rlink.command(WRITE_PORT_4, ACTUATORS_FULLEXT);
	sleep(1000);
	
	// move forward until we meet the block, record the time as well
	stopwatch tmpStopWatch; //stopwatch to move straight
	tmpStopWatch.start(); //start the stopwatch
	moveStraightLittleBitRight(-1, false);
	int moveStraightTime = tmpStopWatch.read();
	
	// read color
	int colour = getBlockColour();
	
	// whether to pick up the block or move back and retract arm
	if((collectColour & colour) != 0){
		rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);
		cout << "collect" << endl;
	}else{ // move back and retract the arm
		moveBackSimple(moveStraightTime+50);
		rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);
		moveStraightLittleBitRight(moveStraightTime+50, true);
		cout << "do not collect" << endl;
	}
}  





