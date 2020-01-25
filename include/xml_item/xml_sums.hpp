#ifndef __XML_SUMS_HPP__
#define __XML_SUMS_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "rapidxml.hpp"
#include "xml_charge.hpp"
#include "xml_item.hpp"

class XMLSums : public XMLItem {
public:
  XMLSums() : root(0) {}

  XMLSums(const rapidxml::xml_node<> *node) : root(node) { load(); }

  ~XMLSums() { clear(); }

  void dump() const {
    assert(root);
    std::cout << "Sums: " << std::endl;
    dump_sums();
  }

  void load() {
    assert(root);
    load_sums();
  }

  std::set<XMLCharge *> Charges;

private:
  const rapidxml::xml_node<> *root;

  // conditional values
  void load_sums() { load_subnodes<XMLCharge>(root, "Charge", Charges); }

  void dump_sums() const {
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

#endif // __XML_SUMS_HPP__
