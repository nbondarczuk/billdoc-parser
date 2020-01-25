#ifndef __XML_CUST_REF_HPP__
#define __XML_CUST_REF_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_addr.hpp"
#include "xml_charge.hpp"
#include "xml_contract.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLCustRef : public XMLItem {
public:
  XMLCustRef() : root(0) {}

  XMLCustRef(const rapidxml::xml_node<> *node) : root(node) { load(); }

  void dump() const {
    assert(root);
    std::cout << "CustRef:"
              << " Id: " << Id << " CustCode: " << CustCode
              << " Reseller: " << Reseller << " PartyType: " << PartyType
              << std::endl;
    dump_addr();
    dump_charges();
    dump_contracts();
  }

  void load() {
    assert(root);
    load_attributes();
    load_addr();
    load_charges();
    load_contracts();
  }

  void collect(std::set<std::string> &tariffs) const {
    for (auto it = Contracts.begin(); it != Contracts.end(); ++it) {
      (*it)->collect(tariffs);
    }
  }

  void collect_service_dates(std::string &start, std::string &end,
                             std::regex &charge_item) const {
    for (auto it = Contracts.begin(); it != Contracts.end(); ++it) {
      (*it)->collect_service_dates(start, end, charge_item);
    }
  }

  const char *Id;
  const char *CustCode;
  const char *Reseller;
  const char *PartyType;
  XMLAddr *Addr;
  std::set<XMLCharge *> Charges;
  std::set<XMLContract *> Contracts;

private:
  const rapidxml::xml_node<> *root;

  // mandatory values
  void load_attributes() {
    Id = find_attribute_value("Id", root);
    CustCode = find_attribute_value("CustCode", root);
    Reseller = find_attribute_value("Reseller", root);
    PartyType = find_attribute_value("PartyType", root);
  }

  void load_addr() { Addr = find_subnode<XMLAddr>(root, "Addr"); }

  void load_charges() { load_subnodes<XMLCharge>(root, "Charge", Charges); }

  void load_contracts() {
    load_subnodes<XMLContract>(root, "Contract", Contracts);
  }

  void dump_addr() const {
    if (Addr) {
      Addr->dump();
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

  void dump_contracts() const {
    const unsigned int n = Contracts.size();
    if (n) {
      std::cout << "Contracts: "
                << "(" << n << ")" << std::endl;
      for (auto it = Contracts.begin(); it != Contracts.end(); ++it) {
        (*it)->dump();
      }
    }
  }
};

#endif // __XML_CUST_REF_HPP__
