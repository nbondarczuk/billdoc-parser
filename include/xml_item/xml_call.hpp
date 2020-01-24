#ifndef __XML_CALL_HPP__
#define __XML_CALL_HPP__

#include <assert.h>

#include <iostream>
#include <fstream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xmlutl.hpp"
#include "xml_item.hpp"
#include "xml_xcd.hpp"
#include "xml_fup.hpp"

class XMLCall : public XMLItem {
public:
	XMLCall() : root(0) {}
	
	XMLCall(const rapidxml::xml_node<>* node) : root(node) {
		load();
	}	

	void dump() const {
		assert(root);
		std::cout << "Call:" << std::endl;
		dump_xcd();
		dump_fup();
		
	}

	void load() {
		assert(root);
		load_xcd();
		load_fup();
	}

	XMLXcd* xcd;
	XMLFup* fup;
	
private:
	const rapidxml::xml_node<>* root;

	void load_xcd() {
		xcd = find_subnode<XMLXcd>(root, "XCD");	
	}
	
	void load_fup() {
		fup = find_subnode<XMLFup>(root, "FUP");	
	}

	void dump_xcd() const {
		if (xcd) {
			xcd->dump();
		}
	}
	
	void dump_fup() const {
		if (fup) {
			fup->dump();
		}
	}	
};

#endif // __XML_CALL_HPP__
