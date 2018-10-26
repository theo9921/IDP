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
	
	int white, blue, red;
	
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
	
	int rw = red - white;
	int bw = blue - white;
	int rb = red - blue;
	
	cout << "b-w0: " << bw << " r-w0: " << rw << " r-b0: " << rb << endl;
	cin >> red;
	
	while(true){
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
		
		cout << "b-w: " << blue-white-bw << " r-w: " << red-white-rw << " r-b: " << red-blue-rb << endl;
		
		cin >> red;
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
