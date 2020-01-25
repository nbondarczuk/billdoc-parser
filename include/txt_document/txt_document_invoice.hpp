#ifndef __TXT_DOCUMENT_INVOICE_HPP__
#define __TXT_DOCUMENT_INVOICE_HPP__

#include <exception>
#include <vector>

#include "bill_document.hpp"
#include "strutl.hpp"
#include "txt_document.hpp"
#include "txt_format.hpp"
#include "txt_invoice_header.hpp"
#include "txt_invoice_lines.hpp"
#include "txt_invoice_trailer.hpp"

// TXT invoice built using XML documents
class TXTDocumentInvoice : public TXTDocument {
public:
  TXTDocumentInvoice(std::map<std::string, BillDocument *> &bd)
      : header(0), lines(0), trailer(0),
        invoice(dynamic_cast<XMLDocumentInvoice *>(bd["Document.Invoice"])),
        invoice_info(
            dynamic_cast<XMLDocumentInvoiceInfo *>(bd["Document.InvoiceInfo"])),
        address(
            dynamic_cast<XMLDocumentAddressPage *>(bd["Document.AddressPage"])),
        balance(
            dynamic_cast<XMLDocumentBalancePage *>(bd["Document.BalancePage"])),
        summary(dynamic_cast<XMLDocumentSummary *>(bd["Document.Summary"])),
        legend(dynamic_cast<XMLDocumentLegend *>(bd["Document.Legend"])) {
    build();
  }

  ~TXTDocumentInvoice() { clear(); }

  virtual std::string id() const { return "TXTDocument::TXTDocumentInvoice"; }

  virtual BillDocument *clone() const {
    return 0; // not implemented (yet)
  }

  virtual void load() { build(); }

  virtual void reload() { build(); }

  virtual void dump() const {
    assert(header);
    assert(trailer);

    std::cout << "NEWENV" << FS << RS;
    header->dump();
    if (lines) {
      lines->dump();
    }
    trailer->dump();
  }

protected:
  TXTInvoiceHeader *header;
  TXTInvoiceLines *lines;
  TXTInvoiceTrailer *trailer;

private:
  const XMLDocumentInvoice *invoice;
  const XMLDocumentInvoiceInfo *invoice_info;
  const XMLDocumentAddressPage *address;
  const XMLDocumentSummary *summary;
  const XMLDocumentBalancePage *balance;
  const XMLDocumentLegend *legend;

  void build() {
    header = new TXTInvoiceHeader(invoice, address, invoice_info, summary);
    lines = new TXTInvoiceLines(invoice, summary, legend);
    trailer = new TXTInvoiceTrailer(invoice, balance, address);
  }

  void clear() {
    delete header;
    if (lines) {
      delete lines;
    }
    delete trailer;
  }
};

#endif // __TXT_DOCUMENT_INVOICE_HPP__
