#ifndef __XML_DOCUMENT_INVOICE_INFO_HPP__
#define __XML_DOCUMENT_INVOICE_INFO_HPP__

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "xml_adv_txt.hpp"
#include "xml_document.hpp"

class XMLDocumentInvoiceInfo : public XMLDocument {
public:
  XMLDocumentInvoiceInfo() : root(0) {}

  XMLDocumentInvoiceInfo(rapidxml::xml_node<> *node) : root(node) { load(); }

  ~XMLDocumentInvoiceInfo() {}

  virtual std::string id() const { return "Document.InvoiceInfo"; }

  virtual XMLDocumentInvoiceInfo *clone() const {
    XMLDocumentInvoiceInfo *p = new XMLDocumentInvoiceInfo(*this);
    return p;
  }

  virtual void reload() {
    const rapidxml::xml_node<> *document_root = get_document_root();
    root = document_root->first_node("InvoiceInfo");
    load();
  }

  virtual void load() {
    assert(root);
    load_adv_txt();
  }

  virtual void dump() const {
    assert(root);
    dump_adv_txt();
  }

  std::set<XMLAdvTxt *> AdvTxt;

private:
  rapidxml::xml_node<> *root;

  void load_adv_txt() { load_subnodes<XMLAdvTxt>(root, "AdvTxt", AdvTxt); }

  void dump_adv_txt() const {
    const unsigned int n = AdvTxt.size();
    if (n) {
      std::cout << "AdvTxt: "
                << "(" << n << ")" << std::endl;
      for (auto it = AdvTxt.begin(); it != AdvTxt.end(); ++it) {
        (*it)->dump();
      }
    }
  }
};

#endif // __XML_DOCUMENT_INVOICE_INFO_HPP__
