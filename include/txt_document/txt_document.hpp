#ifndef __TXT_DOCUMENT_HPP__
#define __TXT_DOCUMENT_HPP__

#include "bill_document.hpp"

class TXTDocument : public BillDocument {
public:
	TXTDocument() {}
	
	~TXTDocument() {}
	
	virtual const char* id() {
		return "TXTDocument";
	}
	
	virtual const char* name() {
		return 0;
	}
	
	virtual BillDocument* clone() {
		return 0;
	}
	
	virtual void dump() {}
};	

#endif // __TXT_DOCUMENT_HPP__
