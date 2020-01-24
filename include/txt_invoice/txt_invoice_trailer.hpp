#ifndef __TXT_INVOICE_TRAILER_HPP__
#define __TXT_INVOICE_TRAILER_HPP__

#include <vector>

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
#include "txt_invoice_sub_total.hpp"
#include "txt_invoice_total.hpp"
#include "txt_invoice_info.hpp"
#include "txt_invoice_period.hpp"
#include "txt_invoice_vat.hpp"
#include "txt_invoice_vat_total.hpp"
#include "txt_invoice_amount.hpp"
#include "txt_invoice_credit.hpp"
#include "txt_format.hpp"
#include "amtutl.hpp"

// invoice trailer tags
class TXTInvoiceTrailer {
public:
	TXTInvoiceTrailer(const XMLDocumentInvoice* invoice,
					  const XMLDocumentBalancePage* balance,
					  const XMLDocumentAddressPage* address) :
		sub_total(new TXTInvoiceSubTotal(invoice)),
		total(new TXTInvoiceTotal(invoice)),
		amount(new TXTInvoiceAmount(invoice)),
		info(new TXTInvoiceInfo(invoice, address)),
		period(new TXTInvoicePeriod(invoice)),
		vat_total(new TXTInvoiceVATTotal(invoice)) {
		load_tax(invoice);		
	}
	
	void dump() const {
		std::cout << sub_total->tagvals() << RS;
		for (auto it = vat.begin(); it != vat.end(); ++it) {
			std::cout << (*it)->tagvals() << RS;
		}
		std::cout << vat_total->tagvals() << RS;
		std::cout << total->tagvals() << RS;
		std::cout << amount->tagvals() << RS;
		std::cout << info->tagvals() << RS;
		std::cout << period->tagvals() << RS;
	}
	
private:
	TXTInvoiceSubTotal* sub_total;
	std::vector<TXTInvoiceVAT*> vat;
	TXTInvoiceTotal* total;
	TXTInvoiceCredit* credit;
	TXTInvoiceAmount* amount;
	TXTInvoiceInfo* info;
	TXTInvoicePeriod* period;
	TXTInvoiceVATTotal* vat_total;
	
	void load_tax(const XMLDocumentInvoice* invoice) {
		for (auto it = invoice->Taxes.begin(); it != invoice->Taxes.end(); ++it) {
			std::string vatRate((*it)->Rate);
			std::string vatChargeAmount((*it)->FindTaxChargeAmount("124"));
			std::string netChargeAmount((*it)->FindTaxChargeAmount("125"));
			vat.push_back(new TXTInvoiceVAT(vatRate, vatChargeAmount, netChargeAmount));
		}
	}
};

#endif // __TXT_INVOICE_TRAILER_HPP__
