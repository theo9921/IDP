/*
*	@author: T.T. Ouzounellis Kavlakonis
*	Date: 18 October 2018
*	Project: Part 1B Engineering Tripos Integrated Design Project
*/

#include <robot_instr.h>
#include <robot_link.h>
#include <stopwatch.h>
#include <bitset>

#define ROBOT_NUM 9
robot_link rlink;

//number between 0 and 127 (128-255 for reverse)
#define DEFAULT_SPEED 80
//above that direction of motors will be reversed
#define REVERSE_STHRES 128

