/*
 * URLSplitter.cpp
 *
 *  Created on: 31.12.2011
 *      Author: dennis
 */

#include "URLSplitter.h"
#include <boost/asio.hpp>
#include <boost/regex.hpp>

 bool URLSplitter::Run(std::string & URL, URLSplitter::URLDetails & details){
	try {
		std::vector<std::string> values;
		boost::regex expression(
				//       proto                 host               port
				"^(\?:([^:/\?#]+)://)\?(\\w+[^/\?#:]*)(\?::(\\d+))\?"
				//       path                  file       parameters
				"(/\?(\?:[^\?#/]*/)*)\?([^\?#]*)\?(\\\?(.*))\?"
		);
		std::string src(URL);
		if (boost::regex_split(std::back_inserter(values), src, expression)) {
			details.protocol 	= values[0];
			details.host 		= values[1];
			details.port 		= values[2];
			details.path 		= values[3];
			details.file 		= values[4];
			details.parameters 	= values[5];
		}
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(values[1], "");
		for(boost::asio::ip::tcp::resolver::iterator i = resolver.resolve(query);
				i != boost::asio::ip::tcp::resolver::iterator();
				++i)
		{
			boost::asio::ip::tcp::endpoint end = *i;
			details.ipadresses.push_back(end.address().to_string());
		}
	} catch(std::exception& e) {
		return false;
	}
	return true;
}
