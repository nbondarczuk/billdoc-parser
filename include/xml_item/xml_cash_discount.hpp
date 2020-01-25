#ifndef __XML_CASH_DISCOUNT_HPP__
#define __XML_CASH_DISCOUNT_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_charge.hpp"
#include "xml_date.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLCashDiscount : public XMLItem {
public:
  XMLCashDiscount() : root(0) {}

  XMLCashDiscount(const rapidxml::xml_node<> *node) : root(node) { load(); }

  void dump() const {
    assert(root);
    std::cout << "CashDiscount: "
              << "Days: " << Days << std::endl;
    Charge.dump();
    Date.dump();
  }

  void load() {
    assert(root);
    load_attributes();
    load_charges();
    load_dates();
  }

  const char *Days;
  XMLCharge Charge;
  XMLDate Date;

private:
  const rapidxml::xml_node<> *root;

  // mandatory value
  void load_attributes() { Days = find_attribute_value("Days", root); }

  // mandatory value
  void load_charges() {
    rapidxml::xml_node<> *node = root->first_node("Charge");
    Charge = XMLCharge(node);
  }

  // mandatory value
  void load_dates() {
    rapidxml::xml_node<> *node = root->first_node("Date");
    Date = XMLDate(node);
  }
};

#endif // __XML_CASH_DISCOUNT_HPP__
