#pragma once

#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/deadline_timer.hpp"
#include "client.h"
#include <map>
#include <string>
using namespace std;
using namespace boost::asio;

const int maxMsg = 1024;

class ClientTalk {
	public:
		ClientTalk(io_service *service);
		void start();
		void stop();
		
		bool started();
		void onRead();
		void onLogin();
		void onPing();

		ip::tcp::socket getSocket();
		string username();
		void setClientsChanged();
	private:
		ip::tcp::socket mySocket;
		char readBuffer[maxMsg];
		char writeBuffer[maxMsg];
		bool _started;
		string _username;
		//deadline_timer timer;
		io_service *service;
		//boost::posix_time::ptime last_ping;
		bool clientsChanged;
		
};

/**** Esta clase tiene la capacidad de interactuar con muchos clientes distintos 
***/
class Server {
	public:
		Server(io_service* service);
		void Listen(int port);
		void recv(void (*func)(string,string));
		
		Client* getClient(string);
		virtual void onNewConnection();
		void handleConnection(ClientTalk *client, const error_code &err);

	private:
		map <string, ClientTalk*> clients;
		ip::tcp::acceptor myAcceptor;
		
		io_service *service;
		~Server();
};
