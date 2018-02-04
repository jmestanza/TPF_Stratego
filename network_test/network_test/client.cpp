
#include "client.h"

Client::Client(io_service* service) : mySocket(*service) , timer(*service){
	
}
string Client::GetIP() {
	return mySocket.remote_endpoint().address().to_string();
}
void Client::tryConnection(string host, int port) {
	ip::tcp::endpoint myEndPoint = ip::tcp::endpoint(ip::address::from_string(host), port);
	mySocket.async_connect(myEndPoint, boost::bind(&Client::connectAction, this, _1));
}
void Client::connectAction(const boost::system::error_code&e) {
	if (!e) {
		this->onConnect();
		cout << "reading ... " << '\n';
		//async_read(mySocket,boost::asio::buffer(readBuffer), boost::bind(&Client::readAction, this, _1,_2));
		mySocket.async_read_some(boost::asio::buffer(readBuffer), boost::bind(&Client::readAction, this, _1, _2));
	} else {
		cout << e.message() << '\n';
	}
}
void Client::readAction(const boost::system::error_code&e,size_t bytes) {
	if (!e) {
		string msg(readBuffer);
		onRecv(msg);
		mySocket.async_read_some(boost::asio::buffer(readBuffer), boost::bind(&Client::readAction, this, _1, _2));
	} else {
		cout << "Error: '" << e.message() << "'";
	}
}
void Client::onRecv(string msg) {
	cout << "new msg! : " << msg << '\n';
}
void Client::send(string msg) {
	copy(msg.begin(), msg.end(), writeBuffer);
	mySocket.async_write_some(boost::asio::buffer(writeBuffer,msg.size()), boost::bind(&Client::sendAction, this, _1, _2));
}
void Client::sendAction(const boost::system::error_code &e,size_t bytes) {
	if (!e) {
		cout << "msg of size "<<bytes<<" sent! " << '\n';
	} else {
		cout << "error sending msg \n";
	}
}
void Client::onConnect() { 
	cout << "established connection\n";
	send("hello from client! ");
}