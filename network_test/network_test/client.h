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
		void onRecv(void (*onRecv)());
		virtual void onConnect();
		void connectAction(const boost::system::error_code& error);
		
	private:
		void (*_onRecv)(string msg); // actions when we recive message
		

		ip::tcp::socket mySocket;
		
		
};

#endif