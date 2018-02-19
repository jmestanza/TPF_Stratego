#pragma once

/* Package: Aqui se estructura todo lo que tienen en comun los packetes de comunicacion */
/* El contenido de cada mensage*/
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

/// Esta excepcion se llama fundamentalmente cuando hay errores de parseo del paquete
class PackageException : logic_error {
	public:
		PackageException(string err);
		string what();
};

class Msg {
	public:
		Msg(string _name, int _length); /// if length is -1 then the message size is variable
		string name;
		int length;
};

class Package {
	public:
		Package(string _name,int _head);
		void addContent(string _name, int _length);
		unsigned char getHead();
		string getName();

		void encode(map <string, string> &input,string &ans); /// codificar un packquete a partir de un map
		// map<string,string> => string para enviar

		void decode(string &value,map <string, string> &ans); /// decodificar un paquete en un map
		// string para enviar => map<string,string>
	private:
		string name;
		unsigned char headCode;
		vector <Msg> content;
};