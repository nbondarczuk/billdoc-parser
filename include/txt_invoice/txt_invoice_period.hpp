#ifndef __TXT_INVOICE_PERIOD_HPP__
#define __TXT_INVOICE_PERIOD_HPP__

#include "amtutl.hpp"
#include "dateutl.hpp"
#include "txt_format.hpp"
#include "xml_document.hpp"
#include "xml_document_address_page.hpp"
#include "xml_document_balance_page.hpp"
#include "xml_document_call_details.hpp"
#include "xml_document_complement.hpp"
#include "xml_document_contracts.hpp"
#include "xml_document_invoice.hpp"
#include "xml_document_invoice_info.hpp"
#include "xml_document_legend.hpp"
#include "xml_document_summary.hpp"

// INVCEPER: invoice period tag
class TXTInvoicePeriod {
public:
  TXTInvoicePeriod(const XMLDocumentInvoice *invoice) {
    assert(invoice);
    load_invoice(invoice);
  }

  std::string tagvals() const {
    return "INVCEPER" + FS + start + FS + end + FS;
  }

private:
  std::string start;
  std::string end;

  void load_invoice(const XMLDocumentInvoice *invoice) {
    assert(invoice);
    start.assign(FormatDate(invoice->FindDate("START")));
    end.assign(FormatDate(invoice->FindDate("END")));
  }
};

#endif
