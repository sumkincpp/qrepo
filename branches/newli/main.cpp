#include <iostream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/regex.hpp>
#include <boost/asio.hpp>


#include <iomanip>

using boost::asio::ip::tcp;

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

using namespace rapidxml;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class DataResolver {
	private :
		std::string _host;
		std::string _path;

		std::string _resHeader;
		std::string _resBody;


	public :
		DataResolver(std::string host, std::string path = "/");

		std::string resHeader() { return _resHeader; }
		std::string resBody() { return _resBody; }

		int readData();

	};
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
DataResolver :: DataResolver(std::string host, std::string path) :
	_host(host), _path(path)
	{}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
int main() {
	xml_document<> doc;
	xml_node<> *node = doc.allocate_node(node_element, "a", "Google");
	doc.append_node(node);
	xml_attribute<> *attr = doc.allocate_attribute("href", "google.com");
	node->append_attribute(attr);
//
	print(std::cout, doc, 0);

	std::cout << "hello world!\n";

	DataResolver r("localhost", "/test.html");
	r.readData();

	std::cout << r.resBody();
	//readData("/test.html", "localhost");
//	return 0;
	}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
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
	if (error) throw boost::system::system_error(error);

	boost::asio::streambuf request;
	std::ostream request_stream(&request);
	request_stream << "GET " << _path << " HTTP/1.0\r\n";
	request_stream << "Host: " << _host << "\r\n";
	request_stream << "Accept: */*\r\n";
	request_stream << "Connection: close\r\n\r\n";

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
		}
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
