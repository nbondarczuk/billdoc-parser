#ifndef __XML_CHARGE_HPP__
#define __XML_CHARGE_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLCharge : public XMLItem {
public:
  XMLCharge() : root(0) {}

  XMLCharge(const rapidxml::xml_node<> *node) : root(node) {
    load_attributes();
  }

  void dump() const {
    assert(root);
    std::cout << "Charge:"
              << " Id: " << Id << " Amount: " << Amount
              << " CurrCode: " << CurrCode << " Type: " << Type << " PT: " << PT
              << std::endl;
  }

  void load() {
    assert(root);
    load_attributes();
  }

  const char *Id;
  const char *Amount;
  const char *CurrCode;
  const char *Type;
  const char *PT;

private:
  const rapidxml::xml_node<> *root;

  // mandatory values
  void load_attributes() {
    Id = find_attribute_value("Id", root);
    Amount = find_attribute_value("Amount", root);
    CurrCode = find_attribute_value("CurrCode", root);
    Type = find_attribute_value("Type", root);
    PT = find_attribute_value("PT", root);
  }
};

#endif // __XML_CHARGE_HPP__
