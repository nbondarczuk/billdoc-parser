#include <iostream>

#include "xml_document_factory.hpp"

using namespace std;

int main(int argn, char **argv) {
  XMLDocumentFactory factory;
  for (int i = 1; i < argn; ++i) {
    char *fn = argv[i];
    try {
      XMLDocument *d = factory.make(fn);
      cout << "Load: " << fn << ": " << d->id() << endl;
      d->dump();
      delete d;
    } catch (std::exception &e) {
      cout << "Failed: " << fn << " - " << e.what() << endl;
    }
  }

  return 0;
}
