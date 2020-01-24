#ifndef __XMLUTL_HPP__
#define __XMLUTL_HPP__

#include <assert.h>

#include <exception>
#include <iostream>
#include <fstream>
#include <set>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"

inline const char* find_attribute_value(const char* name,
										const rapidxml::xml_node<>* root) {
	assert(root);
	assert(name);
	for (rapidxml::xml_attribute<> *a = root->first_attribute(name);
		 a;
		 a = a->next_attribute()) {
		if (STREQN(name, a->name(), a->name_size())) {
			return a->value();
		}
	}
		
	throw std::invalid_argument(std::string("Can't find attribute: ") + name);
} 

inline const char* find_attribute_value_option(const char* name,
											   const rapidxml::xml_node<>* root) {
	assert(root);
	assert(name);
	for (rapidxml::xml_attribute<> *a = root->first_attribute(name);
		 a;
		 a = a->next_attribute()) {
		if (STREQN(name, a->name(), a->name_size())) {
			return a->value();
		}
	}
		
	return "";
} 

inline std::vector<char>* read_binary_file (const std::string filename) {
	// binary mode is only for switching off newline translation
	std::ifstream file(filename, std::ios::binary);
	file.unsetf(std::ios::skipws);
	
	std::streampos file_size;
	unsigned int n = file_size;
	file.seekg(0, std::ios::end);
	file_size = file.tellg();
	file.seekg(0, std::ios::beg);
	
	std::vector<char>* vp = new std::vector<char>(n+1);
	vp->insert(vp->begin(),
			   std::istream_iterator<char>(file),
			   std::istream_iterator<char>());
	
	vp->push_back('\0');
		
	return vp;
}

template <class T>
T* find_subnode(const rapidxml::xml_node<>* root,
				const char* name) {
	assert(root);
	assert(name);
	T* ptr = 0;
	for (rapidxml::xml_node<>* node = root->first_node(name);
		 node;
		 node = node->next_sibling()) {
		if (STREQ(node->name(), name)) {
			ptr = new T(node);
			break;
		}
	}

	return ptr;
}

template <typename T>
void load_subnodes(const rapidxml::xml_node<>* root,
				   const char* name,
				   std::set<T*>& s) {
	assert(root);
	assert(name);
	for (rapidxml::xml_node<>* node = root->first_node(name);
		 node;
		 node = node->next_sibling()) {
		if (STREQ(node->name(), name)) {
			T* ptr = new T(node);
			s.insert(ptr);
		}
	}
}

template <typename T>
void load_subnodes_dict(const rapidxml::xml_node<>* root,
						const char* name,
						const char* index,
						std::map<const char*, T*>& m) {
	assert(root);
	assert(name);
	assert(index);	
	for (rapidxml::xml_node<>* node = root->first_node(name);
		 node;
		 node = node->next_sibling()) {
		if (STREQ(node->name(), name)) {
			T* ptr = new T(node);
			const char* value = find_attribute_value(index, node);
			m[value] = ptr;
		}
	}
}

template <typename T>
void load_subnodes_dict(const rapidxml::xml_node<>* root,
						const char* name,
						const char* i1,
						const char* i2,
						std::map<const std::string, T*>& m) {
	assert(root);
	assert(name);
	assert(i1);
	assert(i2);
	for (rapidxml::xml_node<>* node = root->first_node(name);
		 node;
		 node = node->next_sibling()) {
		if (STREQ(node->name(), name)) {
			T* ptr = new T(node);
			const char* v1 = find_attribute_value(i1, node);
			const char* v2 = find_attribute_value(i2, node);
			std::string index(v1);
			index += ".";
			index += v2;
			m.insert(std::pair<const std::string, T*>(index, ptr));
		}
	}
}

#endif // __XMLUTL_HPP__
