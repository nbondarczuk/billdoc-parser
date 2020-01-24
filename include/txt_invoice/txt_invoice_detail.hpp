#ifndef __TXT_INVOICE_DETAIL_HPP__
#define __TXT_INVOICE_DETAIL_HPP__

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
#include "txt_invoice_form_header.hpp"
#include "txt_invoice_customer_address.hpp"
#include "txt_invoice_detail.hpp"
#include "txt_invoice_message.hpp"
#include "txt_format.hpp"
#include "dateutl.hpp"
#include "amtutl.hpp"

// INVCDETL: invoice details tag
class TXTInvoiceDetail {
public:
	TXTInvoiceDetail(const XMLDocumentInvoice* invoice,
					 const XMLDocumentAddressPage* address) {
		load_invoice(invoice);
		load_address(address);
	}
	
	std::string tagvals() const {
		return "INVCDETL" + FS +
			invoiceNumber  + FS +
			contractNumber + FS +
			remittanceOnInvoiceFlag + FS +
			bankAccountNumber + FS +
			invoiceDueDate + FS +
			paymentMethod + FS +
			billingPeriodEndDate + FS +
			contractId + FS +
			printFlag + FS +
			eBillFlag + FS;
	}

private:
	std::string invoiceNumber;
	std::string contractNumber;
	std::string remittanceOnInvoiceFlag;
	std::string bankAccountNumber;
	std::string invoiceDueDate;
	std::string paymentMethod;
	std::string billingPeriodEndDate;
	std::string contractId;
	std::string printFlag;
	std::string eBillFlag;

	void load_invoice(const XMLDocumentInvoice* invoice) {
		assert(invoice);
		invoiceNumber.assign(invoice->Id);
		invoiceDueDate.assign(FormatDate(invoice->FindDate("DUE_DATE")));
		billingPeriodEndDate.assign(FormatDate(invoice->FindDate("END")));		
	}

	void load_address(const XMLDocumentAddressPage* address) {
		assert(address);
		assert(address->BillAcc);
		paymentMethod.assign(Decode(address->BillAcc->PayMeth, "Direct Debit", "D", address->BillAcc->PayMeth));
		bankAccountNumber.assign(address->BillAcc->FiCont->Account->Num);
		eBillFlag.assign(Decode(address->BillAcc->BillMedium, "EBILL", "Y", "N"));
	}
};

#endif // __TXT_INVOICE_DETAIL_HPP__
