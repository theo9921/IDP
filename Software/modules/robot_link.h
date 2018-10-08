class robot_link {
public:
	//Construction/Destruction
	robot_link();
	~robot_link();
	//Initialization
	bool initialize();	//Connect to local computer
	bool initialize(int card);	//connect ot network card n
	bool initialize(const char *host);	//connect to specified host
	bool reinitialize();	//reconnect after error
	bool command (commad_instruction cmd, int param);
	int request (request_instruction)
	//Error Handling
	void clear_errs();
	link_err get_err ();
	link_err lookup_err (int n);
	void print_errs(const char *prefix)
	void print_errs();
	bool any_errs();
	bool fatal_err();
}
