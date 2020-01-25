#ifndef __XML_ATT_HPP__
#define __XML_ATT_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLAtt : public XMLItem {
public:
  XMLAtt() : root(0) {}

  XMLAtt(const rapidxml::xml_node<> *node) : root(node) { load(); }

  void dump() const {
    assert(root);
    std::cout << "Att:"
              << " Ty: " << Ty << " Id: " << Id << std::endl;
  }

  void load() {
    assert(root);
    load_attributes();
  }

  const char *Ty;
  const char *Id;

private:
  const rapidxml::xml_node<> *root;

  // mandatory values
  void load_attributes() {
    Ty = find_attribute_value("Ty", root);
    Id = find_attribute_value("Id", root);
  }
};

#endif // __XML_ATT_HPP__
