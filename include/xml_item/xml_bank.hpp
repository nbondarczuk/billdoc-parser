#ifndef __XML_BANK_HPP__
#define __XML_BANK_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLBank : public XMLItem {
public:
  XMLBank() : root(0) {}

  XMLBank(const rapidxml::xml_node<> *node) : root(node) { load(); }

  void dump() const {
    assert(root);
    std::cout << "Bank:"
              << " Code: " << Code << " Name: " << Name << " Branch: " << Branch
              << std::endl;
  }

  void load() {
    assert(root);
    load_attributes();
  }

  const char *Code;
  const char *Name;
  const char *Branch;

private:
  const rapidxml::xml_node<> *root;

  // mandatory values
  void load_attributes() {
    Code = find_attribute_value("Code", root);
    Name = find_attribute_value("Name", root);
    Branch = find_attribute_value("Branch", root);
  }
};

#endif // __XML_BANK_HPP__
