#ifndef __XML_DOCUMENT_SUMMARY_HPP__
#define __XML_DOCUMENT_SUMMARY_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "xml_document.hpp"
#include "xml_sums.hpp"
#include "xml_cust_ref.hpp"

class XMLDocumentSummary : public XMLDocument {
public:
	XMLDocumentSummary() : root(0) {}

	XMLDocumentSummary(rapidxml::xml_node<>* node) : root(node) {
		load();
	}	

	~XMLDocumentSummary() {}

	virtual std::string id() const {
		return "Document.Summary";	
	}
	
	virtual XMLDocumentSummary* clone() const {
		XMLDocumentSummary* p = new XMLDocumentSummary(*this);
		return p;
	}
	
	virtual void reload() {
		const rapidxml::xml_node<>* document_root = get_document_root();
		root = document_root->first_node("Summary");
		load();
	}

	virtual void load() {
		assert(root);
		load_sums();
		load_cust_refs();
	}

	virtual void dump() const {
		assert(root);
		dump_sums();
		dump_cust_refs();
	}

	XMLSums* Sums;
	std::set<XMLCustRef*> CustRefs;

	XMLCustRef* FindCustRef(const char* custCode) const {
		XMLCustRef* found = 0;
		for (auto it = CustRefs.begin(); it != CustRefs.end() && !found; ++it) {
			if (STREQ((*it)->CustCode, custCode)) {
				found = *it;
			}
		}

		if (!found) {
			std::invalid_argument(std::string("Can't find CustRef by: ") + custCode);
		}
		
		return found;
	}

	void collect(std::set<std::string>& tariffs) const {
		for (auto it = CustRefs.begin(); it != CustRefs.end(); ++it) {
			(*it)->collect(tariffs);
		}		
	}

	void collect_service_dates(std::string& start, std::string& end, std::regex& charge_item) const {
		for (auto it = CustRefs.begin(); it != CustRefs.end(); ++it) {
			(*it)->collect_service_dates(start, end, charge_item);
		}		
	}
	
private:
	rapidxml::xml_node<> *root;

	void load_sums() {
		Sums = find_subnode<XMLSums>(root, "Sums");
	}

	void load_cust_refs() {
		load_subnodes<XMLCustRef>(root, "CustRef", CustRefs);
	}
	
	void dump_sums() const {
		if (Sums) {
			Sums->dump();
		}	
	}

	void dump_cust_refs() const {
		const unsigned int n = CustRefs.size();
		if (n) {
			std::cout << "CustRefs: " << "(" << n << ")" << std::endl;
			for (auto it = CustRefs.begin(); it != CustRefs.end(); ++it) {
				(*it)->dump();
			}
		}
	}
};

#endif // __XML_DOCUMENT_SUMMARY_HPP__

	
