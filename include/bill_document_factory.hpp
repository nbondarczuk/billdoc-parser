#ifndef __BILL_DOCUMENT_FACTORY_HPP__
#define __BILL_DOCUMENT_FACTORY_HPP__

#include <map>
#include <string>

#include "bill_document.hpp"

// An abstract factory producing documents out of other ones
class BillDocumentFactory {
public:
  virtual ~BillDocumentFactory() = default;
  virtual BillDocument *
  make(const std::map<std::string, BillDocument *> &bd) = 0;
  virtual void dump() const = 0;
};

#endif // __BILL_DOCUMENT_FACTORY_HPP__
