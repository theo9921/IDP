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

//duration of test in seconds
int test_time = 15;

//Define boolean variables (0/1) to hold the readings of the 3 line following sensors
bool sens1=0, sens2=0, sens3=0;

//states of the line following sensors for reference
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
#define LFSTATE_BBB 0
#define LFSTATE_BBW 1
#define LFSTATE_BWB 2
#define LFSTATE_BWW 3
#define LFSTATE_WBB 4
#define LFSTATE_WBW 5
#define LFSTATE_WWB 6
#define LFSTATE_WWW 7

//create a variable to hold the state of the system
int state;

int main()
{
	if (!rlink.initialise(ROBOT_NUM))
	{
		cout << "Cannot initialize link" << endl;
		rlink.print_errs("	");
		return -1;	
	}
	
	watch.start();
	while(testwatch.read()<=test_time*1000)
	{
		//read the 3 line following sensors and store the values
		sens1 = rlink.request(READ_PORT_0);
		sens2 = rlink.request(READ_PORT_1);
		sens3 = rlink.request(READ_PORT_2);
		
		//create a variable state to hold the three readings
		state = ((((sens1<<1)|sens2))<<1)|sens3;
		cout << state << endl;
		
		if(state==LFSTATE_BWB)
		{
			//move forwards
			rlink.command(BOTH_MOTORS_GO_OPPOSITE, 198);
		}
		else if(state==LFSTATE_BBW)
		{
			//turn a bit to the right
			rlink.command(BOTH_MOTORS_GO_SAME, 198);
		}
		else if(state==LFSTATE_WBB)
		{
			//turn a bit to the left
			rlink.command(BOTH_MOTORS_GO_SAME, 70);
		}
		else
		{
			cout << "I dont't know what to do. PANIC MODE ACTIVATED! " << endl;
		}
	}
	return 0;
}
