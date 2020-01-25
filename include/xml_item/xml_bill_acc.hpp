#ifndef __XML_BILL_ACC_HPP__
#define __XML_BILL_ACC_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_addr.hpp"
#include "xml_customer.hpp"
#include "xml_fi_cont.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLBillAcc : public XMLItem {
public:
  XMLBillAcc() : root(0) {}

  XMLBillAcc(const rapidxml::xml_node<> *node) : root(node) { load(); }

  void dump() const {
    assert(root);
    std::cout << "XMLBillAcc:"
              << " Desc: " << Desc << " PayMeth: " << PayMeth
              << " BillMedium: " << BillMedium << " CopyNo: " << CopyNo
              << " State: " << State << std::endl;
    dump_customer();
    dump_addr();
    dump_fi_cont();
  }

  void load() {
    assert(root);
    load_attributes();
    load_customer();
    load_addr();
    load_fi_cont();
  }

  const char *Desc;
  const char *PayMeth;
  const char *BillMedium;
  const char *CopyNo;
  const char *State;
  XMLCustomer *Customer;
  XMLAddr *Addr;
  XMLFiCont *FiCont;

private:
  const rapidxml::xml_node<> *root;

  // mandatory values
  void load_attributes() {
    Desc = find_attribute_value("Desc", root);
    PayMeth = find_attribute_value("PayMeth", root);
    BillMedium = find_attribute_value("BillMedium", root);
    CopyNo = find_attribute_value("CopyNo", root);
    State = find_attribute_value("State", root);
  }

  // conditional value
  void load_customer() {
    Customer = find_subnode<XMLCustomer>(root, "Customer");
  }

  // conditional value
  void load_addr() { Addr = find_subnode<XMLAddr>(root, "Addr"); }

  // conditional value
  void load_fi_cont() { FiCont = find_subnode<XMLFiCont>(root, "FiCont"); }

  void dump_customer() const {
    if (Customer) {
      Customer->dump();
    }
  }

  void dump_addr() const {
    if (Addr) {
      Addr->dump();
    }
  }

  void dump_fi_cont() const {
    if (FiCont) {
      FiCont->dump();
    }
  }
};

#endif // __XML_BILL_ACC_HPP__
