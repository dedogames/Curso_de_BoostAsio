//
// ParserBitcoinMessage.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Developer: Gelson Rodrigues
// geoldery@gmail.com
//
// Deserialize a string in a Trade object
//  


#ifndef PARSER_BITCOIN_MESSAGE_HPP
#define PARSER_BITCOIN_MESSAGE_HPP

#include<boost/shared_ptr.hpp>
#include<boost/algorithm/string.hpp>
#include<boost/lexical_cast.hpp>
#include<vector>
#include<string>
#include"library/bit_types.hpp"
#include "Trade.hpp"

namespace library
{
	namespace bt_message
	{
		namespace constants
		{
			const std::string SPLITER_TRADE=",";
		}

		//Parse message Server to client
		class Parser_Message
		{
		public:
			Parser_Message() {}

			/*
			* Create a Trade from string formated
			* @param msg_from_web_server - string on format Trade::to_string(",")
			* 
			* return filled TradePtr 
			*/
			TradePtr deserialize(std::string& msg_from_web_server)
			{				
				std::vector<std::string> l_split_trade;
				//msg_from_web_server must be in the following format and order
				//id,date,time,type,price,amount,date_time
				boost::split(l_split_trade, msg_from_web_server, boost::is_any_of(constants::SPLITER_TRADE));
				//Create a Trade Object and fill all members
				TradePtr l_trade_curr     = boost::make_shared<Trade>();
				l_trade_curr->m_id        = boost::lexical_cast<u_int>(l_split_trade[e_tade_fields::id]);
				l_trade_curr->m_date      = boost::lexical_cast<u_int>(l_split_trade[e_tade_fields::date]);
				l_trade_curr->m_time      = boost::lexical_cast<u_int>(l_split_trade[e_tade_fields::time]);
				//trick for small enums
				std::string l_type        = l_split_trade[e_tade_fields::type];				
				l_trade_curr->m_type      = l_type == "1" ? etrade_type::sell : etrade_type::buy;
	
				l_trade_curr->m_price     = boost::lexical_cast<double>(l_split_trade[e_tade_fields::price]);
				l_trade_curr->amount      = boost::lexical_cast<float>(l_split_trade[e_tade_fields::amount]);
				l_trade_curr->m_date_time = l_split_trade[e_tade_fields::date_time];
				
				return l_trade_curr;
			} 

		private:
			enum e_tade_fields
			{
				id, date, time, type, price, amount, date_time
			};
		};
		typedef boost::shared_ptr<Parser_Message> Parser_MessagePtr;
	}
}

#endif