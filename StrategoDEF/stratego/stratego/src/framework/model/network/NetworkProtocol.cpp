#include "NetworkProtocol.h"

NetworkProtocolException::NetworkProtocolException(string _err) : err(_err){

}
const char * NetworkProtocolException::what() const throw(){
	return ("NetworkProtocolException:"+err).c_str();
}

NetworkProtocol::NetworkProtocol(io_service* service) : NetworkManager(service){
	debugFlag = 0;
}
void NetworkProtocol::setDebugFlag() {
	debugFlag = 1;
}
void NetworkProtocol::ParseProtocolXML(string filename) {
	ifstream is;
	try {
		is = ifstream(filename);
	}catch (ifstream::failure &e) {
		throw NetworkProtocolException("Error loading network protocol xml file");
	}
	using boost::property_tree::ptree;
	ptree pt;
	try {
		read_xml(is, pt);
	}catch (boost::property_tree::xml_parser::xml_parser_error &e){
		throw NetworkProtocolException("Error parsing network protocol xml file");
	}
	if (pt.count("protocol") != 1) {
		throw NetworkProtocolException("Invalid protocol xml file, number different 1 of protocol tags");
	}
	ptree content = pt.get_child("protocol");
	for (auto it = content.begin(); it != content.end(); ++it) {
		if (it->first == "package") {
			if (it->second.get_child("<xmlattr>").count("name") != 1) {
				throw NetworkProtocolException("Invalid protocol xml file, invalid count 'name'");
			} else if (it->second.get_child("<xmlattr>").count("code") != 1) {
				throw NetworkProtocolException("Invalid protocol xml file, invalid count 'code'");
			}
			string name  = it->second.get<string>("<xmlattr>.name");
			string sCode = it->second.get<string>("<xmlattr>.code");
			std::stringstream ss;
			ss << sCode << hex;
			unsigned int code; ss >> code;

			Package *pkg = new Package(name, code);

			for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				string v = it2->first;
				if (it2->first == "msg") {
					if (it2->second.get_child("<xmlattr>").count("title") != 1) {
						throw NetworkProtocolException("Invalid xml file: invalid count 'title'");
					} else if (it2->second.get_child("<xmlattr>").count("size") != 1) {
						throw NetworkProtocolException("Invalid xml file: invalid count 'size'");
					}
					string title = it2->second.get<string>("<xmlattr>.title");
					string sSize = it2->second.get<string>("<xmlattr>.size");
					int size = stoi(sSize);
					pkg->addContent(title, size);
				} else if (it2->first == "<xmlattr>") {
				} else {
					throw NetworkProtocolException("Invalid protocol xml, invalid tag (expected 'msg')");
				}
			}
			if (debugFlag) {
				cout << "debug: " << "added package " << name << ' ' << code << '\n';
			}
			createNewPackage(pkg);
		} else if(it->first == "<xmlattr>"){
		} else {
			throw NetworkProtocolException("Invalid protocol xml file, invalid tag (expected 'package')");
		}
	}
}
void NetworkProtocol::createNewPackage(Package *pkg) {
	if (pkgByCode.find(pkg->getHead()) != pkgByCode.end()){
		throw NetworkProtocolException("Fatal error: trying to add two packages with same code '"+ to_string(pkg->getHead())+"'");
	}
	if (pkgByName.find(pkg->getName()) != pkgByName.end()) {
		throw NetworkProtocolException("Fatal error: trying to add two packages with same name '"+pkg->getName()+"'");
	}
	pkgByCode[pkg->getHead()] = pkgByName[pkg->getName()] = pkg;
}
void NetworkProtocol::createPackages(vector <Package*> pkgList) {
	for (int i = 0; i < pkgList.size(); i++) createNewPackage(pkgList[i]);
}
void NetworkProtocol::sendPackage(string pkgName, map <string, string> &content) {
	/// Frist we verify package is in a correct format
	if (pkgByName.find(pkgName) == pkgByName.end()) {
		throw NetworkProtocolException("Fatal error: trying to send invalid package, invalid head");
	}
	Package *package = pkgByName[pkgName];
	/// check each pacakge field is present
	string val;
	try {
		package->encode(content, val);
	} catch (PackageException &e) {
		throw NetworkProtocolException("Fatal error: trying to send invalid package");
	}
	this->send(val);
}
void NetworkProtocol::onRecv(string &msg) {
	if (msg.size() == 0) {
		throw NetworkProtocolException("Fatal error: invalid package received, length 0");
	}
	unsigned char packageType = (unsigned char)msg[0];
	if (pkgByCode.find(packageType) == pkgByCode.end()) {
		throw NetworkProtocolException("Fatal error: invalid package type received ");
	}
	map <string, string> content;
	Package *package = pkgByCode[packageType];
	try {
		package->decode(msg, content);
	} catch (PackageException &e) {
		cout << e.what() << '\n';
		throw NetworkProtocolException("Fatal error: can not decode package");
	}
	string packageName = package->getName();
	this->onPackageRecv(packageName, content);
}
NetworkProtocol::~NetworkProtocol() {
	for (auto it = pkgByName.begin(); it != pkgByName.end(); it++) delete it->second;
}
