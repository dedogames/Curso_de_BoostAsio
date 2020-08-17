//
// Server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Developer: Gelson Rodrigues
// geoldery@gmail.com
//
// this file has 3 classes
// 1 - Service
//     Read and process request from cliente and
//     response 
// 2 - Acceptor
//     Wait for clientes in loop and when receved request call Service
// 3 - Synchronous Server 
//     Manager I/O and start all process to comunicate with cliente
//

#ifndef SERVER_HPP
#define SERVER_HPP

#include<boost/asio.hpp>
#include<boost/make_shared.hpp>
#include<memory>
#include<atomic>
#include<thread>
#include"../library/utils/Logger.hpp"
#include "../library/bit_message/ParserBitcoinMessage.hpp"
#include "../library/utils/DateTimeConverter.hpp"
#include "../library/bit_message/Trade.hpp"
#include<istream>
using namespace boost::asio;
using namespace library;
namespace bit_server
{
	/*
	   This class don´t know about boost::asio		
	*/
	class TradeService
	{
		public:
		TradeService(){}

		/*
		* Emulate a processing request
		* @param l_cli - 
		*
		* return void
		*/
		void process_trade(std::string &l_cli)
		{
			utils::Logger::trace("Processing request", utils::e_log_type::message);
			m_client = l_cli;
		}

		/*
		* Create a simple formated message to client
		* return string with trade formated
		*/
		std::string response_msg()
		{
			// part of .json from https://www.mercadobitcoin.net/api/BTC/trades/
			//[{"tid":6666357,"date":1597025162,"type":"buy","price":64600,"amount":0.00110383}]

			/* convert manualy epoc date to YYYYmmddHHMMSS*/
			std::string epoc_date("1597025162");
			std::string l_full_date("");
			std::pair<u_int, u_int> l_date_time_pair = utils::Date_Time_Converter::epoc_to_YYYmmdd_HHMMSS(epoc_date, l_full_date);
			/* Create one Trade based on json*/
			library::bt_message::TradePtr l_trade_ptr = boost::make_shared<library::bt_message::Trade>();// TradePtr(new Trade());
			l_trade_ptr->m_id = boost::lexical_cast<u_int>("6666357");
			l_trade_ptr->m_date = l_date_time_pair.first;
			l_trade_ptr->m_time = l_date_time_pair.second;
			l_trade_ptr->m_type = library::bt_message::etrade_type::buy;
			l_trade_ptr->m_price = boost::lexical_cast<double>("64600");
			l_trade_ptr->amount = boost::lexical_cast<float>("0.00110383");
			l_trade_ptr->m_date_time = l_full_date;

			// prepare message to return
			std::string l_parsed_message = l_trade_ptr->to_string() + "\n";			 
			utils::Logger::trace("[Response to [" + m_client + "] " + l_parsed_message, utils::e_log_type::message);

			return l_parsed_message;
		}
		private:
		std::string m_client;
	};
	typedef boost::shared_ptr<TradeService> TradeServicePtr;

    //***************************************************************************************

	/*
	   This class is like a brigde betwwen network and application	   
	*/
	class Service
	{
	public:
		Service() {}

		/*
		* Processes a request from client synchronously but parallel creating a thread
		* @param cli_socket - represent connection with client
		*
		* return void
		*/
		void start_handler_connection(boost::shared_ptr<ip::tcp::socket> cli_socket)
		{
			std::thread l_thread(([this, cli_socket]() 
			{
				utils::Logger::trace("Handle Connection", utils::e_log_type::message);
				handler_connection(cli_socket);
			}));

			l_thread.detach();
		}

	private:

		/*
		* Read from client socket, process message and write to the socket
		* @param cli_socket - represent connection with client
		* output - write one trade on socket
		* return void
		*/
		void handler_connection(boost::shared_ptr<ip::tcp::socket> cli_socket)
		{
			try {
				utils::Logger::trace("Read request until ", utils::e_log_type::message);
				streambuf request;
				// Read what client send until found '\n'
				read_until(*cli_socket.get(), request, '\n');
					
				//convert request to string
				std::istream l_isstream(&request);
				std::string l_client("everyone");				
				l_isstream >> l_client;

				/* Start process*/
				TradeServicePtr l_trade_serv = boost::make_shared< TradeService>();
				l_trade_serv->process_trade(l_client);
				/* Finished process*/
				
				// Return trade to client
				write(*cli_socket.get(), buffer(l_trade_serv->response_msg()));
			}
			catch (boost::system::system_error &e)
			{
				//ops! something wrong, review your code
				std::cout << e.what() << std::endl;
				std::string l_err = e.what();
				utils::Logger::trace("[Service::handler_connection] - " + l_err, utils::e_log_type::error);
			}

		 
		}
	};
	typedef boost::shared_ptr<Service> ServicePtr;

	//***************************************************************************************

	/*
		This class wait for clients and call service to processes request when request arive
	*/
	class Acceptor
	{
	public:
		Acceptor(io_service & ios, u_int port):
		m_ios(ios),
		m_acceptor(m_ios,ip::tcp::endpoint(ip::address_v4::any(), port))		
		{
			utils::Logger::trace("Listen clients on port "+std::to_string(port), utils::e_log_type::message);	
			
			m_acceptor.listen();
		}

		/*
		* Accept for connection and create a Service to process request 
		* return void
		*/
		void acceptor()
		{
			
			utils::Logger::trace("Wait for a new client connection", utils::e_log_type::message);
            /* to comunicate with clients, aticve socket was created*/
			boost::shared_ptr<ip::tcp::socket> l_socket = boost::make_shared<ip::tcp::socket>(m_ios);
			m_acceptor.accept(*l_socket.get());
			
			utils::Logger::trace("Connection accepted", utils::e_log_type::message);
			
			ServicePtr l_service_ptr = boost::make_shared< Service>();
			l_service_ptr->start_handler_connection(l_socket);
		}
	private:
		//manager I/O network
		io_service& m_ios;
		//passive socket 
		ip::tcp::acceptor m_acceptor;
		
	};

	typedef boost::shared_ptr<Acceptor> AcceptorPtr;

	//***************************************************************************************
	
	/*
		Start process to comunicate with clients
	*/
	class Server
	{
	public:

		/* @constructor
		*  @param port - protocol port where Server listen clients 
		*/
		Server(u_int port):m_port(port), m_stop(false) 
		{
			
		}


		/*  
		*  runs the server on a new thread
		*  @param port - protocol port where Server listen clients
		*/
		void start()
		{
			m_thread.reset(new std::thread(
											[this](){
														utils::Logger::trace("Server started", utils::e_log_type::message);
														run();
													}
											));
		}

		/*
		*  Shutdown server  
		*/
		void stop()
		{	
			m_stop.store(true);		 
			m_thread->join();
			utils::Logger::trace("Server stoped", utils::e_log_type::message);
		}
	private:
		/*
		* Run server until server stoped 
		*/
		void run()
		{
			AcceptorPtr l_accept_ptr = boost::make_shared<Acceptor>(m_ios,m_port);
			utils::Logger::trace("Server running...", utils::e_log_type::message);
			while(!m_stop.load())
			{
				l_accept_ptr->acceptor();
		    }		
		}
		//manager I/O network
		io_service m_ios;
		//Objects of atomic types are the only C++ objects that are free from data races
		std::atomic<bool> m_stop; 
		// port where server wait for clients
		u_int m_port;
		//start server in other thread
		std::unique_ptr<std::thread> m_thread;
	};

	typedef boost::shared_ptr<Server> ServerPtr;
}
#endif

