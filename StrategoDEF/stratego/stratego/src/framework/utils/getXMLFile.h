#pragma once

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
using namespace std;
using boost::property_tree::ptree;

/// Convertir un archivo XML en un ptree de boost

class XMLException : public exception {
	private:
		string err;
	public:
		XMLException(string err);
		virtual const char *what() const throw();
};


void getXMLFile(ptree &tree,string dir);