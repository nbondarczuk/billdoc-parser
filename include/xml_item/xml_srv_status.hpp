#ifndef __XML_SRV_STATUS_HPP__
#define __XML_SRV_STATUS_HPP__

#include <assert.h>

#include <iostream>
#include <fstream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xmlutl.hpp"
#include "xml_item.hpp"
#include "xml_date.hpp"

class XMLSrvStatus : public XMLItem {
public:
	XMLSrvStatus() : root(0) {}
	
	XMLSrvStatus(const rapidxml::xml_node<>* node) : root(node) {
		load();
	}	

	~XMLSrvStatus() {
		clear();
	}
	
	void dump() const {
		assert(root);		
		std::cout << "SrvStatus:"
				  << " Status: " << Status
				  << std::endl;
		dump_dates();
	}

	void load() {
		assert(root);		
		load_attributes();
		load_dates();
	}
	
	const char* Status;
	std::set<XMLDate*> Dates;

private:
	const rapidxml::xml_node<>* root;

	// mandatory values
	void load_attributes(){
		Status = find_attribute_value("Status", root);
	}		

	// conditional set of values
	void load_dates() {
		load_subnodes<XMLDate>(root, "Date", Dates);
	}

	void dump_dates() const {
		const unsigned int n = Dates.size();
		if (n) {
			std::cout << "Dates: " << "(" << n << ")" << std::endl;
			for (auto it = Dates.begin(); it != Dates.end(); ++it) {
				(*it)->dump();
			}
		}
	}

	void clear() {
		clear_dates();
	}
	
	void clear_dates() {
		for (auto it = Dates.begin(); it != Dates.end(); ++it) {
			delete *it;
		}
		Dates.clear();
	}		
};

#endif // __XML_SRV_STATUS_HPP__
