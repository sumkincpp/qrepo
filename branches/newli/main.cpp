#include <iostream>
#include <iterator>
#include <algorithm>
#include <conio.h>
#include <boost/progress.hpp>
#include <boost/foreach.hpp>

#include <iomanip>

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

using namespace rapidxml;

#define foreach         BOOST_FOREACH
#define reverse_foreach BOOST_REVERSE_FOREACH

#include "Sources/DataResolver.h"

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
int main() {
//	int a[5]={0};
//	std::cout << sizeof(a)/sizeof(int);
//	std::cout << (char)tolower('H');
/*	char* p = "1234567";
	p[2] =  3;
	std::cout << p;*/
	//-------------------------------------------
/*	std::string hello( "Hello, world!" );

	foreach( char ch, hello )	{
		std::cout << ch;
		}*/

	//-------------------------------------------
/*	boost::progress_timer t;

	xml_document<> doc;
	xml_node<> *node = doc.allocate_node(node_element, "a", "Google");
	doc.append_node(node);
	xml_attribute<> *attr = doc.allocate_attribute("href", "google.com");
	node->append_attribute(attr);

	print(std::cout, doc, 0);*/

	//-------------------------------------------

	try {
		NewLi::DataResolver r("localhost", "/test.html");
		r.readData();

		std::cout << r.resBody();
		}
	catch (std::exception& e)
		{
		std::cout << "Exception: " << e.what() << "\n";
		}
	/*std::cout << std::endl << t.elapsed();*/
	getch();
	}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

