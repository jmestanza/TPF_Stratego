#include "Package.h"

PackageException::PackageException(string err) : logic_error(err) {

}
string PackageException::what() {
	return logic_error::what();
}

Msg::Msg(string _name,int _length) : name(_name) , length(_length){}

Package::Package(string _name,int _head) : name(_name) ,headCode(_head){}

void Package::addContent(string _name,int _length) {
	content.push_back(Msg(_name, _length));
}
void Package::encode(map<string, string> &input,string &ans) {
	if (content.size() != input.size()) {
		throw PackageException("Length of encoding package is not valid");
	}
	ans.push_back((unsigned char)this->headCode);
	for (int i = 0; i < content.size(); i++) {
		string &fieldValue = input[content[i].name];
		if (content[i].length != -1 && content[i].length != fieldValue.size()) {
			throw PackageException("Trying to encode invalid package");
		}
		if (input[content[i].name].size() == 0) {
			throw PackageException("Trying to encode an empty package field");
		}
		for (int i = 0; i < fieldValue.size(); i++) ans.push_back(fieldValue[i]);
	}
}
void Package::decode(string &value,map<string,string> &answer) {
	if (value.size() == 0) {
		throw PackageException("Error: trying to decode package of no length");
	}
	if (value[0] != headCode) {
		throw PackageException("Error: head of package value is not valid");
	}
	int pnt = 1;
	for (int i = 0; i < content.size(); i++) {
		if (content[i].length == -1 && i != content.size() - 1) {
			throw PackageException("Error: package has a variable size length that is not final field");
		}
		if (pnt + content[i].length > value.size()) {
			throw PackageException("Error: package is too short");
		}
		string current;
		if (content[i].length == -1){
			current = value.substr(pnt, value.size() - pnt);
		} else {
			current = value.substr(pnt, content[i].length);
		}
		answer[content[i].name] = current;
		pnt += current.size();
	}
	if (pnt != value.size()) {
		throw PackageException("Error: invalid package size");
	}
}
string Package::getName() {
	return this->name;
}
unsigned char Package::getHead() {
	return this->headCode;
}