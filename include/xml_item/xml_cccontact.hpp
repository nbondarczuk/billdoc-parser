#ifndef __XML_CCCONTACT_HPP__
#define __XML_CCCONTACT_HPP__

#include <assert.h>

#include <iostream>
#include <fstream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xmlutl.hpp"
#include "xml_item.hpp"

class XMLCCContact : public XMLItem {
public:
	XMLCCContact() : root(0) {}
	
	XMLCCContact(const rapidxml::xml_node<>* node) : root(node) {
		load();
	}	

	void dump() const {
		assert(root);				
		std::cout << "CCContact:" << std::endl;
	}

	void load() {
		assert(root);		
	}
	
private:
	const rapidxml::xml_node<>* root;
};

#endif // __XML_CCCONTACT_HPP__
