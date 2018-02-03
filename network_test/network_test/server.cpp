#include "server.h"


ClientTalk::ClientTalk(io_service *_service) : mySocket(*_service){

}
void ClientTalk::start() {

}
Server::Server(io_service *_service) : myAcceptor(*_service) , service(_service){
	service = _service;
	ClientTalk *clientTalk = new ClientTalk(_service);
	myAcceptor.async_accept(boost::bind(&Server::handleConnection,this,clientTalk,_1));
}
void Server::Listen(int port) {
	

}
void Server::handleConnection(ClientTalk *client, const error_code &err) {
	cout << "client connected! " << '\n';
	client->start();
	ClientTalk *clientTalk = new ClientTalk(service);
	myAcceptor.async_accept(boost::bind(&Server::handleConnection, this, clientTalk, _1));
}
void Server::onNewConnection() {

}
Server::~Server() {
	/// close all connections instantly!
}
Client* Server::getClient(string client) {
	return NULL;
}
