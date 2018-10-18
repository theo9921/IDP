/*
*	@author: T.T. Ouzounellis Kavlakonis
*	Date: 18 October 2018
*	Project: Part 1B Engineering Tripos Integrated Design Project
*/

#include <robot_instr.h>
#include <robot_link.h>
#include <stopwatch.h>

robot_link rlink;
stopwatch testwatch;
stopwatch motorwatch;

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

#define TURNING_SPEED 60


//8-bit number with 3 LSB's being the sensors
int state;

void turnLeft()
{
	//turn left by moving forward a bit first
	motorwatch.start();
	cout << "Turning Left" << endl;
	while(true)
	{
		while(motorwatch.read()<=4650)
		{
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, DEFAULT_SPEED);
		}
		rlink.command(BOTH_MOTORS_GO_SAME, TURNING_SPEED);
		//read the output from the chip
		state = rlink.request(READ_PORT_5);
		if(state==LFSTATE_WBB) break;
	}
}

void turnRight()
{
	//turn left by moving forward a bit first
	motorwatch.start();
	cout << "Turning Right" << endl;
	while(true)
	{
		while(motorwatch.read()<=4650)
		{
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, DEFAULT_SPEED);
		}
		rlink.command(BOTH_MOTORS_GO_SAME, REVERSE_STHRES + TURNING_SPEED);
		//read the output from the chip
		state = rlink.request(READ_PORT_5);
		if(state==LFSTATE_BBW) break;
	}
}

void moveStraight()
{
	
}
