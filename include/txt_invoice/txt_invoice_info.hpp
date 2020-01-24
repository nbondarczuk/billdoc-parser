#ifndef __TXT_INVOICE_INFO_HPP__
#define __TXT_INVOICE_INFO_HPP__

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

// INVCEINFO
class TXTInvoiceInfo {
public:
	TXTInvoiceInfo(const XMLDocumentInvoice* invoice,
				   const XMLDocumentAddressPage* address) {
		load_invoice(invoice);
		load_address(address);
		make_info();
	}
	
	std::string tagvals() const {
		return "INVCEINFO" + FS +
			info + FS;
	}

private:
	std::string bankAccountNumber;
	std::string invoiceDueDate;
	std::string paymentMethod;
	std::string info;
	
	const char* DIRECT_DEBIT_INFO =
		"Het totaalbedrag wordt omstreeks %s van uw rekeningnr. %s afgeschreven.";
	
	void load_address(const XMLDocumentAddressPage* address) {
		assert(address);
		bankAccountNumber.assign(address->BillAcc->FiCont->Account->Num);
		paymentMethod.assign(Decode(address->BillAcc->PayMeth,
									"Direct Debit", "D",
									address->BillAcc->PayMeth));
	}

	void load_invoice(const XMLDocumentInvoice* invoice) {
		invoiceDueDate.assign(FormatDate(invoice->FindDate("DUE_DATE")));
	}

	void make_info() {
		if (paymentMethod == "D") {
			char buffer[256];
			sprintf(buffer,
					DIRECT_DEBIT_INFO,
					invoiceDueDate.c_str(),
					bankAccountNumber.c_str());
			info.assign(buffer);
		}
	}		
};

#endif
