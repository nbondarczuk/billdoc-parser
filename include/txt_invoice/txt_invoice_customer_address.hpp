#ifndef __TXT_INVOICE_CUSTOMER_ADDRESS_HPP__
#define __TXT_INVOICE_CUSTOMER_ADDRESS_HPP__

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

// CUSTADDR: customer address tag
class TXTInvoiceCustomerAddress {
public:
	TXTInvoiceCustomerAddress(const XMLDocumentAddressPage* address) {
		line.resize(7);
		load(address);
	}
	
	std::string tagvals() const {
		return "CUSTADDR" + FS +
			line[3] + FS +
			line[4] + FS +
			line[5] + FS +
			line[6] + FS +
			line[2] + FS;
	}

private:
	std::vector<std::string> line;
	
	void load(const XMLDocumentAddressPage* address) {
		assert(address->BillAcc);
		assert(address->BillAcc->Addr);
		line[1].assign(address->BillAcc->Addr->Line1);
		line[2].assign(address->BillAcc->Addr->Line2);		
		line[3].assign(address->BillAcc->Addr->Line3);
		line[4].assign(address->BillAcc->Addr->Line4);
		line[5].assign(address->BillAcc->Addr->Line5);
		line[6].assign(address->BillAcc->Addr->Line6);
	}
};

#endif // __TXT_INVOICE_CUSTOMER_ADDRESS_HPP__
