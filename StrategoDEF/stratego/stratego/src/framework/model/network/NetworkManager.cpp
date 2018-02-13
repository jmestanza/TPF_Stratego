#include "networkManager.h"

#define BOOST_ASIO_ENABLE_CANCELIO 1
#pragma warning(disable : 4996)

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
	acceptorOn = 0;
}
void NetworkManager::tryConnection(string host, int port, int timeout) {

	cout << "[Network Manager]Try conenction\n";
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
		//timer.expires_from_now(boost::posix_time::millisec(timeout));
		//timer.async_wait(boost::bind(&NetworkManager::handleTimeout,this));
	}catch(boost::exception &e) {
		throw NetworkManagerException("Boost error!");
	}
}
void NetworkManager::waitForConnection(int port) {

	cout << "[Network Manager]Wait for connection\n";
	if (this->connected) {
		throw NetworkManagerException("Network error trying to wait for connection when we are already connected \n");
	}
	mySocket.reset(new boost::asio::ip::tcp::socket(*ioService));
	failure = 0;
	acceptorOn = 1;
	myAcceptor = ip::tcp::acceptor(*ioService,ip::tcp::endpoint(ip::tcp::v4(),port));
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
	//flagWaiting = 1;
//	timerOn = 1;
	//timer.expires_from_now(boost::posix_time::millisec(timeout));
	//timer.async_wait(boost::bind(&NetworkManager::handleRecvTimeout, this, _1));
}
void NetworkManager::handleConnect(const boost::system::error_code& error) {
	cout << "[Network Manager]Call handle connect \n";
	if (error || failure) {
		cout << "[Network Manager]coneccion fallada\n";

		closeConnection();

		failure = 1;
		connected = 0;
		/*mySocket->cancel();
		mySocket->close();
		boost::system::error_code error;
		timerOn = 0; timer.cancel();*/
		onConnFailed(error.message());
		return;
	}
	cout << "[Network Manager]conexion establecida \n";
	connected = 1;

	onConnect();
	mySocket->async_read_some(buffer(readBuffer), boost::bind(&NetworkManager::handleRecv, this, _1, _2));
}
void NetworkManager::handleRecv(const boost::system::error_code& error, size_t bytes) {
	cout << "[Network Manager]mensaje recibido \n";
	if (error) {
		cout << "[Network Manager]lost conenction \n";
		closeConnection();
		connected = 0;
		/*mySocket->cancel();
		mySocket->close(); 
		mySocket.reset(new boost::asio::ip::tcp::socket(*ioService));
		boost::system::error_code error;*/
		
		//mySocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);

		onLostConnection(error.message()); return; 
	}
	flagWaiting = 0;
	string ans(readBuffer, bytes);
	onRecv(ans);
	mySocket->async_read_some(buffer(readBuffer), boost::bind(&NetworkManager::handleRecv, this, _1, _2));
}
void NetworkManager::handleSent(const boost::system::error_code& error, size_t bytes) {
	cout << "[Network Manager]Mensaje enviado \n";
	if (error) { 
		connected = 0;
		boost::system::error_code error;
		//mySocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both,error);
		onLostConnection(error.message()); return; 
	}
	onSent();
}
void NetworkManager::handleTimeout() {
	cout << "[Network Manager]Timeout\n";
	if (connected || !timerOn) return;
	timerOn = 0;
	failure = 1;
	connected = 0;
	mySocket->cancel();
	mySocket->close();
	onConnFailed("timeout waiting for a server");
}
void NetworkManager::handleRecvTimeout(const boost::system::error_code& error) {
	if (!flagWaiting || !timerOn) return;
	timerOn = 0;
	mySocket->cancel();
	mySocket->close();

	boost::system::error_code error2;
	//mySocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both,error2);
	flagWaiting = 0;
	connected = 0;
	onLostConnection("timout waiting for answer");
	
}
void NetworkManager::closeConnection() {
	cout << "[Network Manager]Close connection\n";
	if (connected) {

		boost::system::error_code error;
		mySocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
		cout << "cancel async! "<<'\n';
		mySocket->cancel();
		mySocket->close();
		//mySocket.reset(new boost::asio::ip::tcp::socket(*ioService));

		timerOn = 0;
		flagWaiting = 0;
		connected = 0;
		if (acceptorOn) {
			cout << "closing acceptor !";
			acceptorOn = 0;
			myAcceptor.cancel();
			myAcceptor.close();
		}
	}
}
NetworkManager::~NetworkManager() {}
