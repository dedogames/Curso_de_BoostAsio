//
// main.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Developer: Gelson Rodrigues
// geoldery@gmail.com
//
// start application   

#include "Application.hpp"
 
int main(int argc, char** argv)
{
	const unsigned int port_num(8596);
	/*
	uncomment this part to set port from terminal
	if (argc < 2)
	{
		std::cerr <<
			"Usage:   <port> <name>\n" <<
			"Example:\n" <<
			"    server.exe 8544 gelson\n";
		return EXIT_FAILURE;
	}
 
	port_num = std::stod(argv[1]);
	*/
	Application l_app;  
	l_app.start(port_num);
 
	return 0;
}

 