#ifndef __XML_TYPE_DESC_HPP__
#define __XML_TYPE_DESC_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLTypeDesc : public XMLItem {
public:
  XMLTypeDesc() : root(0) {}

  XMLTypeDesc(const rapidxml::xml_node<> *node) : root(node) { load(); }

  void dump() const {
    assert(root);
    std::cout << "TypeDesc:"
              << " Type: " << Type << " Id: " << Id << " PKey: " << PKey
              << " ShDes: " << ShDes << " LongDes: " << LongDes << std::endl;
  }

  void load() {
    assert(root);
    load_attributes();
  }

  const char *getLongDes() const { return LongDes; }

  const char *Type;
  const char *Id;
  const char *PKey;
  const char *ShDes;
  const char *LongDes;

private:
  const rapidxml::xml_node<> *root;

  // mandatory values
  void load_attributes() {
    Type = find_attribute_value("Type", root);
    Id = find_attribute_value("Id", root);
    PKey = find_attribute_value("PKey", root);
    ShDes = find_attribute_value("ShDes", root);
    LongDes = find_attribute_value("LongDes", root);
  }
};

#endif // __XML_TYPE_DESC_HPP__
