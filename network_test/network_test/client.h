#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <iostream>
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/io_service.hpp"
#include "boost/bind.hpp"

using namespace std;
using namespace boost::asio;

class Client {
	public:
		Client(io_service *service);
		void tryConnection(string host, int port);
		void setConnection(ip::tcp::acceptor &acceptor);
		void onRecv(void (*onRecv)());
		void onConnect(void (*func)(Client*));
		void connectAction(const boost::system::error_code& error);
		void(*_onConnect)(Client *myPnt);
	private:
		void (*_onRecv)(string msg); // actions when we recive message
		

		ip::tcp::socket mySocket;
		
		
};

#endif