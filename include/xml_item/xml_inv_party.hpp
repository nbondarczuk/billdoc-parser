#ifndef __XML_INV_PARTY_HPP__
#define __XML_INV_PARTY_HPP__

#include <assert.h>

#include <iostream>
#include <fstream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xmlutl.hpp"
#include "xml_item.hpp"
#include "xml_addr.hpp"
#include "xml_fi_cont.hpp"
#include "xml_cccontact.hpp"

class XMLInvParty : public XMLItem {
public:
	XMLInvParty() : root(0) {}
	
	XMLInvParty(const rapidxml::xml_node<>* node) : root(node) {
		load();
	}
	
	void dump() const {
		assert(root);
		std::cout << "XMLInvParty:"
				  << " VATRegNo: " <<  VATRegNo
				  << std::endl;
		dump_addr();
		dump_fi_cont();
		dump_cccontact();		
	}
	
	void load() {
		assert(root);
		load_attributes();
		load_addr();
		load_fi_cont();
		load_cccontact();
	}

	const char* VATRegNo;
	XMLAddr* Addr;
	XMLFiCont* FiCont;
	XMLCCContact* CCContact;

private:
	const rapidxml::xml_node<>* root;

	// mandatory values
	void load_attributes(){
		VATRegNo = find_attribute_value("VATRegNo", root);
	}

	void load_addr() {
		Addr = find_subnode<XMLAddr>(root, "Addr");
	}
	
	void load_fi_cont() {
		FiCont = find_subnode<XMLFiCont>(root, "FiCont");
	}
	
	void load_cccontact() {
		CCContact = find_subnode<XMLCCContact>(root, "CCContact");
	}

	void dump_addr() const {
		if (Addr) {
			Addr->dump();
		}
	}
	
	void dump_fi_cont() const {
		if (FiCont) {
			FiCont->dump();
		}
	}

	void dump_cccontact() const {
		if (CCContact) {
			CCContact->dump();
		}
	}
};

#endif // __XML_INV_PARTY_HPP__
