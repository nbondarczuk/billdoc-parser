#ifndef __XML_CUSTOMER_HPP__
#define __XML_CUSTOMER_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLCustomer : public XMLItem {
public:
  XMLCustomer() : root(0) {}

  XMLCustomer(const rapidxml::xml_node<> *node) : root(node) { load(); }

  void dump() const {
    assert(root);
    std::cout << "Customer:"
              << " Id: " << Id << " SocSecNo: " << SocSecNo
              << " DrivLicNo: " << DrivLicNo << std::endl;
  }

  void load() {
    assert(root);
    load_attributes();
  }

  const char *Id;
  const char *SocSecNo;
  const char *DrivLicNo;

private:
  const rapidxml::xml_node<> *root;

  // mandatory values
  void load_attributes() {
    Id = find_attribute_value("Id", root);
    SocSecNo = find_attribute_value("SocSecNo", root);
    DrivLicNo = find_attribute_value("DrivLicNo", root);
  }
};

#endif // __XML_CUSTOMER_HPP__
