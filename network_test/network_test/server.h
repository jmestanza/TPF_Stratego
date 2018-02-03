#pragma once
#ifndef SERVER_H
#define SERVER_H

#include "NetworkAgent.h"
#include "boost/asio/ip/tcp.hpp"
#include "client.h"
#include <map>
using namespace std;
using namespace boost::asio;

/**** Esta clase tiene la capacidad de interactuar con muchos clientes distintos 
***/
class Server {
	public:
		Server(io_service* service);
		void Listen(int port);
		void recv(void (*func)(string,string));
		Client* getClient(string);

	private:
		map <string, Client*> clients;
		ip::tcp::acceptor myAcceptor;

		void (*_onNewConnection)(string);
		void (*_recv(string,string));		

		void onNewConnection(void(*func)(string));
		io_service *service;
		~Server();
};


#endif

