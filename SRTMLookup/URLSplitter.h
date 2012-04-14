/*
 * URLSplitter.h
 *
 *  Created on: 31.12.2011
 *      Author: dennis
 */

#ifndef URLSPLITTER_H_
#define URLSPLITTER_H_

#include <string>
#include <vector>

class URLSplitter {
public:
	struct URLDetails {
		std::string protocol;
		std::string host;
		std::string port;
		std::string path;
		std::string file;
		std::string parameters;
		std::vector<std::string> ipadresses;
	};
	static bool Run(std::string & URL, URLSplitter::URLDetails & details);
private:

};

#endif /* URLSPLITTER_H_ */
