/*
*	@author: T.T. Ouzounellis Kavlakonis
*	Date: 11 October 2018
*	Project: Part 1B Engineering Tripos Integrated Design Project
*/

/*
 * This file is created to test the functionality of the block detection LED's and actuators.
 * To do that it cycles through all the possible combinations of ON/OFF state for each connected
 * actualtor/LED each represented by a bit.
 */

#include <iostream>
using namespace std;
#include "../modules/parameters.h"

robot_link rlink;
stopwatch timer;

int main()
{
	if (!rlink.initialise(ROBOT_NUM))
	{
		rlink.print_errs("	");
		return -1;	
	}
	
	//set the bit sequence to send
	const int const_bit = 0x20; //set to 00100000
	const int led_bits_ref = 0x1F; //set to 00011111
	int actuator_bits = 0x80; // set to 10000000
	int led_bits; //declare value to hold actual led_bit
	int send_bits; //declare value to hold the bit sequence to send
	
	for(int i=0;i<=1;i++)
	{
		int led_bitsR = 0x01; //set to 00000001
	
		for(int j=0;j<=4; j++)
		{
			led_bits = led_bitsR ^ led_bits_ref;
			send_bits = (led_bits ^ actuator_bits) ^ const_bit;
			led_bitsR = led_bitsR << 1;
			cout << "send_bits = " << bitset<8>(send_bits) << endl;
			rlink.command(WRITE_PORT_4, send_bits);
			timer.start();
			while(timer.read()<=500){}
		}
		actuator_bits = actuator_bits >> 1;
	}
}


