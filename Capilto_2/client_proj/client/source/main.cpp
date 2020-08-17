//
// main.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Developer: Gelson Rodrigues
// geoldery@gmail.com
//
// Very simple client
//
// Basically , this app connects to a server 
// and print on screen one trade
  
#include <boost/asio.hpp>
#include <iostream>

using namespace boost;
std::string name;

class Server
{
public:
	Server(const std::string& raw_ip_address,
		unsigned short port_num) :
		m_ep(asio::ip::address::from_string(raw_ip_address),
			port_num),
		m_sock(m_ios)
	{
		//open socket based on endpoint
		m_sock.open(m_ep.protocol());
	}

	void connect()
	{
		//connect on server
		m_sock.connect(m_ep);
	}

	void close()
	{
		//kills connection to the server
		m_sock.shutdown(
			boost::asio::ip::tcp::socket::shutdown_both);
		m_sock.close();
	}


	void sendRequest(const std::string& request)
	{
		//Send request
		asio::write(m_sock, asio::buffer(request));
	}

	std::string process_resposne()
	{
		// Read buffer
		asio::streambuf buf;
		asio::read_until(m_sock, buf, '\n');

		std::istream input(&buf);
		// put on string 
		std::string response;
		std::getline(input, response);

		return response;
	}
private:
	//main I/0 manager
	asio::io_service m_ios;
	// server address
	asio::ip::tcp::endpoint m_ep;
	//socket to server
	asio::ip::tcp::socket m_sock;
};

int main(int argc, char** argv)
{
	// Check command line arguments.
	if (argc < 3)
	{
		std::cerr <<
			"Usage: <host> <port> <name>\n" <<
			"Example:\n" <<
			"    127.0.0.1 8544 gelson\n";
		return EXIT_FAILURE;
	}

	const std::string raw_ip_address = argv[1];
	const unsigned short port_num    = std::stod(argv[2]);
	name = argv[3];

	try {
		Server server(raw_ip_address, port_num);

		// Sync connect.
		server.connect();

		std::cout << "Sending request to the server... " << std::endl;

		server.sendRequest(name);
		std::string response = server.process_resposne();

		std::cout << "Response received: " << response << std::endl;

		// Close the connection and free resources.
		server.close();
	}
	catch (system::system_error &e) {
		std::cout << "Error occured! Error code = " << e.code()	<< ". Message: " << e.what();

		return e.code().value();
	}

	return 0;
}