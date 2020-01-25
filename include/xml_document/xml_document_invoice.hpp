#ifndef __XML_DOCUMENT_INVOICE_HPP__
#define __XML_DOCUMENT_INVOICE_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_cash_discount.hpp"
#include "xml_date.hpp"
#include "xml_document.hpp"
#include "xml_invoice_item.hpp"
#include "xml_invoice_totals.hpp"
#include "xml_tax.hpp"
#include "xmlutl.hpp"

class XMLDocumentInvoice : public XMLDocument {
public:
  XMLDocumentInvoice() : root(0) {}

  XMLDocumentInvoice(rapidxml::xml_node<> *node) : root(node) { load(); }

  ~XMLDocumentInvoice() { clear(); }

  virtual std::string id() const { return "Document.Invoice"; }

  virtual XMLDocumentInvoice *clone() const {
    XMLDocumentInvoice *p = new XMLDocumentInvoice(*this);
    return p;
  }

  virtual void reload() {
    XMLDocument::reload();
    const rapidxml::xml_node<> *document_root = get_document_root();
    root = document_root->first_node("Invoice");
    load();
  }

  virtual void load() {
    assert(root);
    load_attributes();
    load_dates();
    load_cash_discounts();
    load_invoice_items();
    load_invoice_totals();
    load_taxes();
  }

  virtual void dump() const {
    assert(root);
    XMLDocument::dump();
    std::cout << id() << ".BillingMode: " << BillingMode << std::endl;
    std::cout << id() << ".InvType: " << InvType << std::endl;
    dump_dates();
    dump_cash_discounts();
    dump_invoice_items();
    dump_invoice_totals();
    dump_taxes();
  }

  const char *BillingMode;
  const char *InvType;
  std::set<XMLDate *> Dates;
  std::set<XMLCashDiscount *> CashDiscounts;
  std::set<XMLInvoiceItem *> InvoiceItems;
  XMLInvoiceTotals *InvoiceTotals;
  std::set<XMLTax *> Taxes;

  const std::string FindDate(const char *Type) const {
    bool found = false;
    for (auto it = Dates.begin(); it != Dates.end() && !found; ++it) {
      if (STREQ((*it)->Type, Type)) {
        return (*it)->Date;
      }
    }

    if (!found) {
      throw std::invalid_argument(std::string("Can't find date of type: ") +
                                  Type);
    }

    return "";
  }

  std::string FindInvoiceTotalChargeAmount(const char *Id) const {
    return InvoiceTotals->FindChargeAmount(Id);
  }

  template <int N>
  void collect(std::set<std::string> &unique, std::regex &pattern) const {
    for (auto it = InvoiceItems.begin(); it != InvoiceItems.end(); ++it) {
      (*it)->collect<N>(unique, pattern);
    }
  }

  void collect_charge(long &total, const char *Id, std::regex &pattern) const {
    for (auto it = InvoiceItems.begin(); it != InvoiceItems.end(); ++it) {
      (*it)->collect_charge(total, Id, pattern);
    }
  }

  void collect_charge_tax(long &total, long &taxRate, const char *Id,
                          std::regex &pattern) const {
    for (auto it = InvoiceItems.begin(); it != InvoiceItems.end(); ++it) {
      (*it)->collect_charge_tax(total, taxRate, Id, pattern);
    }
  }

  void collect_price(long &price, std::regex &pattern) const {
    for (auto it = InvoiceItems.begin(); it != InvoiceItems.end(); ++it) {
      if ((*it)->collect_price(price, pattern)) {
        return;
      }
    }
  }

private:
  rapidxml::xml_node<> *root;

  void load_attributes() {
    BillingMode = find_attribute_value("BillingMode", root);
    InvType = find_attribute_value("InvType", root);
  }

  void load_dates() { load_subnodes<XMLDate>(root, "Date", Dates); }

  void load_cash_discounts() {
    load_subnodes<XMLCashDiscount>(root, "CashDiscount", CashDiscounts);
  }

  void load_invoice_items() {
    load_subnodes<XMLInvoiceItem>(root, "InvoiceItem", InvoiceItems);
  }

  void load_invoice_totals() {
    InvoiceTotals = find_subnode<XMLInvoiceTotals>(root, "InvoiceTotals");
  }

  void load_taxes() { load_subnodes<XMLTax>(root, "Tax", Taxes); }

  void dump_dates() const {
    const unsigned int n = Dates.size();
    if (n) {
      std::cout << "Dates: "
                << "(" << n << ")" << std::endl;
      for (auto it = Dates.begin(); it != Dates.end(); ++it) {
        (*it)->dump();
      }
    }
  }

  void dump_cash_discounts() const {
    const unsigned int n = CashDiscounts.size();
    if (n) {
      std::cout << "CashDiscounts: "
                << "(" << n << ")" << std::endl;
      for (auto it = CashDiscounts.begin(); it != CashDiscounts.end(); ++it) {
        (*it)->dump();
      }
    }
  }

  void dump_invoice_items() const {
    const unsigned int n = InvoiceItems.size();
    if (n) {
      std::cout << "InvoiceItems: "
                << "(" << n << ")" << std::endl;
      for (auto it = InvoiceItems.begin(); it != InvoiceItems.end(); ++it) {
        (*it)->dump();
      }
    }
  }

  void dump_invoice_totals() const {
    if (InvoiceTotals) {
      InvoiceTotals->dump();
    }
  }

  void dump_taxes() const {
    const unsigned int n = Taxes.size();
    if (n) {
      std::cout << "Taxes: "
                << "(" << n << ")" << std::endl;
      for (auto it = Taxes.begin(); it != Taxes.end(); ++it) {
        (*it)->dump();
      }
    }
  }

  void clear() {
    clear_dates();
    clear_cash_discounts();
    clear_invoice_items();
    clear_invoice_totals();
    clear_taxes();
  }

  void clear_dates() {
    for (auto it = Dates.begin(); it != Dates.end(); ++it) {
      delete *it;
    }
    Dates.clear();
  }

  void clear_cash_discounts() {
    for (auto it = CashDiscounts.begin(); it != CashDiscounts.end(); ++it) {
      delete *it;
    }
    CashDiscounts.clear();
  }

  void clear_invoice_items() {
    for (auto it = InvoiceItems.begin(); it != InvoiceItems.end(); ++it) {
      delete *it;
    }
    InvoiceItems.clear();
  }

  void clear_invoice_totals() {
    if (InvoiceTotals) {
      delete InvoiceTotals;
    }
  }

  void clear_taxes() {
    for (auto it = Taxes.begin(); it != Taxes.end(); ++it) {
      delete *it;
    }
    Taxes.clear();
  }
};

#endif // __XML_DOCUMENT_INVOICE_HPP__
