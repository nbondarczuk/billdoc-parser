#include <iostream>

#include <map>
#include <memory>

#include "trace.hpp"
#include "txt_document_factory.hpp"
#include "txt_document_file.hpp"
#include "xml_document_factory.hpp"

int main(int argn, char **argv) {
  FRAME;

  // parse all xml files and batch them in a map prepared for txt generation
  XMLDocumentFactory xml_factory;
  std::map<std::string, BillDocument *> docs;
  for (int i = 1; i < argn; ++i) {
    char *fn = argv[i];
    BillDocument *xml = xml_factory.make(fn);
    docs.insert(std::pair<std::string, BillDocument *>(xml->id(), xml));
    TRACE(sprintf("Loaded file: %s", fn));
  }

  // produce single txt document file using all batched xml files
  TXTDocumentFactory txt_factory;
  const BillDocument *txt_document = txt_factory.make(docs);
  TXTDocumentFile file(docs);
  file.add(txt_document);
  file.dump();

  return 0;
}
