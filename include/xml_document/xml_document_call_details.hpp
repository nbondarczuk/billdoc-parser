#ifndef __XML_DOCUMENT_CALL_DETAILS_HPP__
#define __XML_DOCUMENT_CALL_DETAILS_HPP__

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "xml_call.hpp"
#include "xml_document.hpp"

class XMLDocumentCallDetails : public XMLDocument {
public:
  XMLDocumentCallDetails() : root(0) {}

  XMLDocumentCallDetails(rapidxml::xml_node<> *node) : root(node) { load(); }

  ~XMLDocumentCallDetails() {}

  virtual std::string id() const { return "Document.CallDetails"; }

  virtual XMLDocumentCallDetails *clone() const {
    XMLDocumentCallDetails *p = new XMLDocumentCallDetails(*this);
    return p;
  }

  virtual void reload() {
    const rapidxml::xml_node<> *document_root = get_document_root();
    root = document_root->first_node("CallDetails");
    load();
  }

  virtual void load() {
    assert(root);
    load_calls();
  }

  virtual void dump() const {
    assert(root);
    dump_calls();
  }

  std::set<XMLCall *> Calls;

private:
  rapidxml::xml_node<> *root;

  void load_calls() { load_subnodes<XMLCall>(root, "Call", Calls); }

  void dump_calls() const {
    const unsigned int n = Calls.size();
    if (n) {
      std::cout << "Calls: "
                << "(" << n << ")" << std::endl;
      unsigned int i = 0;
      for (auto it = Calls.begin(); it != Calls.end(); ++it) {
        std::cout << "[";
        std::cout << i++;
        std::cout << "]";
        (*it)->dump();
      }
    }
  }
};

#endif // __XML_DOCUMENT_CALL_DETAILS_HPP__
