/* 
* Author T.T. Ouzounellis Kavlakonis
* Date: 02 November 2018
* Cambridge Engineering Tripos Part 1B IDP (2018-2019)
*/

#include <conio.h>
#include <iostream>
#include <bitset>
#include <cmath>
#include <vector>
#include <stdio.h>
using namespace std; 

//definitions to use on platform controller
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

//definitions for COLOUR Values
#define COLOR_WHITE 1
#define COLOR_RED 2
#define COLOR_TRANS 3
#define COLOR_WOOD 4
#define COLOR_GREEN 5

//number between 0 and 127 (128-255 for reverse)
#define DEFAULT_SPEED 80
//above that direction of motors will be reversed
#define REVERSE_STHRES 128


//return block colour
//White=1, Red=2 Transparent=3 Wooden=4 Green=5 --> IDK = 0
int getBlockColour()
{
	
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
	//Green 113, 15, 85
	if((percentageError(113, white-none)<=10) && (percentageError(15, red-none)<=40) && (percentageError(85, blue-none)<=50))
	{
		cout << "It is a Green Block" << endl;
		return COLOR_GREEN;
	}
	//Wood 153, 44, 136
	if((percentageError(153, white-none)<=10) && (percentageError(44, red-none)<=40) && (percentageError(136, blue-none)<=50))
	{
		cout << "It is a Wooden Block" << endl;
		return COLOR_WOOD;
	}

	//transparent 90, 5, 33 most unstable
	if((percentageError(90, white-none)<=10) && (percentageError(33, blue-none)<=50))
	{
		cout << "It is a Trasnsparent Block" << endl;
		return COLOR_TRANS;
	}
	//red 120, 28, 63
	if((percentageError(120, white-none)<=10) && (percentageError(28, red-none)<=40) && (percentageError(63, blue-none)<=50))
	{
		cout << "It is a Red Block" << endl;
		return COLOR_RED;
	}
	//white 128, 26, 125
	if((percentageError(128, white-none)<=10) && (percentageError(26, red-none)<=30) && (percentageError(125, blue-none)<=50))
	{
		cout << "It is a White Block" << endl;
		return COLOR_WHITE;
	}
	else
	{
		cout << "Don't know what colour" << endl;
		return 0;
	}
}
//function to remotely control platform
void controlPlatform()
{
	int c = 0;
    while(1)
    {
        c = 0;
	c = getch();
        if(c == KEY_UP) 
	{
		//move platform up
		//rlink.command(MOTOR_3_GO, REVERSE_STHRES + PLATFORM_SPEED);
		cout << "up" << endl;
	}
	else if(c == KEY_DOWN)
	{
		//move platform down
		//rlink.command(MOTOR_3_GO, PLATFORM_SPEED);
		cout << "down" << endl;
	}
	else if(c == KEY_ENTER)
	{
		break;	
	}
    }
}

//function to move Platform
//-1 --> down 0--> up
void movePlatform(int position)
{
	/*
	if(position == 0)
	{
		// adjust the platform height to level
		rlink.command(MOTOR_3_GO, REVERSE_STHRES + PLATFORM_SPEED);
		sleep(10000);
		rlink.command(MOTOR_3_GO, 0);
	}
	else if(position == 1)
	{
		// adjust the platform height to level
		rlink.command(MOTOR_3_GO, PLATFORM_SPEED);
		sleep(8000);
		rlink.command(MOTOR_3_GO, 0);
	}
	*/
}

