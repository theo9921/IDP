/*
*	@author: T.T. Ouzounellis Kavlakonis
*	Date: 18 October 2018
*	Project: Part 1B Engineering Tripos Integrated Design Project
*/

#include <robot_instr.h>
#include <robot_link.h>
#include <stopwatch.h>

#define ROBOT_NUM 9

//number between 0 and 127 (128-255 for reverse)
#define DEFAULT_SPEED 40
//above that direction of motors will be reversed
#define REVERSE_STHRES 128
