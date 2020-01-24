#ifndef __XML_AGG_SET_HPP__
#define __XML_AGG_SET_HPP__

#include <assert.h>

#include <iostream>
#include <fstream>
#include <string>
#include <set>

#include "rapidxml.hpp"
#include "xml_att.hpp"
#include "xml_item.hpp"

class XMLAggSet : public XMLItem {
public:
	XMLAggSet() : root(0) {}
	
	XMLAggSet(const rapidxml::xml_node<> *node) : root(node) {
		load();
	}

	~XMLAggSet() {
		clear();
	}
	
	void dump() const {
		assert(root);		
		std::cout << "AggSet: " << std::endl;
		dump_atts();
	}

	void load() {
		assert(root);		
		load_atts();
	}
	
	std::set<XMLAtt*> Atts;

private:	
	const rapidxml::xml_node<>* root;
	
	// conditional values
	void load_atts() {
		load_subnodes<XMLAtt>(root, "Atts", Atts);
	}
	
	void dump_atts() const {
		const unsigned int n = Atts.size();
		if (n) {
			std::cout << "Atts: " << "(" << n << ")" << std::endl;		
			for (auto it = Atts.begin(); it != Atts.end(); ++it) {
				(*it)->dump();
			}
		}
	}

	void clear() {
		clear_atts();
	}

	void clear_atts() {
		for (auto it = Atts.begin(); it != Atts.end(); ++it) {
			delete *it;
		}
		Atts.clear();
	}	
};

#endif // __XML_AGG_SET_HPP__
