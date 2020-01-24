#ifndef __BILL_DOCUMENT_HPP__
#define __BILL_DOCUMENT_HPP__

#include "rapidxml.hpp"

// A billing document interface: can be identified, has a name, clonable,
// reloadsable from xml, dumpable
class BillDocument {
public:
	virtual ~BillDocument() = default;	
	virtual std::string id() const = 0;
	virtual BillDocument* clone() const = 0;
	virtual void reload() = 0;
	virtual void load() = 0;
	virtual void dump() const = 0;
};	

#endif // __BILL_DOCUMENT_HPP__
