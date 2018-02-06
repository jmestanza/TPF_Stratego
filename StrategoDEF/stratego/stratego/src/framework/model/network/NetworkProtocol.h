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
		void createNewPackage(Package *pkg);
		void createPackages(vector <Package*> pkg);
		void sendPackage(string pkgName, map <string,string> &content);
		void onRecv(string &msg);
		void setDebugFlag();

		virtual void onPackageRecv(string &PkgName, map<string, string> &content) = 0;
		~NetworkProtocol();
	private:
		map <unsigned char, Package*> pkgByCode; // packages indexed by code
		map <string, Package*> pkgByName;
		int debugFlag;
};

