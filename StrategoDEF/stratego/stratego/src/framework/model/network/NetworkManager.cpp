#include "networkManager.h"

NetworkManagerException::NetworkManagerException(string _err) : err(_err) {

}
const char * NetworkManagerException::what() const throw() {
	return err.c_str();
}

NetworkManager::NetworkManager(io_service *_service) : timer(*_service), myAcceptor(*_service), ioService(_service){
	flagWaiting = 0;
	connected = 0;
	failure = 0;
	timerOn = 0;
}
void NetworkManager::tryConnection(string host, int port, int timeout) {
	if (this->connected) {
		throw NetworkManagerException("Network error trying connect when we are already connected \n");
	}
	try {
		mySocket.reset(new boost::asio::ip::tcp::socket(*ioService));
		failure = 0;
		ip::tcp::endpoint myEndPoint(ip::address::from_string(host),port);
		mySocket->async_connect(myEndPoint,boost::bind(&NetworkManager::handleConnect,this,_1));
		//mt19937 g1(std::chrono::system_clock::now().time_since_epoch().count());
		//timer.cancel();
		timerOn = 1;
		timer.expires_from_now(boost::posix_time::millisec(timeout));
		timer.async_wait(boost::bind(&NetworkManager::handleTimeout,this));
	}catch(boost::exception &e) {
		throw NetworkManagerException("Boost error!");
	}
}
void NetworkManager::waitForConnection(int port) {
	if (this->connected) {
		throw NetworkManagerException("Network error trying to wait for connection when we are already connected \n");
	}
	mySocket.reset(new boost::asio::ip::tcp::socket(*ioService));
	failure = 0;
	myAcceptor = ip::tcp::acceptor(*ioService, ip::tcp::endpoint(ip::tcp::v4(), port));
	myAcceptor.async_accept(*mySocket,boost::bind(&NetworkManager::handleConnect,this,_1));
	
}
void NetworkManager::send(string msg) {
	copy(msg.begin(), msg.end(), writeBuffer);
	mySocket->async_write_some(buffer(writeBuffer, msg.size()),boost::bind(&NetworkManager::handleSent,this,_1,_2));
}
void NetworkManager::setRecvTimeout(int timeout) {
	if (flagWaiting) {
		throw NetworkManagerException("network error: recv timeout already started\n");
	}
	flagWaiting = 1;
	timerOn = 1;
	timer.expires_from_now(boost::posix_time::millisec(timeout));
	timer.async_wait(boost::bind(&NetworkManager::handleRecvTimeout, this, _1));
}
void NetworkManager::handleConnect(const boost::system::error_code& error) {
	if (error || failure) {
		failure = 1;
		connected = 0;
		mySocket->close();
		timerOn = 0; timer.cancel();
		onConnFailed(error.message());
		return;
	}
	connected = 1;
	onConnect();
	mySocket->async_read_some(buffer(readBuffer), boost::bind(&NetworkManager::handleRecv, this, _1, _2));
}
void NetworkManager::handleRecv(const boost::system::error_code& error, size_t bytes) {
	if (error) { mySocket->close(); onLostConnection(error.message()); return; }
	flagWaiting = 0;
	string ans(readBuffer, bytes);
	onRecv(ans);
	mySocket->async_read_some(buffer(readBuffer), boost::bind(&NetworkManager::handleRecv, this, _1, _2));
}
void NetworkManager::handleSent(const boost::system::error_code& error, size_t bytes) {
	if (error) { onLostConnection(error.message()); return; }
	onSent();
}
void NetworkManager::handleTimeout() {
	if (connected || !timerOn) return;
	timerOn = 0;
	failure = 1;
	mySocket->close();
	onConnFailed("timeout waiting for a server");
}
void NetworkManager::handleRecvTimeout(const boost::system::error_code& error) {
	if (!flagWaiting || !timerOn) return;
	timerOn = 0;
	mySocket->close();
	onLostConnection("timout waiting for answer");
	flagWaiting = 0;
	connected = 0;
}
NetworkManager::~NetworkManager() {}
