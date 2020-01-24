#ifndef __TXT_DOCUMENT_FACTORY_HPP__
#define __TXT_DOCUMENT_FACTORY_HPP__

#include <set>

#include "bill_document_factory.hpp"
#include "txt_document_invoice.hpp"

class TXTDocumentFactory {
public:
	TXTDocumentFactory() {}

	~TXTDocumentFactory() {}

	void dump() const {}
		
	BillDocument* make(std::map<std::string, BillDocument*>& bd) {
		return new TXTDocumentInvoice(bd);
	}	
};

#endif // __TXT_DOCUMENT_FACTORY_HPP__
