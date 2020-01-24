#ifndef __TXT_INVOICE_LINE_VARIANT_ACCESS_HPP__
#define __TXT_INVOICE_LINE_VARIANT_ACCESS_HPP__

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
#include "txt_invoice_line_variant_tariff.hpp"
#include "txt_format.hpp"
#include "strutl.hpp"

class TXTInvoiceLineVariantAccess : public TXTInvoiceLineVariant {
public:
	TXTInvoiceLineVariantAccess(const std::string& article,
								const XMLDocumentInvoice* inv,
								const XMLDocumentSummary* sum,
								const XMLDocumentLegend* lgn,
								std::regex& re) :
		amountNet(0),
		amountVAT(0),
		amountWithVAT(0),
		taxRate(0),
		price(0),
		charge_item(re) {
		TXTInvoiceLineVariant::VariandCode = "B";
		load_desc(article, lgn);
		load_dates(sum);
		load_price(inv);
		load_charges(inv);
	}
	
	void dump() const {
		TXTInvoiceLineVariant::dump(); // generic dump, variant common
	}

	long GetAmountNet() const {
		return amountNet;
	}
	
	long GetAmountVAT() const {
		return amountVAT;
	}

	long GetAmountWithVAT() const {
		return amountWithVAT;
	}
	
private:
	std::regex charge_item;
	long amountNet;
	long amountVAT;
	long amountWithVAT;
	long taxRate;
	long price;
	std::string start;
	std::string end;
	
	void load_desc(const std::string& article, const XMLDocumentLegend* lgn) {			
		TXTInvoiceLineVariant::Description1 = lgn->getLongDes("SN", split<5>(article.c_str(), '.')[3].c_str());
		TXTInvoiceLineVariant::Description2 = lgn->getLongDes("SP", split<5>(article.c_str(), '.')[2].c_str());
		TXTInvoiceLineVariant::Description3 = lgn->getLongDes("TM", split<5>(article.c_str(), '.')[0].c_str());
	}

	void load_dates(const XMLDocumentSummary* sum) {
		sum->collect_service_dates(start, end, charge_item);
		TXTInvoiceLineVariant::DateFrom = FormatDate(start);
		TXTInvoiceLineVariant::DateTo = FormatDate(end);
	}
	
	void load_price(const XMLDocumentInvoice* inv) {
		inv->collect_price(price, charge_item);
		TXTInvoiceLineVariant::Rate = PutDecimalAmount<2>(price);
	}
	
	void load_charges(const XMLDocumentInvoice* inv) {
		inv->collect_charge(amountNet, "125", charge_item);
		TXTInvoiceLineVariant::InvoiceLineValue = PutDecimalAmount<2>(amountNet);
		inv->collect_charge_tax(amountVAT, taxRate, "124", charge_item);
		TXTInvoiceLineVariant::RateVAT = PutDecimalAmount<2>(taxRate);	
		TXTInvoiceLineVariant::AmountVAT = PutDecimalAmount<2>(amountVAT);		
		inv->collect_charge(amountWithVAT, "203", charge_item);
		TXTInvoiceLineVariant::AmountWithVAT = PutDecimalAmount<2>(amountWithVAT);		
	}	
};

#endif
