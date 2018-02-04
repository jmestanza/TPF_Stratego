#include "server.h"


ClientTalk::ClientTalk(io_service *_service) : mySocket(*_service) {

}
void ClientTalk::start() {
	mySocket.async_read_some(buffer(readBuffer), boost::bind(&ClientTalk::readAction, this, _1, _2));
}
void ClientTalk::send(string msg) {
	copy(msg.begin(), msg.end(), writeBuffer);
	mySocket.async_write_some(buffer(writeBuffer, msg.size()), boost::bind(&ClientTalk::sentAction,this,_1,_2));
}
void ClientTalk::readAction(const boost::system::error_code& error, size_t bytes_transferred) {
	string msg(readBuffer);
	onRecv(msg);
	mySocket.async_read_some(buffer(readBuffer), boost::bind(&ClientTalk::readAction, this, _1, _2));
}
void ClientTalk::onRecv(string msg) {
	//cout << "msg received !: " << msg << '\n';
}
void ClientTalk::sentAction(const boost::system::error_code& error, size_t bytes_transferred) {
	//cout << "message of size " << bytes_transferred << " sent " << '\n';
}
string ClientTalk::getIP() {
	return mySocket.remote_endpoint().address().to_string();
}
Server::Server(io_service *_service) : service(_service) , myAcceptor(*_service){
	service = _service;
}
void Server::Listen(int port) {
	cout << "listening " << port << '\n';
	myAcceptor = ip::tcp::acceptor(*service,ip::tcp::endpoint(ip::tcp::v4(), port));

	ClientTalk *clientTalk = new ClientTalk(service);
	myAcceptor.async_accept(clientTalk->mySocket,boost::bind(&Server::handleConnection, this, clientTalk, _1));

}
void Server::handleConnection(ClientTalk *client, const error_code &err) {
	//cout << "client connected! " << '\n';
	//cout << "IP Adress: " << client->getIP() << '\n';
	clients[client->getIP()] = client;
	client->start();
	ClientTalk *clientTalk = new ClientTalk(service);
	myAcceptor.async_accept(clientTalk->mySocket,boost::bind(&Server::handleConnection, this, clientTalk, _1));
}
void Server::onNewConnection() {

}
Server::~Server() {
	/// close all connections instantly!
}

