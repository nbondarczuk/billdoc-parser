#ifndef __XML_ITEM_HPP__
#define __XML_ITEM_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xmlutl.hpp"

// imposes Dumpability and Loadability on all sub-items
// Dumpability and Loadibility assume that the object is initiated from valid
// root node of XML sub-tree
class XMLItem {
public:
  virtual void dump() const = 0;
  virtual void load() = 0;
};

#endif // __XML_ITEM_HPP__
