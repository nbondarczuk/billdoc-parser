#ifndef __XML_TAX_HPP__
#define __XML_TAX_HPP__

#include <assert.h>

#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_charge.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLTax : public XMLItem {
public:
  XMLTax() : root(0) {}

  XMLTax(const rapidxml::xml_node<> *node) : root(node) { load(); }

  ~XMLTax() { clear(); }

  void dump() const {
    assert(root);
    std::cout << "Tax:"
              << " ItemType: " << ItemType << " Name: " << Cat
              << " LegalCode: " << LegalCode << " Rate: " << Rate
              << " CalcMethod: " << CalcMethod << " Exception: " << Exemption
              << std::endl;
    dump_charges();
  }

  void load() {
    assert(root);
    load_attributes();
    load_charges();
  }

  const char *ItemType;
  const char *Cat;
  const char *Name;
  const char *LegalCode;
  const char *Rate;
  const char *CalcMethod;
  const char *Exemption;
  std::set<XMLCharge *> Charges;

  std::string FindTaxChargeAmount(const char *Id) {
    for (auto it = Charges.begin(); it != Charges.end(); ++it) {
      if (STREQ((*it)->Id, Id)) {
        return (*it)->Amount;
      }
    }
    throw std::invalid_argument(std::string("Can't find charge of id: ") + Id);
    return "";
  }

private:
  const rapidxml::xml_node<> *root;

  // mandatory values
  void load_attributes() {
    ItemType = find_attribute_value("ItemType", root);
    Cat = find_attribute_value("Cat", root);
    Name = find_attribute_value("Name", root);
    LegalCode = find_attribute_value("LegalCode", root);
    Rate = find_attribute_value("Rate", root);
    CalcMethod = find_attribute_value("CalcMethod", root);
    Exemption = find_attribute_value("Exemption", root);
  }

  // conditional values
  void load_charges() { load_subnodes<XMLCharge>(root, "Charge", Charges); }

  void dump_charges() const {
    const unsigned int n = Charges.size();
    if (n) {
      std::cout << "Charges: "
                << "(" << n << ")" << std::endl;
      for (auto it = Charges.begin(); it != Charges.end(); ++it) {
        (*it)->dump();
      }
    }
  }

  void clear() { clear_charges(); }

  void clear_charges() {
    for (auto it = Charges.begin(); it != Charges.end(); ++it) {
      delete *it;
    }
    Charges.clear();
  }
};

#endif // __XML_TAX_HPP__
