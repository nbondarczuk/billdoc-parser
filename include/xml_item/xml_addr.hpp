#ifndef __XML_ADDR_HPP__
#define __XML_ADDR_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLAddr : public XMLItem {
public:
  XMLAddr() : root(0) {}

  XMLAddr(const rapidxml::xml_node<> *node) : root(node) { load(); }

  void dump() const {
    assert(root);
    std::cout << "Addr:"
              << " Name: " << Name << " City: " << City << " Zip: " << Zip
              << " Country: " << Country << " Line1: " << Line1
              << " Line2: " << Line2 << " Line3: " << Line3 << std::endl;
  }

  void load() {
    assert(root);
    load_attributes();
  }

  const char *Name;
  const char *City;
  const char *Zip;
  const char *Country;
  const char *Line1;
  const char *Line2;
  const char *Line3;
  const char *Line4;
  const char *Line5;
  const char *Line6;

private:
  const rapidxml::xml_node<> *root;

  // mandatory values
  void load_attributes() {
    Name = find_attribute_value_option("Name", root);
    City = find_attribute_value_option("City", root);
    Zip = find_attribute_value_option("Zip", root);
    Country = find_attribute_value_option("Country", root);
    Line1 = find_attribute_value_option("Line1", root);
    Line2 = find_attribute_value_option("Line2", root);
    Line3 = find_attribute_value_option("Line3", root);
    Line4 = find_attribute_value_option("Line4", root);
    Line5 = find_attribute_value_option("Line5", root);
    Line6 = find_attribute_value_option("Line6", root);
  }
};

#endif // __XML_ADDR_HPP__
