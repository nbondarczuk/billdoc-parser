#ifndef __XML_DN_HPP__
#define __XML_DN_HPP__

#include <assert.h>

#include <iostream>
#include <fstream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xmlutl.hpp"
#include "xml_item.hpp"

class XMLDn : public XMLItem {
public:
	XMLDn() : root(0) {}
	
	XMLDn(const rapidxml::xml_node<>* node) : root(node) {
		load();
	}	

	void dump() const {
		assert(root);				
		std::cout << "Dn:"
				  << " Num: " << Num
				  << " Main: " << Main
				  << std::endl;
	}

	void load() {
		assert(root);		
		load_attributes();
	}
	
	const char* Num;
	const char* Main;

private:
	const rapidxml::xml_node<>* root;

	// mandatory values
	void load_attributes(){
		Num = find_attribute_value("Num", root);
		Main = find_attribute_value("Main", root);
	}		
};

#endif // __XML_DN_HPP__
