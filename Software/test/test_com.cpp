#include <iostream>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>

#define ROBOT_NUM 33
robot_link rlink;

int main()
{
	int val;
	if (!rlink.initialize(ROBOT_NUM))
	{
		cout << "Cannot initialize link" << endl;
		rlink.print_errs("	");
		return -1;	
	}
	
	val = rlink.request(TEST_INSTRUCTION);
	if (val == TEST_INSTRUCTION_RESULT)
	{
		cout << "Test Passed" << endl;
		return 0;	
	}
	else if (val == REQUEST_ERROR) 
	{
		cout << "Fatal errors on link:" << endl;
		rlink.print_errs();
	}
	else
		cout << "Test  failed (bad value returned)" << endl;
	return -1 
}
