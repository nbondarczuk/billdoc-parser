#ifndef __TXT_INVOICE_VAT_TOTAL_HPP__
#define __TXT_INVOICE_VAT_TOTAL_HPP__

#include "xml_document.hpp"
#include "xml_document_invoice.hpp"
#include "xml_document_summary.hpp"
#include "xml_document_address_page.hpp"
#include "xml_document_balance_page.hpp"
#include "xml_document_call_details.hpp"
#include "xml_document_complement.hpp"
#include "xml_document_legend.hpp"
#include "xml_document_contracts.hpp"
#include "xml_document_invoice_info.hpp"
#include "txt_format.hpp"
#include "dateutl.hpp"
#include "amtutl.hpp"

// INVCEVTOT: total vat tag
class TXTInvoiceVATTotal {
public:
	TXTInvoiceVATTotal(const XMLDocumentInvoice* invoice) {
		load_invoice(invoice);
	}
	
	std::string tagvals() const {
		return "INVCEVTOT" + FS +
			vat_total_amount + FS +
			sap_vat_total_amount + FS +
			invoice_no + FS;
	}		
	
private:
	std::string vat_total_amount;
	std::string sap_vat_total_amount;
	std::string invoice_no;
	
	void load_invoice(const XMLDocumentInvoice* invoice) {
		assert(invoice);
		long total = 0;
		for (auto it = invoice->Taxes.begin(); it != invoice->Taxes.end(); ++it) {
			std::string vatChargeAmount((*it)->FindTaxChargeAmount("124"));
			total += GetDecimalAmount<2>(vatChargeAmount);
		}
		vat_total_amount = PutDecimalAmount<2>(total);
		invoice_no.assign(invoice->Id);
	}
};

#endif
