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
stopwatch testwatch;
stopwatch motorwatch;

/*
	MOTOR_2 is right wheel 
	MOTOR_1 is left wheel (needs reverse to go forward)
*/

#define MOTOR_LEFT_GO MOTOR_2_GO
#define MOTOR_RIGHT_GO MOTOR_1_GO

//states of the line following sensors for reference (first 3 bits of the output)
/*
	000=0 --> bbb
	001=1 --> bbw
	010=2 --> bwb
	011=3 --> bww
	100=4 --> wbb
	101=5 --> wbw
	110=6 --> wwb
	111=7 --> www
*/
#define LFSTATE_BBB 240 //11110000
#define LFSTATE_BBW 241 //11110001
#define LFSTATE_BWB 242 //11110010
#define LFSTATE_BWW 243 //11110011
#define LFSTATE_WBB 244 //11110100
#define LFSTATE_WBW 245 //11110101
#define LFSTATE_WWB 246 //11110110
#define LFSTATE_WWW 247 //11110111

//number between 0 and 127 (128-255 for reverse)
#define DEFAULT_SPEED 40
//above that direction of motors will be reversed
#define REVERSE_STHRES 128

//duration of test in seconds
int test_time = 40;

//Define boolean variables (0/1) to hold the readings of the 3 line following sensors
bool sens1=0, sens2=0, sens3=0;

//8-bit number with 3 LSB's being the sensors
int state;

void turnLeftTT()
{
	//turn left by moving forward a bit first
	motorwatch.start();
	cout << "Turning" << endl;
	while(true)
	{
		while(motorwatch.read()<=4650)
		{
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, DEFAULT_SPEED);
		}
		rlink.command(BOTH_MOTORS_GO_SAME, 60);
		//read the output from the chip
		state = rlink.request(READ_PORT_5);
		if(state==LFSTATE_WBB) break;
	}
}

void turnLeftXD()
{
	// turn left by calibrating the turning process real time
	cout << "Turning" << endl;
	float leftSpeed = REVERSE_STHRES+DEFAULT_SPEED*0.5;
	float rightSpeed = DEFAULT_SPEED;
	while(true){
		if(state==LFSTATE_WWW){ // it is in the initial state of the turning
			rlink.command(MOTOR_LEFT_GO, leftSpeed);
			rlink.command(MOTOR_RIGHT_GO, rightSpeed);
		}
		else if(state==LFSTATE_BWW){ // turn slightly slower
			leftSpeed += DEFAULT_SPEED*0.025;
			rlink.command(MOTOR_LEFT_GO, leftSpeed);
			rlink.command(MOTOR_RIGHT_GO, rightSpeed);
		}
		else if(state==LFSTATE_BBW){ // turn much slower
			leftSpeed += DEFAULT_SPEED*0.05;
			rlink.command(MOTOR_LEFT_GO, leftSpeed+DEFAULT_SPEED*0.1);
			rlink.command(MOTOR_RIGHT_GO, rightSpeed);
		}
		else if(state==LFSTATE_WWB){ // turn harder
			leftSpeed -= DEFAULT_SPEED*0.025;
			rlink.command(MOTOR_LEFT_GO, leftSpeed-DEFAULT_SPEED*0.1);
			rlink.command(MOTOR_RIGHT_GO, rightSpeed);
		}
		else if(state==LFSTATE_WBB){ // turn super hard
			leftSpeed -= DEFAULT_SPEED*0.05;
			rlink.command(MOTOR_LEFT_GO, leftSpeed-DEFAULT_SPEED*0.2);
			rlink.command(MOTOR_RIGHT_GO, rightSpeed);
		}
		else if(state==LFSTATE_BWB || leftSpeed >= REVERSE_STHRES+DEFAULT_SPEED*0.5){
			// then the turning is over
			break;
		}
	}
}

int main()
{
	if (!rlink.initialise(ROBOT_NUM))
	{
		rlink.print_errs("	");
		return -1;	
	}
	
	testwatch.start();
	while(testwatch.read()<=test_time*1000)
	{
		//read the output from the chip
		state = rlink.request(READ_PORT_5);
		if(state==LFSTATE_BWB)
		{
			//move forwards
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, DEFAULT_SPEED);
		}
		else if(state==LFSTATE_BBW || state==LFSTATE_BWW)
		{
			//turn a bit to the right
			//speed down the left wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES + DEFAULT_SPEED);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED*0.8);
		}
		else if(state==LFSTATE_WWB)
		{
			//turn a bit to the left
			//speed down right wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES+DEFAULT_SPEED*0.8);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED);
		}
		else if(state==LFSTATE_WBB)
		{
			//turn a bit to the left
			//speed down right wheel
			rlink.command(MOTOR_LEFT_GO, REVERSE_STHRES+DEFAULT_SPEED*0.65);
			rlink.command(MOTOR_RIGHT_GO, DEFAULT_SPEED);
		}
		else if(state==LFSTATE_WWW)
		{
			turnLeftTT()
		}
		else
		{
			motorwatch.start();
			while(motorwatch.read()<= 1000 && state==LFSTATE_BBB)
			{
				rlink.command(BOTH_MOTORS_GO_OPPOSITE, REVERSE_STHRES + DEFAULT_SPEED);
			}
			
		}
		
		
	}
	return 0;
}



