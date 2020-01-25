#ifndef __XML_PART_HPP__
#define __XML_PART_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLPart : public XMLItem {
public:
  XMLPart() : root(0) {}

  XMLPart(const rapidxml::xml_node<> *node) : root(node) { load(); }

  void dump() const {
    assert(root);
    std::cout << "Part:"
              << " File: " << File << " LinkType: " << LinkType
              << " DocType: " << DocType << " Format: " << Format << std::endl;
  }

  void load() {
    assert(root);
    load_attributes();
  }

  const char *File;
  const char *LinkType;
  const char *DocType;
  const char *Format;

private:
  const rapidxml::xml_node<> *root;

  // mandatory values
  void load_attributes() {
    File = find_attribute_value("File", root);
    LinkType = find_attribute_value("LinkType", root);
    DocType = find_attribute_value("DocType", root);
    Format = find_attribute_value("Format", root);
  }
};

#endif // __XML_PART_HPP__
