#ifndef __XML_CONTRACT_HPP__
#define __XML_CONTRACT_HPP__

#include <assert.h>

#include <iostream>
#include <fstream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xmlutl.hpp"
#include "xml_item.hpp"
#include "xml_dn.hpp"
#include "xml_charge.hpp"
#include "xml_per_ct_info.hpp"

class XMLContract : public XMLItem {
public:
	XMLContract() : root(0) {}
	
	XMLContract(const rapidxml::xml_node<>* node) : root(node) {
		load();
	}	

	void dump() const {
		assert(root);				
		std::cout << "Contract:"
				  << " Id: " << Id
				  << " MRKT: " << MRKT
				  << " SM: " << SM
				  << " BOPInd: " << BOPInd
				  << std::endl;
		dump_charges();
		dump_per_ct_infos();
	}

	void load() {
		assert(root);
		load_attributes();
		load_charges();
		load_per_ct_infos();
	}

	void collect(std::set<std::string>& tariffs) const {
		for (auto it = PerCTInfos.begin(); it != PerCTInfos.end(); ++it) {
			(*it)->collect(tariffs);
		}
	}	

	void collect_service_dates(std::string& start, std::string& end, std::regex& charge_item) const {
		for (auto it = PerCTInfos.begin(); it != PerCTInfos.end(); ++it) {
			(*it)->collect_service_dates(start, end, charge_item);
		}
	}
	
	const char* Id;
	const char* MRKT;
	const char* SM;
	const char* BOPInd;
	XMLDn* Dn;
	std::set<XMLCharge*> Charges;
	std::set<XMLPerCTInfo*> PerCTInfos;
	
private:
	const rapidxml::xml_node<>* root;

	// mandatory values
	void load_attributes(){
		Id = find_attribute_value("Id", root);
		MRKT = find_attribute_value("MRKT", root);
		SM = find_attribute_value("SM", root);
		BOPInd = find_attribute_value("BOPInd", root);
	}

	void load_dn() {
		Dn = find_subnode<XMLDn>(root, "Dn");
	}
	
	void load_charges() {
		load_subnodes<XMLCharge>(root, "Charge", Charges);
	}

	void load_per_ct_infos()   {
		load_subnodes<XMLPerCTInfo>(root, "PerCTInfo", PerCTInfos);
	}
	
	void dump_dn() const {
		if (Dn) {
			Dn->dump();
		}
	}
	
	void dump_charges() const {
		const unsigned int n = Charges.size();
		if (n) {			
			std::cout << "Charges: " << "(" << n << ")" << std::endl;
			for (auto it = Charges.begin(); it != Charges.end(); ++it) {
				(*it)->dump();
			}
		}
	}

	void dump_per_ct_infos() const {
		const unsigned int n = PerCTInfos.size();
		if (n) {			
			std::cout << "PerCTInfos: " << "(" << n << ")" << std::endl;
			for (auto it = PerCTInfos.begin(); it != PerCTInfos.end(); ++it) {
				(*it)->dump();
			}
		}
	}	
	
};

#endif // __XML_CONTRACT_HPP__
