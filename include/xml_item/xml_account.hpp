#ifndef __XML_ACCOUNT_HPP__
#define __XML_ACCOUNT_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLAccount : public XMLItem {
public:
  XMLAccount() : root(0) {}

  XMLAccount(const rapidxml::xml_node<> *node) : root(node) { load(); }

  void dump() const {
    assert(root);
    std::cout << "Account:"
              << " Num: " << Num << " HolderName1: " << HolderName1
              << " HolderName2: " << HolderName2 << std::endl;
  }

  void load() {
    assert(root);
    load_attributes();
  }

  const char *Num;
  const char *HolderName1;
  const char *HolderName2;

private:
  const rapidxml::xml_node<> *root;

  // mandatory values
  void load_attributes() {
    Num = find_attribute_value("Num", root);
    HolderName1 = find_attribute_value("HolderName1", root);
    HolderName2 = find_attribute_value("HolderName2", root);
  }
};

#endif // __XML_ACCOUNT_HPP__
