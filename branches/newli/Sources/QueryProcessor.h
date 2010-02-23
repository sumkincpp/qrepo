/*
 * QueryProcessor.h
 *
 *  Created on: 04.02.2010
 *      Author: Fedor
 */

#ifndef QUERYPROCESSOR_H_
#define QUERYPROCESSOR_H_

#include <conio.h>

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <boost/xpressive/xpressive.hpp>
#include <boost/xpressive/regex_actions.hpp>


using namespace boost::xpressive;

namespace NewLi {

const std::string QueryDirectory = "";//"queries/";
const std::string QueryDefaultFile = "default.txt";

class QueryProcessor {
		std::map<std::string, std::string> _env;
		std::string _queryFile;

		std::string _query;

		bool writeContentLength();

	public:
		QueryProcessor(std::string host, std::string path = '/');
		virtual ~QueryProcessor();

		void setQueryFile(std::string file) { _queryFile = file; }
		bool processQueryFile ();
		bool processQuery ();

		std::string queryFile() { return _queryFile; }

		std::string operator() ();

	};

}

#endif /* QUERYPROCESSOR_H_ */
