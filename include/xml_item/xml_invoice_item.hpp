#ifndef __XML_INVOICE_ITEM_HPP__
#define __XML_INVOICE_ITEM_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include "amtutl.hpp"
#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_agg_set.hpp"
#include "xml_charge.hpp"
#include "xml_item.hpp"
#include "xml_price.hpp"
#include "xml_srv_params.hpp"
#include "xml_tax.hpp"
#include "xmlutl.hpp"

class XMLInvoiceItem : public XMLItem {
public:
  XMLInvoiceItem() : root(0) {}

  XMLInvoiceItem(const rapidxml::xml_node<> *node)
      : root(node), AggSet(0), Price(0) {
    load();
  }

  ~XMLInvoiceItem() { clear(); }

  void dump() const {
    assert(root);
    std::cout << "InvoiceItem:"
              << " NumItem: " << NumItem << " ArticleString: " << ArticleString
              << " CT: " << CT << " CollInd: " << CollInd << std::endl;
    dump_agg_set();
    dump_srv_params();
    dump_charges();
    dump_price();
    dump_taxes();
  }

  void load() {
    assert(root);
    load_attributes();
    load_agg_set();
    load_srv_params();
    load_charges();
    load_price();
    load_taxes();
  }

  template <int N>
  void collect(std::set<std::string> &unique, std::regex &pattern) const {
    if (std::regex_match(ArticleString, pattern)) {
      std::vector<std::string> prefix = split<N>(ArticleString, '.');
      unique.insert(join<N>(prefix, '.'));
    }
  }

  void collect_charge(long &total, const char *Id, std::regex &pattern) const {
    if (std::regex_match(ArticleString, pattern)) {
      std::string amount(FindChargeAmount(Id));
      total += GetDecimalAmount<2>(amount);
    }
  }

  void collect_charge_tax(long &total, long &taxRate, const char *Id,
                          std::regex &pattern) const {}

  bool collect_price(long &price, std::regex &pattern) const {
    if (std::regex_match(ArticleString, pattern)) {
      if (Price) {
        std::string amount(Price->Price);
        price = GetDecimalAmount<2>(amount);
        return true;
      }
    }

    return false;
  }

  std::string FindChargeAmount(const char *Id) const {
    for (auto it = Charges.begin(); it != Charges.end(); ++it) {
      if (STREQ((*it)->Id, Id)) {
        return (*it)->Amount;
      }
    }

    for (auto it = Taxes.begin(); it != Taxes.end(); ++it) {
      try {
        return (*it)->FindTaxChargeAmount(Id);
      } catch (std::invalid_argument &e) {
      }
    }

    throw std::invalid_argument(std::string("Can't find charge of id: ") + Id);
    return "";
  }

  const char *NumItem;
  const char *ArticleString;
  const char *CT;
  const char *CollInd;
  XMLAggSet *AggSet;
  std::set<XMLSrvParams *> SrvParams;
  std::set<XMLCharge *> Charges;
  XMLPrice *Price;
  std::set<XMLTax *> Taxes;

private:
  const rapidxml::xml_node<> *root;

  // mandatory values
  void load_attributes() {
    NumItem = find_attribute_value("NumItem", root);
    ArticleString = find_attribute_value("ArticleString", root);
    CT = find_attribute_value("CT", root);
    CollInd = find_attribute_value("CollInd", root);
  }

  // optional value
  void load_agg_set() { AggSet = find_subnode<XMLAggSet>(root, "AggSet"); }

  // conditional set of values
  void load_srv_params() {
    load_subnodes<XMLSrvParams>(root, "SrvParams", SrvParams);
  }

  // mandatory set of values
  void load_charges() { load_subnodes<XMLCharge>(root, "Charge", Charges); }

  // optional value
  void load_price() { Price = find_subnode<XMLPrice>(root, "Price"); }

  // conditional set of values
  void load_taxes() { load_subnodes<XMLTax>(root, "Tax", Taxes); }

  void dump_agg_set() const {
    if (AggSet) {
      AggSet->dump();
    }
  }

  void dump_srv_params() const {
    const unsigned int n = SrvParams.size();
    if (n) {
      std::cout << "SrvParams: "
                << "(" << n << ")" << std::endl;
      for (auto it = SrvParams.begin(); it != SrvParams.end(); ++it) {
        (*it)->dump();
      }
    }
  }

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

  void dump_price() const {
    if (Price) {
      Price->dump();
    }
  }

  void dump_taxes() const {
    const unsigned int n = Taxes.size();
    if (n) {
      std::cout << "Taxes: "
                << "(" << n << ")" << std::endl;
      for (auto it = Taxes.begin(); it != Taxes.end(); ++it) {
        (*it)->dump();
      }
    }
  }

  void clear() {
    clear_agg_set();
    clear_srv_params();
    clear_charges();
    clear_price();
    clear_taxes();
  }

  void clear_agg_set() {
    if (AggSet) {
      delete AggSet;
    }
  }

  void clear_srv_params() {
    for (auto it = SrvParams.begin(); it != SrvParams.end(); ++it) {
      delete *it;
    }
    SrvParams.clear();
  }

  void clear_charges() {
    for (auto it = Charges.begin(); it != Charges.end(); ++it) {
      delete *it;
    }
    Charges.clear();
  }

  void clear_price() {
    if (Price) {
      delete Price;
    }
  }

  void clear_taxes() {
    for (auto it = Taxes.begin(); it != Taxes.end(); ++it) {
      delete *it;
    }
    Taxes.clear();
  }
};

#endif // __XML_INVOICE_ITEM_HPP__
