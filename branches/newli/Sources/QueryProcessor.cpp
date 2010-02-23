/*
 * QueryProcessor.cpp
 *
 *  Created on: 04.02.2010
 *      Author: Fedor
 */

#include "QueryProcessor.h"

namespace NewLi {

/*
int str2int (const std::string &str) {
	std::stringstream ss(str);
	int n;
	ss >> n;
	return n;
	}

std::string int2str (int n) {
	std::stringstream ss;
	ss << n;
	return ss.str();
	}
*/
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
	writeContentLength();

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

struct formatter	{
    typedef std::map<std::string, std::string> env_map;
    env_map env;

    template<typename Out>
    Out operator()(smatch const &what, Out out) const
		{
        env_map::const_iterator where = env.find(what[1]);
        if(where != env.end())
			{
            std::string const &sub = where->second;
            out = std::copy(sub.begin(), sub.end(), out);
			}
        else {
        	std::string const &sub = "${" + what[1].str() + "}";
        	out = std::copy(sub.begin(), sub.end(), out);
			}
        return out;
		}
	};



bool QueryProcessor :: processQuery () {
	formatter fmt;
	fmt.env = _env;

    sregex envar = "${" >> (s1 = +_w) >> "}";
    _query = regex_replace(_query, envar, fmt);

    return true;
	}

bool QueryProcessor :: writeContentLength(){
	sregex rex = sregex::compile( "(.*?)\n\n(.*)");
	smatch what;

	if(!regex_match( _query, what, rex )) {
		return 0;
		}

	std::map<std::string, std::string> myEnv;

	myEnv["ContentLength"] = boost::lexical_cast<std::string>(what[2].str().length());

	sregex envar = "${" >> (s1 = +_w) >> '}';
    std::string output = regex_replace(_query, envar, ref(myEnv)[s1]);
    _query = output;

    return 1;
	}


}
