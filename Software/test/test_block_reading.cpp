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
#define LEN 100

int main()
{
	if (!rlink.initialise(ROBOT_NUM))
	{
		rlink.print_errs("	");
		return -1;	
	}
	timer.start();
	
	/*
	int none, white, blue, red;
	
	rlink.command(WRITE_PORT_5, 0b11111111);
	none = 0;
	for(int i=0; i<LEN; i++){
		none += rlink.request(ADC2);
	}
	none /= LEN;
	
	rlink.command(WRITE_PORT_5, 0b11101111);
	white = 0;
	for(int i=0; i<LEN; i++){
		white += rlink.request(ADC2);
	}
	white /= LEN;
	
	rlink.command(WRITE_PORT_5, 0b11011111);
	blue = 0;
	for(int i=0; i<LEN; i++){
		blue += rlink.request(ADC2);
	}
	blue /= LEN;
	
	rlink.command(WRITE_PORT_5, 0b10111111);
	red = 0;
	for(int i=0; i<LEN; i++){
		red += rlink.request(ADC2);
	}
	red /= LEN;
	
	int wn = white - none;
	int rn = red - none;
	int bn = blue - none;
	
	cout << "w0: " << bw << " r0: " << rw << " b0: " << rb << endl;
	cin >> red;
	*/
	
		
	int none, white, blue, red;


	while(true){
		cin >> red;
	
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
	}
	
	
	/*
	int tmp[LEN] = {0};
	int reading = 0;
	while(true)
	{
		reading = rlink.request(ADC2);
		for(int i=LEN-1; i>=1; i--){
			tmp[i] = tmp[i-1];
		}
		tmp[0] = reading;
		
		int sum = 0;
		for(int i=0; i<LEN; i++){
			sum += tmp[i];
		}
		sum /= LEN;
		cout << sum << endl;
	}*/
	//cout << rlink.request(ADC0) << endl;
	//cout << rlink.request(ADC1) << endl;
	//cout << rlink.request(ADC2) << endl;
	//cout << rlink.request(ADC3) << endl;
	//cout << rlink.request(ADC4) << endl;
}
