//
// Application.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Developer: Gelson Rodrigues
// geoldery@gmail.com
//
// For a better aproach, all start from here

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "server/Server.hpp"
#include "library/bit_types.hpp"
#include "library/utils/Logger.hpp"
class Application
{
	public:
	Application()
	{
		 
	}
	void start(u_int port)
	{
		
		utils::Logger::trace("Initiating server...", utils::elog_type::message);
		m_server = boost::make_shared< bit_server::Server>(port);
		run();
	}
	void run()
	{
		try
		{ 
			utils::Logger::trace("Start server....", utils::elog_type::message);
			m_server->start(); 

			//run server forever
			while(true)	{} 

		
		}
		catch (const boost::system::system_error& e)
		{
			std::string l_err = e.what();
			utils::Logger::trace("[Application::run] - " + l_err, utils::elog_type::error);
		}
	}
 
	
	virtual ~Application()
	{
	
	}

	private:
	bit_server::ServerPtr m_server;
};

#endif