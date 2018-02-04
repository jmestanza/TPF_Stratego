#include "NetworkManager.h"



NetworkManager::NetworkManager(io_service *_service) : mySocket(*_service) , timer(*_service), ioService(_service){}

void NetworkManager::tryConnection(string host, int port) {
	ip::tcp::endpoint myEndPoint(ip::address::from_string(host), port);
	mySocket.async_connect(myEndPoint, boost::bind(&NetworkManager::handleConnect, this, _1));
	mt19937 g1(std::chrono::system_clock::now().time_since_epoch().count());
	timer.expires_from_now(boost::posix_time::millisec(g1()%waitRange+waitBase));
	timer.async_wait(boost::bind(&NetworkManager::handleTimeout, this, _1));
}
void NetworkManager::waitForConnection(int port) {
	ip::tcp::acceptor myAcceptor(*ioService,ip::tcp::v4(), port);
	myAcceptor.async_accept(mySocket, boost::bind(&NetworkManager::handleConnect,this,_1));
}
void NetworkManager::send(string msg) {
	copy(msg.begin(), msg.end(), writeBuffer);
	mySocket.async_write_some(buffer(writeBuffer, msg.size()),boost::bind(&NetworkManager::handleSent,this,_1,_2));
}

void NetworkManager::handleConnect(const boost::system::error_code& error) {
	if (error) { onConnFailed(error.message()); return; }

	onConnect();
	mySocket.async_read_some(buffer(readBuffer), boost::bind(&NetworkManager::handleRecv, this, _1, _2));
}
void NetworkManager::handleRecv(const boost::system::error_code& error, size_t bytes) {
	if (error) { onLostConnection(error.message()); return; }
	string ans(readBuffer);
	onRecv(ans);
	mySocket.async_read_some(buffer(readBuffer), boost::bind(&NetworkManager::handleRecv, this, _1, _2));
}
void NetworkManager::handleSent(const boost::system::error_code& error, size_t bytes) {
	if (error) { onLostConnection(error.message()); return; }
	onSent();
}
void NetworkManager::handleTimeout(const boost::system::error_code& error) {
	mySocket.close();
	onConnFailed("timeout waiting for a server");
}
NetworkManager::~NetworkManager() {}
