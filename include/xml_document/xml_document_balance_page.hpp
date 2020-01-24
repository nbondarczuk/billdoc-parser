#ifndef __XML_DOCUMENT_BALANCE_PAGE_HPP__
#define __XML_DOCUMENT_BALANCE_PAGE_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "xml_document.hpp"

class XMLDocumentBalancePage : public XMLDocument {
public:
	XMLDocumentBalancePage() : root(0) {}

	XMLDocumentBalancePage(rapidxml::xml_node<>* node) : root(node) {
		load();
	}	

	~XMLDocumentBalancePage() {
		clear();
	}
	
	virtual std::string id() const {
		return "Document.BalancePage";	
	}
	
	virtual XMLDocumentBalancePage* clone() const {
		XMLDocumentBalancePage* p = new XMLDocumentBalancePage(*this);
		return p;
	}

	virtual void reload() {
		const rapidxml::xml_node<>* document_root = get_document_root();
		root = document_root->first_node("BalancePage");
		load();
	}

	virtual void load() {
		assert(root);
		load_date_dict();
		load_charge_dict();
	}

	virtual void dump() const {
		assert(root);
		dump_date_dict();
		dump_charge_dict();		
	}

	std::map<const char *, XMLDate*> DateDict;
	std::map<const char *, XMLCharge*> ChargeDict;
	
private:
	rapidxml::xml_node<> *root;

	void load_date_dict() {
		load_subnodes_dict<XMLDate>(root, "Date", "Type", DateDict);
	}
	
	void load_charge_dict() {
		load_subnodes_dict<XMLCharge>(root, "Charge", "Id", ChargeDict);
	};

	void dump_date_dict() const {
		const unsigned int n = DateDict.size();
		if (n) {			
			std::cout << "Dates: " << "(" << n << ")" << std::endl;
			for (auto it = DateDict.begin(); it != DateDict.end(); ++it) {
				it->second->dump();
			}
		}
	}

	void dump_charge_dict() const {
		const unsigned int n = ChargeDict.size();
		if (n) {			
			std::cout << "Charges: " << "(" << n << ")" << std::endl;
			for (auto it = ChargeDict.begin(); it != ChargeDict.end(); ++it) {
				it->second->dump();
			}
		}
	}

	void clear () {
		clear_date_dict();
		clear_charge_dict();
	}
	
	void clear_date_dict() {
		for (auto it = DateDict.begin(); it != DateDict.end(); ++it) {
			delete it->second;
		}
		DateDict.clear();
	}

	void clear_charge_dict() {
		for (auto it = ChargeDict.begin(); it != ChargeDict.end(); ++it) {
			delete it->second;
		}
		ChargeDict.clear();
	}	
};

#endif // __XML_DOCUMENT_BALANCE_PAGE_HPP__
