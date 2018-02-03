#include "server.h"



Server::Server(io_service *_service) : myAcceptor(*_service) , service(_service){
	
}
void Server::Listen(int port) {
	Client *newClient = new Client(service);
	newClient->_onConnect = [this](Client* client_pnt) {
		
	};
	newClient->setConnection(myAcceptor);

}
void Server::onNewConnection(void(*func)(string)) { _onNewConnection = func; }


Server::~Server() {
	/// close all connections instantly!
}
Client* Server::getClient(string client) {
	return clients[client];
}
