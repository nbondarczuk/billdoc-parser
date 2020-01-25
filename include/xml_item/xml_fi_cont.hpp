#ifndef __XML_FI_CONT_HPP__
#define __XML_FI_CONT_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_account.hpp"
#include "xml_bank.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLFiCont : public XMLItem {
public:
  XMLFiCont() : root(0) {}

  XMLFiCont(const rapidxml::xml_node<> *node) : root(node) { load(); }

  void dump() const {
    assert(root);
    std::cout << "FiCont:" << std::endl;
    dump_account();
    dump_bank();
  }

  void load() {
    assert(root);
    load_account();
    load_bank();
  }

  XMLAccount *Account;
  XMLBank *Bank;

private:
  const rapidxml::xml_node<> *root;

  // optional value
  void load_account() { Account = find_subnode<XMLAccount>(root, "Account"); }

  // optional value
  void load_bank() { Bank = find_subnode<XMLBank>(root, "Bank"); }

  void dump_account() const {
    if (Account) {
      Account->dump();
    }
  }

  void dump_bank() const {
    if (Bank) {
      Bank->dump();
    }
  }
};

#endif // __XML_FI_CONT_HPP__
