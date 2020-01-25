#ifndef __TXT_INVOICE_VAT_HPP__
#define __TXT_INVOICE_VAT_HPP__

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

// INVCEVAT: total vat amount tag
class TXTInvoiceVAT {
public:
  TXTInvoiceVAT(std::string vat_rate, std::string vat_charge_amount,
                std::string net_charge_amount)
      : rate(FormatDecimalRate<5>(vat_rate)),
        amount(FormatDecimalAmount<2>(vat_charge_amount)),
        net_amount(FormatDecimalAmount<2>(net_charge_amount)) {}

  std::string tagvals() const {
    return "INVCEVAT" + FS + amount + FS + rate + FS + net_amount + FS;
  }

private:
  std::string rate;
  std::string amount;
  std::string net_amount;
};

#endif
