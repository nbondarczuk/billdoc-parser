#ifndef __XML_DOCUMENT_ADDRESS_PAGE_HPP__
#define __XML_DOCUMENT_ADDRESS_PAGE_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "xml_document.hpp"
#include "xml_inv_party.hpp"
#include "xml_bill_acc.hpp"

class XMLDocumentAddressPage : public XMLDocument {
public:
	XMLDocumentAddressPage() {}
	
	virtual std::string id() const {
		return "Document.AddressPage";	
	}

	virtual XMLDocumentAddressPage* clone() const {
		XMLDocumentAddressPage* p = new XMLDocumentAddressPage(*this);
		return p;
	}

	virtual void reload() {
		XMLDocument::reload();
		const rapidxml::xml_node<>* document_root = get_document_root();
		root = document_root->first_node("AddressPage");
		load();
	}

	virtual void load () {
		assert(root);		
		load_inv_party();
		load_bill_acc();
	}

	virtual void dump() const {
		XMLDocument::dump();		
		dump_inv_party();
		dump_bill_acc();
	}

	XMLInvParty* InvParty;
	XMLBillAcc* BillAcc;

private:
	rapidxml::xml_node<> *root;

	void load_inv_party() {
		InvParty = find_subnode<XMLInvParty>(root, "InvParty");
	}

	void load_bill_acc() {
		BillAcc = find_subnode<XMLBillAcc>(root, "BillAcc");
	}
	
	void dump_inv_party() const {
		if (InvParty) {
			InvParty->dump();
		}
	}
	
	void dump_bill_acc() const {
		if (BillAcc) {
			BillAcc->dump();
		}		
	}
};

#endif // __XML_DOCUMENT_ADDRESS_PAGE_HPP__
