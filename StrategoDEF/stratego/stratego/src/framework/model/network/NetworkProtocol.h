#pragma once

#include "Package.h"
#include "NetworkManager.h"
#include <fstream>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
using namespace boost::asio;
using namespace std;

/*
Aqui se encuentra programado NetworkProtocol:
Su funcion principal es amplicar las funcionalidades de NetworkManager 
para que funcione mediante envios/recepciones de packetes en forma de un map<string,string>
que sean codificados y decodificados segun corresponda.

Los map son validados constantemente para verificar si cumplen el formato del protocolo,
que se encuentra cargado en un archivo xml

La idea es que otra clase de network herede de NetworkProtocol y sobre-escriba las funciones
que se llaman cuando llegan mensajes con el funcionamiento particular
*/

class NetworkProtocolException : public exception {
	private:
		string err;
	public:
		NetworkProtocolException(string err);
		virtual const char *what() const throw();
};

class NetworkProtocol : public NetworkManager{
	public:
		NetworkProtocol(io_service *service);
		void ParseProtocolXML(string filename); // load protocol from xml file
		void createNewPackage(Package *pkg); // crear un tipo de paquete para el protocolo
		void createPackages(vector <Package*> pkg);
		void sendPackage(string pkgName, map <string,string> &content); // enviar un paquete
		void onRecv(string &msg); 
		void setDebugFlag();

		virtual void onPackageRecv(string &PkgName, map<string, string> &content) = 0; // para ser sobre-escrito
		// con funcionamiento particular de una clase de network
		~NetworkProtocol();
	private:
		map <unsigned char, Package*> pkgByCode; // packages indexed by code
		map <string, Package*> pkgByName; // indexamiento de packetes
		int debugFlag;
};

