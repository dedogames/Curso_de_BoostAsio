//
// Trade.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Developer: Gelson Rodrigues
// geoldery@gmail.com
//
// This class only store values
// 

#ifndef TRADE_HPP
#define TRADE_HPP

#include<boost/shared_ptr.hpp>
#include<string>
#include"library/bit_types.hpp"
namespace library
{
	namespace bt_message
	{
		//point of negotiation enum
		enum etrade_type
		{
			buy,
			sell
		};

		class Trade
		{
		public:
			Trade() {}
			virtual ~Trade() {}

			// unique number
			u_int64 m_id;
			//YYYYmmdd
			u_int m_date;
			//HHMMSS
			u_int m_time;
			//point of negotiation
			etrade_type m_type;
			//Price Negotiation
			double m_price;
			//Amount of negotiation
			float amount;
			//YYYYmmddHHMMSS
			std::string m_date_time;

			/*
			* Concact all members with div into a string
			* @param div[optional] - divisor between members when print			
			* return string with all Trade members
			*/
			std::string to_string(const std::string & div = ",")
			{
				std::string l_return("");
				l_return =
					std::to_string(m_id) + div +
					std::to_string(m_date) + div +
					std::to_string(m_time) + div +
					std::to_string(m_type) + div +
					std::to_string(m_price) + div +
					std::to_string(amount) + div +
					m_date_time;
				return l_return;
			}
		};
		typedef boost::shared_ptr<Trade> TradePtr;
	}
}
#endif