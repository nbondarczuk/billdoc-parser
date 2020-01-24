#ifndef __TXT_INVOICE_LINE_VARIANT_HPP__
#define __TXT_INVOICE_LINE_VARIANT_HPP__

#include <string>

// invoice generic details for all specific types
class TXTInvoiceLineVariant {
public:
	std::string VariandCode;
	std::string Description1;
	std::string Description2;	
	std::string Description3;
	std::string DateFrom;
	std::string DateTo;
	std::string Quantity;
	std::string UnitType;
	std::string Rate;
	std::string DiscountValue;
	std::string DiscountDescription;
	std::string InvoiceLineValue;
	std::string RateVAT;
	std::string AmountVAT;
	std::string CallRecordQuantity;
	std::string AmountWithVAT;

	void dump() const {
		std::cout << "INVCLIN" << FS 
				  << VariandCode << FS 
				  << Description1 << FS 
				  << Description2 << FS 
				  << Description3 << FS
				  << DateFrom << FS 
				  << DateTo << FS 
				  << Quantity << FS 
				  << UnitType << FS 
				  << Rate << FS 
				  << DiscountValue << FS 
				  << DiscountDescription << FS 
				  << InvoiceLineValue << FS 
				  << RateVAT << FS 
				  << AmountVAT << FS 
				  << CallRecordQuantity << FS 
				  << AmountWithVAT << FS
				  << RS;
	}	
};

#endif
