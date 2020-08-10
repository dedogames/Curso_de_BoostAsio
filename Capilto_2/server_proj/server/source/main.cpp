//
// main.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Developer: Gelson Rodrigues
// geoldery@gmail.com
//
// start application  
//
//Conventions syntax for C++
// pointers  - my_foo_ptr
// class     - My_Foo_Class
// enum      - emy_foo_enum
// namespace - my_foot_namespace
// interface - IMy_Foo_Interface

#include "Application.hpp"
 
/*
	From here don't matter if I use boost:: or Berkeley socket directly,
	it's very important to abstract your solution like components
*/
int main(int argc, char** argv)
{
	
	if (argc < 2)
	{
		std::cerr <<
			"Usage: server.exe <port>\n" <<
			"Example:\n" <<
			" server.exe 3584 \n";
		//return EXIT_FAILURE;
	}
	Application l_app;
	//u_int port_num = std::stoi(argv[1]); 
	u_int port_num(3333);
	l_app.start(port_num);
 
	return 0;
}

 