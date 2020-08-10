//
// DateTimeConverter.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Developer: Gelson Rodrigues
// geoldery@gmail.com
//
// Static class to convert any kind of date time
// all convertions will be here
//
// What is epoch time ? -> www.epochconverter.com



#ifndef DATETIMECONVERTER_HPP
#define DATETIMECONVERTER_HPP

#include<map>
#include"../bit_types.hpp"
#include <boost/date_time/posix_time/posix_time_io.hpp>
namespace utils
{
	class Date_Time_Converter
	{
	public:
		/*
		* Convert epoc date to human-readable date
		* @param epoc_date - POSIX time
		* @param full_date - output with full date YYYYmmddHHMMSS
		* return pair<u_int,u_int>(YYYYmmdd, HHMMSS)
		*/
		static std::pair<u_int, u_int> epoc_to_YYYmmdd_HHMMSS(std::string& epoc_date, std::string &full_date)
		{
			std::pair<u_int, u_int> l_date_time;
			std::time_t btime_ = boost::lexical_cast<std::time_t>(epoc_date); 
			std::stringstream str;
			/*POSIX time to  YYYYmmdd HHMMSS*/
			boost::posix_time::time_facet *facet = new boost::posix_time::time_facet("%Y%m%d%H%M%S");
			str.imbue(std::locale(str.getloc(), facet));
			str << boost::posix_time::from_time_t(btime_);
			full_date = str.str();

			/*extract date and time */
			l_date_time.first = boost::lexical_cast<u_int>(full_date.substr(0, 8));
			l_date_time.second = boost::lexical_cast<u_int>(full_date.substr(8, 14));

			return l_date_time;
		}
	private:
		Date_Time_Converter() {}
	};
}
#endif