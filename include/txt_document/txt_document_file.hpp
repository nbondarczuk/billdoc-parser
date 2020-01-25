#ifndef __TXT_DOCUMENT_FILE_HPP__
#define __TXT_DOCUMENT_FILE_HPP__

#include <vector>

#include "bill_document.hpp"
#include "dateutl.hpp"
#include "txt_format.hpp"

class TXTDocumentFile {
public:
  TXTDocumentFile(std::map<std::string, BillDocument *> &bd)
      : inv_printed(0), rfm_printed(0), cdt_printed(0), bdm_printed(0),
        env_printed(0),
        invoice(dynamic_cast<XMLDocumentInvoice *>(bd["Document.Invoice"])) {
    FileCreated.assign(FileTimeStamp());
    load_invoice(invoice);
  }

  ~TXTDocumentFile() {}

  void add(const BillDocument *d) {
    docs.push_back(d);
    inv_printed++;
  }

  void dump() const {
    dump_file_header();
    for (auto it = docs.cbegin(); it != docs.cend(); ++it) {
      (*it)->dump();
    }
    dump_file_trailer();
    std::cout << std::endl; // flush the buffer
  }

private:
  std::string FileCreated;
  std::string FileName;
  std::string BillCycleNo;
  std::string BatchVersion;
  unsigned int inv_printed;
  unsigned int rfm_printed;
  unsigned int cdt_printed;
  unsigned int bdm_printed;
  unsigned int env_printed;
  const XMLDocumentInvoice *invoice;
  std::vector<const BillDocument *> docs;

  void load_invoice(const XMLDocumentInvoice *invoice) {
    FileName.assign("INV");
    FileName += invoice->Id;
    FileName += ".txt";
  }

  void dump_file_header() const {
    std::cout << "FILEHDR" << FS << FileCreated << FS << FileName << FS
              << BillCycleNo << FS << BatchVersion << FS << RS;
  }

  void dump_file_trailer() const {
    std::cout << "FILETRLR" << FS << inv_printed << FS << rfm_printed << FS
              << cdt_printed << FS << bdm_printed << FS << env_printed << FS
              << RS;
  }
};

#endif // __TXT_DOCUMENT_FILE_HPP__
