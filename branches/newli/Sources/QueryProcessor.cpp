/*
 * QueryProcessor.cpp
 *
 *  Created on: 04.02.2010
 *      Author: Fedor
 */

#include "QueryProcessor.h"

namespace NewLi {

QueryProcessor :: QueryProcessor(std::string host, std::string path) {
	// TODO Auto-generated constructor stub
    _env["host"] = host;
    _env["path"] = path;

	}

QueryProcessor :: ~QueryProcessor() {
		// TODO Auto-generated destructor stub
	}

std::string QueryProcessor :: operator()() {
	processQueryFile ();
	processQuery ();

	return _query;
	}

bool QueryProcessor :: processQueryFile () {
	std::string fileName = (_queryFile.size() > 0) ? _queryFile : QueryDefaultFile;

	std::ifstream file((QueryDirectory + fileName).c_str());
	std::stringstream buffer;

	buffer << file.rdbuf();
	_query = buffer.str();

	file.close();

	return true;
	}

bool QueryProcessor :: processQuery () {
    sregex envar = "${" >> (s1 = +_w) >> '}';
    std::string output = regex_replace(_query, envar, ref(_env)[s1]);

    _query = output;

    return true;
	}


}
