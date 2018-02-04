#pragma once

#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/deadline_timer.hpp"
#include "boost/asio/io_service.hpp"
#include "boost/bind.hpp"
#include <map>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <thread>       
#include <chrono> 

using namespace std;
using namespace boost::asio;

const int maxMsg = 1024;

class ClientTalk {
public:
	ClientTalk(io_service *service);
	void start();
	void send(string msg);
	virtual void onRecv(string msg);
	void sentAction(const boost::system::error_code& error,size_t bytes_transferred);
	void readAction(const boost::system::error_code& error, size_t bytes_transfered);
	ip::tcp::socket getSocket();
	string getIP();
	void setClientsChanged();

	friend class Server;
private:
	ip::tcp::socket mySocket;
	char readBuffer[maxMsg], writeBuffer[maxMsg];
	//deadline_timer timer;
	io_service *service;
	boost::posix_time::ptime last_ping;
	deadline_timer timer;
	bool clientsChanged;

};

/**** Esta clase tiene la capacidad de interactuar con muchos clientes distintos
***/
class Server {
public:
	Server(io_service* service);
	void Listen(int port);
	void recv(void(*func)(string, string));
	virtual void onNewConnection();
	void handleConnection(ClientTalk *client, const error_code &err);
	
	~Server();
	
private:
	map <string, ClientTalk*> clients;
	ip::tcp::acceptor myAcceptor;



	io_service *service;
	
};
