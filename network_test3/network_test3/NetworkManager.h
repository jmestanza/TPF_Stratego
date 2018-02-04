#pragma once

/********

Este archivo contiene la clase NetworkManager, un "framework" para simplificar la interaccion 
con boost y su parte de red

Toda interaccion del programa en red se hara mediante un NetworkManager
sea servidor o cliente. Es el intermediario encargado de enviar y recibir toda comunicacion
Esto es equivalente a decir que, de la parte del juego del protocolo de red, es la de menor nivel.
******/

#include <string>
#include <chrono>
#include <random>
#include "boost/asio.hpp"
#include "boost/bind.hpp"

using namespace boost::asio;
using namespace std;

const int bufferSize = 1024;
const int waitRange = 3000;
const int waitBase = 2000;


class NetworkManager {
	public:
		NetworkManager(io_service* service);
		~NetworkManager();

		/*** External use ***/
		void tryConnection(string host, int port); // tomamos la iniciativa buscando una conexion
		void waitForConnection(int port); // esperamos una conexion. (asincronicamente)
		void send(string msg); 

		/*** Override functions ***/
		virtual void onConnect() = 0;
		virtual void onConnFailed(string err) = 0;
		virtual void onRecv(string msg) = 0;
		virtual void onSent() = 0;
		virtual void onLostConnection(string err) = 0;

	private:
		ip::tcp::socket mySocket;
		io_service *ioService;
		char readBuffer[bufferSize], writeBuffer[bufferSize];

		boost::posix_time::ptime last_ping;
		deadline_timer timer;

		/*** Internal functions ***/
		void handleConnect(const boost::system::error_code& error);
		void handleRecv(const boost::system::error_code& error, size_t bytes);
		void handleSent(const boost::system::error_code& error, size_t bytes);
		void handleTimeout(const boost::system::error_code& error);
};

