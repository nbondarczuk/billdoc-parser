#ifndef __XML_DOCUMENT_LEGEND_HPP__
#define __XML_DOCUMENT_LEGEND_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "xml_document.hpp"
#include "xml_type_desc.hpp"

class XMLDocumentLegend : public XMLDocument {
public:
	XMLDocumentLegend() : root(0) {}

	XMLDocumentLegend(rapidxml::xml_node<>* node) : root(node) {
		load();
	}	

	~XMLDocumentLegend() {
		clear();
	}

	virtual std::string id() const {
		return "Document.Legend";	
	}

	virtual XMLDocumentLegend* clone() const {
		XMLDocumentLegend* p = new XMLDocumentLegend(*this);
		return p;
	}

	virtual void reload() {
		const rapidxml::xml_node<>* document_root = get_document_root();
		root = document_root->first_node("Legend");
		load();
	}

	virtual void load() {
		assert(root);
		load_type_desc_dict();
	}

	virtual void dump() const {
		assert(root);
		dump_type_desc_dict();
	}

	// utility function to be used to decode article string
	const char* getLongDes(const char* type, const char* id) const {
		const char* rv = 0;
		const std::string v1(type);
		const std::string v2(id);
		const std::string separator(".");
		
		const std::string key(v1 + separator + v2);
		std::map<const std::string, XMLTypeDesc*>::const_iterator it2 = TypeDescDict.find(key);
		if (it2 != TypeDescDict.end()) {
			XMLTypeDesc* ptr = it2->second;
			return ptr->getLongDes();
		} else {
			throw std::invalid_argument(std::string("Can't find mapping of: ") + key);
		}
		
		return rv;
	}
	
	std::map<const std::string, XMLTypeDesc*> TypeDescDict;	
	
private:
	rapidxml::xml_node<> *root;
	
	void load_type_desc_dict() {
		load_subnodes_dict<XMLTypeDesc>(root, "TypeDesc", "Type", "Id", TypeDescDict);
	}

	void clear() {
		clear_type_desc_dict();
	}

	void clear_type_desc_dict() {
		for (auto it = TypeDescDict.begin(); it != TypeDescDict.end(); ++it) {
			delete it->second;
		}
		TypeDescDict.clear();		
	}

	void dump_type_desc_dict() const {
		const unsigned int n = TypeDescDict.size();
		if (n) {			
			std::cout << "TypeDesc: " << "(" << n << ")" << std::endl;
			for (auto it = TypeDescDict.begin(); it != TypeDescDict.end(); ++it) {
				const std::string index(it->first);
				std::map<const std::string, XMLTypeDesc*>::const_iterator it2 = TypeDescDict.find(index);
				if (it2 != TypeDescDict.end()) {
					XMLItem* ptr = it2->second;
					std::cout << it->first << " -> ";
					ptr->dump();
				}
			}
		}
	}
};

#endif // __XML_DOCUMENT_LEGEND_HPP__	
