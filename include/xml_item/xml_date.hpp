#ifndef __XML_DATE_HPP__
#define __XML_DATE_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLDate : public XMLItem {
public:
  XMLDate() : root(0) {}

  XMLDate(const rapidxml::xml_node<> *node) : root(node) { load(); }

  void dump() const {
    assert(root);
    std::cout << "Date:"
              << " Type: " << Type << " Date: " << Date << std::endl;
  }

  void load() {
    assert(root);
    load_attributes();
  }

  const char *Type;
  const char *Date;
  const char *HH;
  const char *MM;
  const char *SS;

private:
  const rapidxml::xml_node<> *root;

  // mandatory values
  void load_attributes() {
    Type = find_attribute_value("Type", root);
    Date = find_attribute_value("Date", root);
  }
};

#endif // __XML_DATE_HPP__
