//
// Server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Developer: Gelson Rodrigues
// geoldery@gmail.com
//
// Static class to show some messages formated on screen.
// this version don´t write in files yet.

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include<iostream>
#include<string>
namespace utils
{
	enum e_log_type
	{
		message,
		debug,
		error,
		warning
	};

	class Logger
	{
	public:
		/*
		* Print on screen formated string on screen
		* @param msg - message to print
		* @logType - type o message
		* return void
		*/
		static void trace(const std::string& msg, e_log_type logType)
		{
			std::string l_full_msg("");
			switch (logType)
			{
			case message:
			{
				l_full_msg += "[MESSAGE]";
				break;
			}
			case debug:
			{
				l_full_msg += "[DEBUG]";
				break;
			}

			case error:
			{
				l_full_msg += "[ERROR]";
				break;
			}
			case warning:
			{
				l_full_msg += "[WARNING]";
				break;
			}
			default:
				l_full_msg += "[DEBUG]";
			}

			std::cout << l_full_msg + " " + msg + "\n";
		}
	private:
		Logger() {}
	};
}
#endif