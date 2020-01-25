#ifndef __TXT_INVOICE_HEADER_HPP__
#define __TXT_INVOICE_HEADER_HPP__

#include <vector>

#include "amtutl.hpp"
#include "dateutl.hpp"
#include "txt_format.hpp"
#include "txt_invoice_customer_address.hpp"
#include "txt_invoice_detail.hpp"
#include "txt_invoice_form_header.hpp"
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

// invoice header tags
class TXTInvoiceHeader {
public:
  TXTInvoiceHeader(const XMLDocumentInvoice *invoice,
                   const XMLDocumentAddressPage *address,
                   const XMLDocumentInvoiceInfo *invoice_info,
                   const XMLDocumentSummary *summary)
      : form_header(new TXTInvoiceFormHeader(invoice, address, summary)),
        customer_address(new TXTInvoiceCustomerAddress(address)),
        invoice_detail(new TXTInvoiceDetail(invoice, address)),
        message(new TXTInvoiceMessage(invoice_info)) {}

  void dump() const {
    std::cout << form_header->tagvals() << RS;
    std::cout << customer_address->tagvals() << RS;
    std::cout << invoice_detail->tagvals() << RS;
    // std::cout << message->tagvals() << std::endl;
  }

protected:
  TXTInvoiceFormHeader *form_header;
  TXTInvoiceCustomerAddress *customer_address;
  TXTInvoiceDetail *invoice_detail;
  TXTInvoiceMessage *message;
};

#endif // __TXT_INVOICE_HEADER_HPP__
