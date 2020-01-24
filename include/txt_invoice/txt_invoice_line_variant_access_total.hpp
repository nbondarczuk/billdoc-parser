#ifndef __TXT_INVOICE_LINE_VARIANT_ACCESS_TOTAL_HPP__
#define __TXT_INVOICE_LINE_VARIANT_ACCESS_TOTAL_HPP__

#include <regex>

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
#include "txt_invoice_line_variant.hpp"
#include "txt_invoice_line_variant_access.hpp"
#include "txt_format.hpp"
#include "strutl.hpp"

class TXTInvoiceLineVariantAccessTotal : public TXTInvoiceLineVariant {
public:
	TXTInvoiceLineVariantAccessTotal(const XMLDocumentInvoice* inv) :
		amountNet(0),
		amountVAT(0),
		amountWithVAT(0) {
		TXTInvoiceLineVariant::VariandCode = "M";
		TXTInvoiceLineVariant::Description1 = "Maandkosten";
		TXTInvoiceLineVariant::DateTo.assign(FormatDate(inv->FindDate("END")));
	}
	
	void dump() {
		TXTInvoiceLineVariant::InvoiceLineValue = PutDecimalAmount<2>(amountNet);
		TXTInvoiceLineVariant::AmountVAT = PutDecimalAmount<2>(amountVAT);
		TXTInvoiceLineVariant::AmountWithVAT = PutDecimalAmount<2>(amountWithVAT);
		TXTInvoiceLineVariant::dump(); // generic dump, variant common
	}

	void Add(long a1, long a2, long a3) {
		amountNet += a1;
		amountVAT += a2;
		amountWithVAT += a3;
	}
	
private:
	long amountNet;
	long amountVAT;
	long amountWithVAT;
};

#endif
