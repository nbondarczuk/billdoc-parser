#ifndef __TXT_INVOICE_LINES_HPP__
#define __TXT_INVOICE_LINES_HPP__

#include <algorithm>
#include <list>

#include "amtutl.hpp"
#include "txt_format.hpp"
#include "txt_invoice_line_variant.hpp"
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

// all details section, starting with A-type detail variant
class TXTInvoiceLines {
public:
  TXTInvoiceLines(const XMLDocumentInvoice *invoice,
                  const XMLDocumentSummary *summary,
                  const XMLDocumentLegend *legend) {
    load_tariffs(invoice, summary, legend);
    load_tariff_charges(invoice, summary, legend);
  }

  void dump() const {
    for (auto it = lines.begin(); it != lines.end(); ++it) {
      (*it)->dump();
    }
  }

private:
  std::list<TXTInvoiceLineVariantTariff *> lines;
  std::set<std::string> tariffs;

  void load_tariffs(const XMLDocumentInvoice *invoice,
                    const XMLDocumentSummary *summary,
                    const XMLDocumentLegend *legend) {
    // recursively find use tariff models in sum-sheet
    summary->collect(tariffs);
    for (auto it = tariffs.begin(); it != tariffs.end(); ++it) {
      // decode tariff info for invoice line
      std::string id(*it);
      std::string des(legend->getLongDes("TM", id.c_str()));
      std::string start(FormatDate(invoice->FindDate("START")));
      std::string end(FormatDate(invoice->FindDate("END")));
      // make new top level capital tariff line
      lines.push_back(new TXTInvoiceLineVariantTariff(id, des, start, end));
    }
  }

  void load_tariff_charges(const XMLDocumentInvoice *invoice,
                           const XMLDocumentSummary *summary,
                           const XMLDocumentLegend *legend) {
    for (auto it = lines.begin(); it != lines.end(); ++it) {
      (*it)->load_access_charges(invoice, summary, legend);
      (*it)->load_usage_charges(invoice, summary, legend);
      (*it)->load_occ_charges(invoice, summary, legend);
    }
  }
};

#endif // __TXT_INVOICE_LINES_HPP__
