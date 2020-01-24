#ifndef __XML_SRV_PARAMS_HPP__
#define __XML_SRV_PARAMS_HPP__

#include <assert.h>

#include <iostream>
#include <fstream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xmlutl.hpp"
#include "xml_item.hpp"
#include "xml_date.hpp"

class XMLSrvParams : public XMLItem {
public:
	XMLSrvParams() : root(0) {}
	
	XMLSrvParams(const rapidxml::xml_node<>* node) : root(node) {
		load();
	}	

	~XMLSrvParams() {
		clear();
	}
	
	void dump() const {
		assert(root);		
		std::cout << "SrvParams:"
				  << " FlexParamDesc: " << FlexParamDesc
				  << " ParamDesc: " << ParamDesc
				  << " ParamVal: " << ParamVal
				  << std::endl;
		dump_dates();
	}

	void load() {
		assert(root);		
		load_attributes();
		load_dates();
	}
	
	const char* FlexParamDesc;
	const char* ParamDesc;
	const char* ParamVal;
	std::set<XMLDate*> Dates;

private:
	const rapidxml::xml_node<>* root;

	// mandatory values
	void load_attributes(){
		FlexParamDesc = find_attribute_value("FlexParamDesc", root);
		ParamDesc = find_attribute_value("ParamDesc", root);
		ParamVal = find_attribute_value("ParamVal", root);
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

#endif // __XML_SRV_PARAM_HPP__
