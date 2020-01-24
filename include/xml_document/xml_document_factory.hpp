#ifndef __XML_DOCUMENT_FACTORY_HPP__
#define __XML_DOCUMENT_FACTORY_HPP__

#include <cstring>
#include <iostream>
#include <map>
#include <memory>

#include "xml_document.hpp"
#include "xml_document_invoice.hpp"
#include "xml_document_summary.hpp"
#include "xml_document_address_page.hpp"
#include "xml_document_balance_page.hpp"
#include "xml_document_call_details.hpp"
#include "xml_document_complement.hpp"
#include "xml_document_legend.hpp"
#include "xml_document_contracts.hpp"
#include "xml_document_invoice_info.hpp"
#include "xml_envelope.hpp"

//
// Makes specific document using generic XML structure
// by recognizing document types, cloning and, as side effect, loading it.
//
class XMLDocumentFactory {
public:
	// factory must be inistized before usage with table of clones
	XMLDocumentFactory() {
		init_models();
	}

	~XMLDocumentFactory() {
		clear();
	}

	// provide info about document table
	void dump() const {
		for (auto it = models.begin(); it != models.end(); ++it) {
			std::cout << it->first << ": " << it->second->id() << std::endl;
		}	
	}
	
	// make concrete instance of specifc document using parsed generic document
	XMLDocument* make(const char* fn) const {		
		// generic XML structure used to determine document model template
		XMLDocument* d = new XMLDocument(fn);
			
		// create specific document replacing base and rebuilding it
		XMLDocument* model = 0;
		ModelDictConstIter it = models.find(d->id());
		if (it != models.end()) {
			model = it->second;
		} else {
			throw std::invalid_argument(std::string("Can't find model for: ") + d->id());
		}
		
		XMLDocument* copy = model->clone();
		copy->rebase(d);
		copy->reload();
		delete d; // empty now
		
		return copy;
	}
	
private:
	typedef std::map<const std::string, XMLDocument*> ModelDict;
	typedef std::map<const std::string, XMLDocument*>::const_iterator ModelDictConstIter;
	ModelDict models;

	// register all known document models
	void init_models() {
		models.insert(std::pair<const std::string, XMLDocument*>("Document.Invoice", new XMLDocumentInvoice()));
		models.insert(std::pair<const std::string, XMLDocument*>("Document.AddressPage", new XMLDocumentAddressPage()));
		models.insert(std::pair<const std::string, XMLDocument*>("Document.BalancePage", new XMLDocumentBalancePage()));
		models.insert(std::pair<const std::string, XMLDocument*>("Document.Legend", new XMLDocumentLegend()));
		models.insert(std::pair<const std::string, XMLDocument*>("Document.CallDetails", new XMLDocumentCallDetails()));
		models.insert(std::pair<const std::string, XMLDocument*>("Document.Summary", new XMLDocumentSummary()));		
		models.insert(std::pair<const std::string, XMLDocument*>("Document.Complement", new XMLDocumentComplement()));
		models.insert(std::pair<const std::string, XMLDocument*>("Document.Contracts", new XMLDocumentContracts()));
		models.insert(std::pair<const std::string, XMLDocument*>("Document.InvoiceInfo", new XMLDocumentInvoiceInfo()));
		models.insert(std::pair<const std::string, XMLDocument*>("Envelope", new XMLEnvelope()));
	}

	void clear() {
		for (auto it = models.begin(); it != models.end(); ++it) {
			delete it->second;
		}
		models.clear();
	}	
};

#endif // __XML_DOCUMENT_FACTORY_HPP__
