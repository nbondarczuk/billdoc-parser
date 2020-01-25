#ifndef __TXT_INVOICE_LINE_VARIANT_TARIFF_HPP__
#define __TXT_INVOICE_LINE_VARIANT_TARIFF_HPP__

#include <regex>

#include "txt_format.hpp"
#include "txt_invoice_line_variant.hpp"
#include "txt_invoice_line_variant_access.hpp"
#include "txt_invoice_line_variant_access_total.hpp"
#include "txt_invoice_line_variant_tariff.hpp"
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

// A-type variant: tariff model header
class TXTInvoiceLineVariantTariff : public TXTInvoiceLineVariant {
public:
  TXTInvoiceLineVariantTariff(std::string id, std::string des,
                              std::string start, std::string end)
      : tariffId(id), tariffDes(des), accessTotal(0) {
    // rebase common fields
    TXTInvoiceLineVariant::VariandCode = "A";
    TXTInvoiceLineVariant::Description3 = des;
    TXTInvoiceLineVariant::DateFrom = start;
    TXTInvoiceLineVariant::DateTo = end;
  }

  void dump() const {
    TXTInvoiceLineVariant::dump(); // generic dump, variant common
    if (accessTotal) {
      accessTotal->dump();
      dump_access_charges();
    }
    dump_usage_charges();
    dump_occ_charges();
  }

  // variant M: total of B (standard access fee), P1 (PVAS access fee)
  void load_access_charges(const XMLDocumentInvoice *invoice,
                           const XMLDocumentSummary *summary,
                           const XMLDocumentLegend *legend) {
    std::set<std::string> unique;
    std::string pattern("^" + tariffId +
                        "\\.\\d+\\.\\d+\\.\\d+\\.A\\.AC\\.P\\.[PCA]$");
    std::regex access_charges(pattern);
    invoice->collect<5>(unique, access_charges); // 5 token prefix
    accessTotal = new TXTInvoiceLineVariantAccessTotal(invoice);
    for (auto it = unique.begin(); it != unique.end(); ++it) {
      // prorated access fee
      std::regex access_past_cred("^" + *it + "\\.AC\\.P\\.[PC]$");
      TXTInvoiceLineVariantAccess *a1 = new TXTInvoiceLineVariantAccess(
          *it, invoice, summary, legend, access_past_cred);
      access.push_back(a1);
      accessTotal->Add(a1->GetAmountNet(), a1->GetAmountVAT(),
                       a1->GetAmountWithVAT());
      // advance acess fee
      std::regex access_adv("^" + *it + "\\.AC\\.P\\.[A]$");
      TXTInvoiceLineVariantAccess *a2 = new TXTInvoiceLineVariantAccess(
          *it, invoice, summary, legend, access_adv);
      access.push_back(a2);
      accessTotal->Add(a2->GetAmountNet(), a2->GetAmountVAT(),
                       a2->GetAmountWithVAT());
    }
  }

  // variant E: total of D
  void load_usage_charges(const XMLDocumentInvoice *invoice,
                          const XMLDocumentSummary *summary,
                          const XMLDocumentLegend *legend) {
    std::regex usage_item_pattern(tariffId + USAGE_FEE_REGEXP);
    // invoice->collect<5>(usage, usage_item_pattern);
    for (auto it = usage.begin(); it != usage.end(); ++it) {
      // std::cout << "Usage: " << *it << std::endl;
    }
  }

  // variant O: total of P2
  void load_occ_charges(const XMLDocumentInvoice *invoice,
                        const XMLDocumentSummary *summary,
                        const XMLDocumentLegend *legend) {
    std::regex pvas_item_pattern(tariffId + PVAS_FEE_REGEXP);
    // invoice->collect<5>(pvas, pvas_item_pattern);
    for (auto it = pvas.begin(); it != pvas.end(); ++it) {
      // std::cout << "PVAS: " << *it << std::endl;
    }
  }

private:
  // regexp for invoice service item
  const char *ACCESS_FEE_REGEXP = "\\.\\w+\\.\\w\\.[APC]$";
  const char *ACCESS_FEE_REGEXP_PAST_CRED = "\\.\\w+\\.\\w\\.[PC]$";
  const char *ACCESS_FEE_REGEXP_ADV = "\\.\\w+\\.\\w\\.[A]$";
  const char *USAGE_FEE_REGEXP = "\\..+";
  const char *OCC_FEE_REGEXP = "\\..+";
  const char *PVAS_FEE_REGEXP = "\\.\\w+\\.\\w\\.\\w+\\.\\w\\.\\d+$";
  // tariff info
  std::string tariffId;
  std::string tariffDes;
  // distinctive 5 token long prefixes for all valid invoice items
  std::vector<TXTInvoiceLineVariantAccess *> access;
  TXTInvoiceLineVariantAccessTotal *accessTotal;
  std::set<std::string> usage;
  std::set<std::string> pvas;

  void dump_access_charges() const {
    for (auto it = access.begin(); it != access.end(); ++it) {
      (*it)->dump();
    }
  }

  void dump_usage_charges() const {}

  void dump_occ_charges() const {}
};

#endif
