#include "server.h"


ClientTalk::ClientTalk(io_service *_service) : mySocket(*_service) {

}
void ClientTalk::start() {

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
	cout << "client connected! " << '\n';
	client->start();
	ClientTalk *clientTalk = new ClientTalk(service);
	myAcceptor.async_accept(clientTalk->mySocket,boost::bind(&Server::handleConnection, this, clientTalk, _1));
}
void Server::onNewConnection() {

}
Server::~Server() {
	/// close all connections instantly!
}

