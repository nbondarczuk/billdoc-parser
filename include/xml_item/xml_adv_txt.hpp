#ifndef __XML_ADV_TXT_HPP__
#define __XML_ADV_TXT_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLAdvTxt : public XMLItem {
public:
  XMLAdvTxt() : root(0) {}

  XMLAdvTxt(const rapidxml::xml_node<> *node) : root(node) { load(); }

  void dump() const {
    assert(root);
    std::cout << "AdvTxt:" << AdvTxt << std::endl;
  }

  void load() {
    assert(root);
    load_text();
  }

  const char *AdvTxt;

private:
  const rapidxml::xml_node<> *root;

  void load_text() { AdvTxt = root->value(); }
};

#endif // __XML_ADV_TXT_HPP__
