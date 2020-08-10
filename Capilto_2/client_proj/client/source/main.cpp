#include <boost/asio.hpp>
#include <iostream>

using namespace boost;
std::string name;
class SyncTCPClient {
public:
	SyncTCPClient(const std::string& raw_ip_address,
		unsigned short port_num) :
		m_ep(asio::ip::address::from_string(raw_ip_address),
			port_num),
		m_sock(m_ios) {

		m_sock.open(m_ep.protocol());
	}

	void connect() {
		m_sock.connect(m_ep);
	}

	void close() {
		m_sock.shutdown(
			boost::asio::ip::tcp::socket::shutdown_both);
		m_sock.close();
	}

	std::string emulateLongComputationOp(
		unsigned int duration_sec) {

		std::string request = name + "\n";

		sendRequest(request);
		return receiveResponse();
	};

private:
	void sendRequest(const std::string& request) {
		asio::write(m_sock, asio::buffer(request));
	}

	std::string receiveResponse() {
		asio::streambuf buf;
		asio::read_until(m_sock, buf, '\n');

		std::istream input(&buf);

		std::string response;
		std::getline(input, response);

		return response;
	}

private:
	asio::io_service m_ios;

	asio::ip::tcp::endpoint m_ep;
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

	//auto const host = ;
	 
	const std::string raw_ip_address = argv[1];
	const unsigned short port_num =  std::stod(argv[2]);
	name = argv[3];

	try {
		SyncTCPClient client(raw_ip_address, port_num);

		// Sync connect.
		client.connect();

		std::cout << "Sending request to the server... "
			<< std::endl;

		std::string response =
			client.emulateLongComputationOp(10);

		std::cout << "Response received: " << response
			<< std::endl;

		// Close the connection and free resources.
		client.close();
	}
	catch (system::system_error &e) {
		std::cout << "Error occured! Error code = " << e.code()
			<< ". Message: " << e.what();

		return e.code().value();
	}

	return 0;
}