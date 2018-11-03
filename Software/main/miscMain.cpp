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
		return 5;
	}
	//Wood 153, 44, 136
	if((percentageError(153, white-none)<=10) && (percentageError(44, red-none)<=40) && (percentageError(136, blue-none)<=50))
	{
		cout << "It is a Wooden Block" << endl;
		return 4;
	}

	//transparent 90, 5, 33 most unstable
	if((percentageError(90, white-none)<=10) && (percentageError(33, blue-none)<=50))
	{
		cout << "It is a Trasnsparent Block" << endl;
		return 3;
	}
	//red 120, 28, 63
	if((percentageError(120, white-none)<=10) && (percentageError(28, red-none)<=40) && (percentageError(63, blue-none)<=50))
	{
		cout << "It is a Red Block" << endl;
		return 2;
	}
	//white 128, 26, 125
	if((percentageError(128, white-none)<=10) && (percentageError(26, red-none)<=30) && (percentageError(125, blue-none)<=50))
	{
		cout << "It is a White Block" << endl;
		return 1;
	}
	else
	{
		cout << "Don't know what colour" << endl;
		return 0;
	}*/
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

void scanCollect(int collectColour, int timeLen) //return the block type
{
	/*
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
	
	//====ADDED===
	//read the current state of the indicator LED's and set LED based on the colour
	bitset<8> LEDstate (rlink.command(READ_PORT_4));
	LEDstate[colour-1] = 0;
	bitset<8> LEDstate (rlink.command(WRITE_PORT_4, LEDstate));
	sleep(1000);
	//====ADDED===
	
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
	*/
}  

int main()
{
	/*
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
	
	*/
	//Start by manually setting up the platform
	
	//controlPlatform();
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
    
    //set the bit sequence to send
	const int const_bit = 0x20; //set to 00100000
	const int led_bits_ref = 0x1F; //set to 00011111
	int actuator_bits = 0x80; // set to 10000000
	int led_bits; //declare value to hold actual led_bit
	int send_bits; //declare value to hold the bit sequence to send
	
	send_bits = ((led_bits ^ led_bits_ref) ^ actuator_bits) ^ const_bit;
	
	bitset<8> state (37);
	cout << state <<endl;
	state[8]=1;
	cout << state <<endl;
	
	
}
