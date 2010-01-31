#include <iostream>

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

using namespace rapidxml;

int main() {
	xml_document<> doc;
	xml_node<> *node = doc.allocate_node(node_element, "a", "Google");
	doc.append_node(node);
	xml_attribute<> *attr = doc.allocate_attribute("href", "google.com");
	node->append_attribute(attr);

	print(std::cout, doc, 0);

	return 0;
	}
