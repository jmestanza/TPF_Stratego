#include <boost/asio.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <network/NetworkProtocol.h>
#include <fstream>
using namespace boost::asio;

ostream& operator<< (ostream& os, map<string,string>&content) {
	cout << "{";
	for (auto it = content.begin(); it != content.end(); it++) {
		cout << it->first << ":" << it->second;
		if (it != prev(content.end())) cout << ",";
	}
	cout << "}";
	return os;
}


struct protocol : NetworkProtocol {
	bool mode;
	protocol(io_service* service) : NetworkProtocol(service){
		mode = 0;
	}
	void onPackageRecv(string &PkgName, map<string, string> &content) {
		cout << "new message! " << '\n';
		cout << "pack = " << PkgName << '\n';
		cout << content << '\n';
	}
	void onConnect() {
		cout << "Connection successful! " << '\n';
		map <string, string> data = { 
			{ "original_row","a" },
			{ "original_col","e" },
			{"destination_col","f"},
			{"destination_row","a"}
		};
		this->sendPackage("move",data);
	};
	void onConnFailed(string err) {
		if (mode == 0) {
			cout << "connection failed: " << err << '\n';
			cout << "trying as server" << '\n';
			this->waitForConnection(9999);
			mode = 1;
		} else {
			cout << err << '\n';
			cout << "conenction failed again \n";
		} 
	};
	void onLostConnection(string msg) {
		cout << "connection lost \n";
	}
	void onSent() {};
};

int main() {
	try {
		io_service service;
		
		protocol myProtocol(&service);
		myProtocol.setDebugFlag();
		ifstream is("xml/protocol.xml", ifstream::in);
		myProtocol.ParseProtocolXML(is);

		myProtocol.tryConnection("127.0.0.1", 9999, 2000);
		//myProtocol.waitForConnection(9999);
		while (1) {
			service.poll();
		}
	} catch (exception &e) {
		cout << "error: " << e.what() << '\n';
	} catch (...) {
		cout << "crazy " << '\n';
	}
	
	system("pause");
}
