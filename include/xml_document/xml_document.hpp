#ifndef __XML_DOCUMENT_HPP__
#define __XML_DOCUMENT_HPP__

#include <assert.h>

#include <iostream>
#include <istream>
#include <iterator>    
#include <fstream>
#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xmlutl.hpp"
#include "bill_document.hpp"

// cache & handle: document in xml format to be loaded from file
class XMLDocument : public BillDocument {
public:
	XMLDocument() : doc(0), root(0) {}	

	// load xml from file parsing it and populating the cache
	XMLDocument(const char *fn) : doc(0), root(0) {
		parse_document_file(fn);
		XMLDocument::load();
	}

	~XMLDocument() {
		if (doc) {
			doc->clear();
			delete doc;
		}
		if (buffer_ptr) {
			delete buffer_ptr;
		}	
	}	
	
	virtual std::string id() const {
		if (!root) {
			return "EMPTY";
		}
		
		std::string name(root->name());
		if (name == "Document") {
			name += ".";			
			name += subnode_name();			
		}

		return name;	
	}

	virtual XMLDocument* clone() const {
		XMLDocument* p = new XMLDocument(*this);
		return p;		
	}
	
	// parse all xml info mapping it to fields in case doc base changed
	virtual void reload() {
		assert(doc);
		root = doc->first_node();
		XMLDocument::load();
	}	

	virtual void load() {
		assert(root);
		load_attributes();			
	}
	
	virtual void dump() const {
		assert(root);		
		std::cout << id() << ".Sender: " << Sender << std::endl;
		std::cout << id() << ".Id: " << Id << std::endl;
		std::cout << id() << ".BAId: " << BAId << std::endl;
	}

	// shall be first subnode of Document
	virtual std::string subnode_name() const {
		assert(root);
		return root->first_node()->name();
	}
	
	// reinit main xml structure with parameter to be destroyed
	void rebase(XMLDocument* d) {
		// move references to a new container
		buffer_ptr = d->buffer_ptr;
		doc = d->doc;
		root = d->root;
		// release moved references
		d->buffer_ptr = 0;
		d->doc = 0;
		d->root = 0;
	}

	// original file name of the xml
	const std::string filename() const {
		return xml_filename;
	}	

	rapidxml::xml_node<> *get_document_root() const {
		return root;
	}
	
	const char* Sender;
	const char* Id;
	const char* BAId;	
	
private:
	std::string xml_filename;
	std::vector<char>* buffer_ptr;
	rapidxml::xml_document<>* doc;
	rapidxml::xml_node<>* root;

	// handle the xml file parsing it and storing the document root node
	void parse_document_file(const char* fn) {
		xml_filename.assign(fn);
		buffer_ptr = read_binary_file(fn);
		doc = new rapidxml::xml_document<>();
		try {
			doc->parse<0>(&(*buffer_ptr)[0]);
		} catch(const rapidxml::parse_error &e) {
			throw std::invalid_argument(std::string("Invalid XML, parse error: ") + e.what());
		}
		
		root = doc->first_node();
		if (!root) {
			throw std::invalid_argument(std::string("Invalid XML, no root node"));			
		} else if (!(STREQ(root->name(), "Document") || STREQ(root->name(), "Envelope"))) {
			throw std::invalid_argument(std::string("Invalid XML: ") + root->name());			
		}		
	}

	void load_attributes() {
		Sender = find_attribute_value_option("Sender", root);
		Id = find_attribute_value_option("Id", root);
		BAId = find_attribute_value_option("BAId", root);
	}
};

#endif //__XML_DOCUMENT_HPP__
