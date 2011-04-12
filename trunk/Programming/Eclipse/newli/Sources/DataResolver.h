/*
 * DataResolver.h
 *
 *  Created on: 04.02.2010
 *      Author: Fedor
 */

#ifndef DATARESOLVER_H_
#define DATARESOLVER_H_

#include <iostream>
//#include <boost/regex.hpp>
#include <boost/asio.hpp>

#include "QueryProcessor.h"

using boost::asio::ip::tcp;

namespace NewLi {

class DataResolver {
		std::string _host;
		std::string _path;

		std::string _resHeader;
		std::string _resBody;

		QueryProcessor _p;

	public :
		DataResolver(std::string host, std::string path = "/");
		virtual ~DataResolver();

		void setQueryFile(std::string file) { _p.setQueryFile(file); }

		std::string resHeader() { return _resHeader; }
		std::string resBody() { return _resBody; }

		int readData();

	};

}

#endif /* DATARESOLVER_H_ */
