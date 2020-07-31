//
// main.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Desenvolvedor: Gelson Rodrigues
// geoldery@gmail.com
//
// Create a passive socket to 
// accepted connection for endpoints(clients) using boost::assio
// 

#include<iostream>
#include <boost/asio.hpp>
 
int main()
{	

	// The size of the queue - pending connection	
	const  int l_size_queue = 10;
	//Step 0 - Get port protocol
	unsigned short l_port = 8574;
	//Step 2 - Creating a server endpoint
	boost::asio::ip::tcp::endpoint l_endpoint(boost::asio::ip::address_v4::any(), l_port);
	boost::asio::io_service l_io_service;
	try
	{
		std::cout << "[SERVER] Waiting for clients port("<<l_port<<")...." << std::endl;
		
		//Step 3  - Creating Acceptor socket
		boost::asio::ip::tcp::acceptor l_acceptor(l_io_service, l_endpoint.protocol());
		
		//Step 4 - Binding acceptor to endpoint
		l_acceptor.bind(l_endpoint);
		
		//Step 5 - Start to listen clients
		l_acceptor.listen(l_size_queue);
		
		//Step 6 - Creating active socket
		boost::asio::ip::tcp::socket l_socket(l_io_service);
		
		//Step 7 - Processing the next connection and connect active socket to the client
		l_acceptor.accept(l_socket);
		
		std::cout << "[SERVER] Accepted connection from Client" << std::endl;
		
	}
	catch (boost::system::system_error &e)
	{
		std::cerr << "[SERVER] - error Code " << e.code() << 
		 " Message: " << e.what() << std::endl;
	}
	getchar();
	return 0;
}