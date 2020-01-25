#ifndef __TXT_INVOICE_TOTAL_HPP__
#define __TXT_INVOICE_TOTAL_HPP__

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

// INVCETOT: invoice gross amount = net + vat tag
class TXTInvoiceTotal {
public:
  TXTInvoiceTotal(const XMLDocumentInvoice *invoice) { load_invoice(invoice); }

  std::string tagvals() const { return "INVCETOT" + FS + amount + FS; }

private:
  std::string amount;

  void load_invoice(const XMLDocumentInvoice *invoice) {
    assert(invoice);
    amount.assign(
        FormatDecimalAmount<2>(invoice->FindInvoiceTotalChargeAmount("77")));
  }
};

#endif
