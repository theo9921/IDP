/*
*	@author: T.T. Ouzounellis Kavlakonis
*	Date: 24 October 2018
*	Project: Part 1B Engineering Tripos Integrated Design Project
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
	cout << rlink.request(ADC0) << endl;
	cout << rlink.request(ADC1) << endl;
	cout << rlink.request(ADC2) << endl;
	cout << rlink.request(ADC3) << endl;
	cout << rlink.request(ADC4) << endl;
}
