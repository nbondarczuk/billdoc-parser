#ifndef __TXT_INVOICE_FORM_HEADER_HPP__
#define __TXT_INVOICE_FORM_HEADER_HPP__

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

// FORMHDR: invoice header tag
class TXTInvoiceFormHeader {
public:
	TXTInvoiceFormHeader(const XMLDocumentInvoice* invoice,
						 const XMLDocumentAddressPage* address,
						 const XMLDocumentSummary* summary) {
		load_invoice(invoice);
		load_address(address);
		load_summary(summary);
		load_setup();
	}
	
	std::string tagvals() const {
		return "FORMHDR" + FS +
			documentType + FS +
			customerCode + FS +
			divertCode  + FS +
			firstAddrLine + FS +
			invoiceDate + FS +
			referenceNumber + FS +
			customerType + FS +
			pricesIncVAT + FS +
			printVAT + FS;
	}
	
private:
	std::string documentType;
	std::string customerCode;
	std::string divertCode;
	std::string firstAddrLine;
	std::string invoiceDate;
	std::string referenceNumber;
	std::string customerType;
	std::string pricesIncVAT;
	std::string printVAT;

	void load_invoice(const XMLDocumentInvoice* invoice) {
		documentType.assign("INVOICE");
		assert(invoice);	
		invoiceDate.assign(FormatDate(invoice->FindDate("INV")));
		referenceNumber.assign(invoice->Id); // tbd
	}
	
	void load_address(const XMLDocumentAddressPage* address) {
		assert(address);	
		assert(address->BillAcc);
		assert(address->BillAcc->Addr);
		assert(address->BillAcc->Customer);
		customerCode.assign(address->BillAcc->Customer->Id);
		firstAddrLine.assign(address->BillAcc->Addr->Line1);
	}

	void load_summary(const XMLDocumentSummary* summary) {
		assert(summary);
		customerType.assign(summary->FindCustRef(customerCode.c_str())->PartyType);
	}
	
	void load_setup() {
		pricesIncVAT.assign("Y"); // tbd
		printVAT.assign("N"); // tbd
	}
};

#endif // __TXT_INVOICE_FORM_HEADER_HPP__

