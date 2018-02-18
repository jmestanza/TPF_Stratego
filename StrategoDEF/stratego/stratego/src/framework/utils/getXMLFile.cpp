#include "getXMLFile.h"


XMLException::XMLException(string _err) : err("XMLException: " + _err) {

}
const char * XMLException::what() const throw() {
	return err.c_str();
}

void getXMLFile(ptree &tree,string dir) {
	ifstream is;
	try {
		is = ifstream(dir);
	} catch (ifstream::failure &e) {
		throw XMLException("could not open '" + dir + "'");
	}
	try {
		read_xml(is,tree);
	} catch (boost::property_tree::xml_parser::xml_parser_error &e) {
		throw XMLException("Error parsing xml file '" + dir + "'");
	}
}