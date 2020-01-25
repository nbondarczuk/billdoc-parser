#ifndef __TXT_INVOICE_DETAILS_HPP__
#define __TXT_INVOICE_DETAILS_HPP__

#include <algorithm>
#include <list>

#include "amtutl.hpp"
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

// invoice generic details for all specific types
class TXTInvoiceLineVariant {
public:
  std::string VariandCode;
  std::string Description1;
  std::string Description2;
  std::string Description3;
  std::string DateFrom;
  std::string DateTo;
  std::string Quantity;
  std::string UnitType;
  std::string Rate;
  std::string DiscountValue;
  std::string DiscountDescription;
  std::string InvoiceLineValue;
  std::string VATRate;
  std::string VATValue;
  std::string CallRecordQuantity;
  std::string AmountIncVAT;

  void dump() const {
    std::cout << "INVCLIN" << FS << VariandCode << FS << Description1 << FS
              << Description2 << FS << Description3 << FS << DateFrom << FS
              << DateTo << FS << Quantity << FS << UnitType << FS << Rate << FS
              << DiscountValue << FS << DiscountDescription << FS
              << InvoiceLineValue << FS << VATRate << FS << VATValue << FS
              << CallRecordQuantity << FS << AmountIncVAT << FS << RS;
  }
};

// A-type variant: tariff model header
class TXTInvoiceLineVariantRatePlan : public TXTInvoiceLineVariant {
public:
  TXTInvoiceLineVariantRatePlan(std::string id, std::string des,
                                std::string date_start, std::string date_end)
      : tmid(id), tmdes(des) {
    // rebase common fields
    TXTInvoiceLineVariant::VariandCode = "A";
    TXTInvoiceLineVariant::Description3 = id;
    TXTInvoiceLineVariant::DateFrom = date_start;
    TXTInvoiceLineVariant::DateTo = date_end;
  }

  void dump() const {
    TXTInvoiceLineVariant::dump(); // generic dump, variant common
  }

private:
  std::string tmid;
  std::string tmdes;
};

// all details section, starting with A-type detail variant
class TXTInvoiceLines {
public:
  TXTInvoiceLines(const XMLDocumentInvoice *invoice,
                  const XMLDocumentSummary *summary,
                  const XMLDocumentLegend *legend) {
    load_tariffs(invoice, summary, legend);
  }

  void dump() const {
    for (auto it = details.begin(); it != details.end(); ++it) {
      (*it)->dump();
    }
  }

private:
  std::list<TXTInvoiceLineVariant *> details;
  std::set<std::string> tariffs;

  void load_tariffs(const XMLDocumentInvoice *invoice,
                    const XMLDocumentSummary *summary,
                    const XMLDocumentLegend *legend) {
    // recursively find use tariff models in sum-sheet
    summary->collect(tariffs);
    for (auto it = tariffs.begin(); it != tariffs.end(); ++it) {
      // collect tariff info
      std::string tm_id(*it);
      std::string tm_des(legend->getLongDes("TM", tm_id.c_str()));
      std::string tm_date_start(FormatDate(invoice->FindDate("START")));
      std::string tm_date_end(FormatDate(invoice->FindDate("END")));
      // make new tariff model detail
      details.push_back(new TXTInvoiceLineVariantRatePlan(
          tm_id, tm_des, tm_date_start, tm_date_end));
    }
  }
};

#endif // __TXT_INVOICE_DETAILS_HPP__
