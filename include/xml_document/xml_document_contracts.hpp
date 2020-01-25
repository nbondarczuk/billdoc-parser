#ifndef __XML_DOCUMENT_CONTRACTS_HPP__
#define __XML_DOCUMENT_CONTRACTS_HPP__

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "xml_document.hpp"

class XMLDocumentContracts : public XMLDocument {
public:
  XMLDocumentContracts() : root(0) {}

  XMLDocumentContracts(rapidxml::xml_node<> *node) : root(node) { load(); }

  ~XMLDocumentContracts() {}

  virtual std::string id() const { return "Document.Contracts"; }

  virtual XMLDocumentContracts *clone() const {
    XMLDocumentContracts *p = new XMLDocumentContracts(*this);
    return p;
  }

  virtual void reload() {
    const rapidxml::xml_node<> *document_root = get_document_root();
    root = document_root->first_node("Contracts");
    load();
  }

  virtual void load() {
    // assert(root);
  }

  virtual void dump() const {
    // assert(root);
  }

private:
  rapidxml::xml_node<> *root;
};

#endif // __XML_DOCUMENT_CONTRACTS_HPP__
