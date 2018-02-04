#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <iostream>
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/io_service.hpp"
#include "boost/bind.hpp"
#include "boost/asio.hpp"
#include "boost/asio/read.hpp"

using namespace std;
using namespace boost::asio;

const int bufferSize = 1024;
class Client {
	public:
		Client(io_service *service);
		void tryConnection(string host, int port);
		virtual void onRecv(string msg);
		virtual void onConnect();
		void send(string msg);
		void connectAction(const boost::system::error_code& error);
		void readAction(const boost::system::error_code& error, size_t bytes);
		void sendAction(const boost::system::error_code& error, size_t bytes);
		string GetIP();
	private:
		void (*_onRecv)(string msg); // actions when we recive message
		

		ip::tcp::socket mySocket;
		
		char readBuffer[bufferSize],writeBuffer[bufferSize];
		
};

#endif