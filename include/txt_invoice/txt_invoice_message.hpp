#ifndef __TXT_INVOICE_MESSAGE_HPP__
#define __TXT_INVOICE_MESSAGE_HPP__

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

// MESSAGE tag
class TXTInvoiceMessage {
public:
	TXTInvoiceMessage(const XMLDocumentInvoiceInfo* invoice_info) {
		load(invoice_info);
	}
	
	std::string tagvals() const {
		std::string message;
		for (int i = 0; i < text.size(); i++) {
			message += "MESSAGE|" + text[i];
			if (i < text.size() - 1) {
				message += "\n";
			}	
		}
		return message;
	}

private:
	std::vector<std::string> text;

	void load(const XMLDocumentInvoiceInfo* invoice_info) {
		std::string line;
		for (auto it = invoice_info->AdvTxt.begin(); it != invoice_info->AdvTxt.end(); ++it) {
			line.assign((*it)->AdvTxt);
			text.push_back(line);
		}
	}
};

#endif // __TXT_INVOICE_MESSAGE_HPP__