bool scanCollect(int lorry) //return the block type
{
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
	
	//====ADDED===
	//read the current state of the indicator LED's and set LED based on the colour
	bitset<8> LEDstate (rlink.command(READ_PORT_4));
	LEDstate[colour-1] = 0;
	bitset<8> LEDstate (rlink.command(WRITE_PORT_4, LEDstate));
	sleep(1000);
	//====ADDED===
	
	//if we want to pick that block pick it up
	
	//FOR LORRY 1
	if(lorry == 1)
	{
		//If the brick is Red White or Transparent we can pick it up
		if((colour==COLOR_RED) || (colour==COLOR_WHITE) || (colour==COLOR_TRANS))
		{
			rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);
			cout << "collect" << endl;
			return 0;
		}
		//else do not pick it up
		else
		{
			moveBackSimple(moveStraightTime+50);
			rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);
			moveStraightLittleBitRight(moveStraightTime+50, true);
			cout << "do not collect" << endl;
			return 1;
		}
	}
	
	//FOR LORRY 2
	else if(lorry == 1)
	{
		//If it is Green Wood or Transparent pick it up
		if((colour==COLOR_GREEN) || (colour==COLOR_WOOD) || (colour==COLOR_TRANS))
		{
			rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);
			cout << "collect" << endl;
			return 0;
		}
		//else not pick it up
		else
		{
			moveBackSimple(moveStraightTime+50);
			rlink.command(WRITE_PORT_4, ACTUATORS_NOEXT);
			moveStraightLittleBitRight(moveStraightTime+50, true);
			cout << "do not collect" << endl;
			return 1;
		}
	}
}  

int main()
{
	//Initialize robot link
	#ifdef __arm__  //setup for local hardware
		if (!rlink.initialise()){} 
	#else //setup for use over wifif
		if (!rlink.initialise(ROBOT_NUM))
		{
			rlink.print_errs("	");
			return -1;	
		}
	#endif
	
	//Start by manually setting up the platform
	controlPlatform();
	//initialize arrays to hold non-collected blocks at C1 and C2
	int blocksC1 [5] = {1, 1, 1, 1, 1};
	int blocksC2 [5] = {1, 1, 1, 1, 1};
	
	//Initialize 2d array of 5 rows and 8 columns
	//All 1's represent real junctions and all 0's imaginary ones
	int mapArr[5][8] =
    	{
        {1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,1,1},
        {1,1,1,1,0,0,1,1},
        {1,1,1,1,0,0,1,1}
    	};
	
	//get into position along C2
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);
	
	//move to the first block and stop
	moveStraight(-1, false);
	stopMovement();
	
	// move back a little
	moveBackSimple(500);
	
	//start scanning all the boxes in C2
	blocksC2[0] = scanCollect(1);
	blocksC2[1] = scanCollect(1);
	blocksC2[2] = scanCollect(1);
	blocksC2[3] = scanCollect(1);
	blocksC2[4] = scanCollect(1);

	// go to the first lorry and dump
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);

	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);

	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);

	// drop boxes
	drop();

	// go back to the start of C2
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnRightFull(0);

	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);

	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);

	// reset the platform level to the lowest
	rlink.command(MOTOR_3_GO, PLATFORM_SPEED);
	sleep(8000);
	rlink.command(MOTOR_3_GO, 0);

	// go to the initial position and start the second round
	// collect the ramaining C2 boxes to dump on lorry 2
	int currentPos=0;
	for(int i=0; i<=4; i++)
	{
		if(blocksC2[i]==0)
		{
			//move to the first block and stop
			for(int moves=1; moves<=(i-currentPos+1)); moves++)
			{
				moveStraight(-1, false);
			}
			stopMovement();
			// move back a little
			moveBackSimple(500);
			blocksC2[i] = scanCollect(2);
		}
		
		currentPos=i;
	}
	//go past C2
	for(int j=0; j<=(4-currentPos); i++)
	{
		moveStraight(-1, false);
	}
	// go to lorry 2 and dump
	turnLeftFull(0);

	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);

	moveStraight(-1, false);
	moveStraight(-1, false);
	turnLeftFull(0);

	// drop boxes
	drop();

	// go back to start
	moveStraight(-1, false);
	moveStraight(-1, false);
	turnRightFull(0);

	moveStraight(-1, false);
	moveStraight(-1, false);

	stopMovement();

	cout << "completed round" << endl;

	return 0;
	//INSERT STRATEGY AND OVERALL FUNCTION
}
	
