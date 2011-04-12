/*
 * DataResolver.cpp
 *
 *  Created on: 04.02.2010
 *      Author: Fedor
 */

#include "DataResolver.h"

namespace NewLi {


DataResolver::~DataResolver() {
	// TODO Auto-generated destructor stub
	}

DataResolver :: DataResolver(std::string host, std::string path) :
	_host(host), _path(path), _p(host, path)
	{}

int DataResolver :: readData() {
	boost::asio::io_service io_service;

	// Get a list of endpoints corresponding to the server name.
	tcp::resolver resolver(io_service);
	tcp::resolver::query query(_host, "http");
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	tcp::resolver::iterator end;

	tcp::socket socket(io_service);
	boost::system::error_code error = boost::asio::error::host_not_found;
	while (error && endpoint_iterator != end)	{
		socket.close();
		socket.connect(*endpoint_iterator++, error);
		}
	if (error) {
		std::cout << error.message();
		//throw boost::system::system_error(error);
		return 0;//error.value();
		}

	boost::asio::streambuf request;
	std::ostream request_stream(&request);

	request_stream << _p();

	/*request_stream << "GET " << _path << " HTTP/1.0\r\n";
	request_stream << "Host: " << _host << "\r\n";
	request_stream << "Accept: *\/*\r\n";
	request_stream << "Connection: close\r\n\r\n";*/

	boost::asio::write(socket, request);

	boost::asio::streambuf response;
	boost::asio::read_until(socket, response, "\r\n");

	std::istream response_stream(&response);
	std::string http_version;
	response_stream >> http_version;
	unsigned int status_code;
	response_stream >> status_code;
	std::string status_message;
	std::getline(response_stream, status_message);

	if (!response_stream || http_version.substr(0, 5) != "HTTP/"){
		std::cout << "Invalid response\n";
		return -1;
		}//
	if (status_code != 200)	{
		std::cout << "Response returned with status code " << status_code << "\n";
		return status_code;
		}

	boost::asio::read_until(socket, response, "\r\n\r\n");

	_resHeader = "";
	std::string header;
	while (std::getline(response_stream, header) && header != "\r")	{
		_resHeader += header;
		}

	std::istream is(&response);
	_resBody = "";

    if (response.size() > 0)	{
    	std::stringstream buffer;
    	buffer << &response;

    	_resBody += buffer.str();
		}

    while (boost::asio::read(socket, response,
          boost::asio::transfer_at_least(1), error))	{
		std::stringstream buffer;
		buffer << &response;

		_resBody += buffer.str();
		}


	return 200;
	}

}
