
#include "client.h"

Client::Client(io_service* service) : mySocket(*service){
	
}

void Client::tryConnection(string host, int port) {
	ip::tcp::endpoint myEndPoint = ip::tcp::endpoint(ip::address::from_string(host), port);
	mySocket.async_connect(myEndPoint, boost::bind(&Client::connectAction, this, _1));
}
void Client::connectAction(const boost::system::error_code&e) {
	if (!e) {
		this->onConnect();
	} else {
		cout << e.message() << '\n';
	}
}
void Client::onConnect() { 
	cout << "established connection\n";
}