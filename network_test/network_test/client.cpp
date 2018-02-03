
#include "client.h"

Client::Client(io_service* service) : mySocket(*service){
	this->_onConnect = NULL;
}

void Client::tryConnection(string host, int port) {
	ip::tcp::endpoint myEndPoint = ip::tcp::endpoint(ip::address::from_string(host), port);
	mySocket.async_connect(myEndPoint, boost::bind(&Client::connectAction, this, _1));
}
void Client::setConnection(ip::tcp::acceptor &acceptor) {
	acceptor.async_accept(this->mySocket, bind(&Client::connectAction,this, _1));
}
void Client::connectAction(const boost::system::error_code&e) {
	if (!e) {
		if (this->_onConnect != NULL) this->_onConnect(this);
	}
}
void Client::onConnect(void(*func)(Client*)) { _onConnect = func;  }