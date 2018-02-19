#pragma once
#include <iostream>
#include "boost/bind.hpp"
#include "boost/asio.hpp"
#include "boost/scoped_ptr.hpp"

/*
NetworkManager:
Esta clase, considerada formalmente parte del modelo interactua con boost de manera asincronica
para poder 

- Esperar que un cliente se conecte
- Intentar conectarse a un servidor
- Enviar packetes
- LLamar a callbacks cuando llegan packetes (la idea es hacer otra clase que herede de netorkManager
y que dicha clase sobre-escriba metodos virtuales de NetworkManager y coloque alli lo que 
se quiera que suceda cuando un packete llega)
- Llamar a callbacks si se pierde conexion o si no se puede conectar

*/

using namespace boost::asio;
using namespace std;

const int bufferSize = 1024;

class NetworkManagerException : public exception {
	private:
		string err;
	public:
		NetworkManagerException(string err);
		virtual const char *what() const throw();
};

class NetworkManager {
	public:
		NetworkManager(io_service* service);
		~NetworkManager();

		/*** External use ***/
		void tryConnection(string host, int port, int timeout); // tomamos la iniciativa buscando una conexion
		void waitForConnection(int port); // esperamos una conexion. (asincronicamente)
		void send(string msg);
		void setRecvTimeout(int timeout); // max time to wait for message
		void closeConnection();
		int getConnected();
		/*** Override functions ***/
		virtual void onConnect() = 0; // conexion establecida
		virtual void onConnFailed(string err) = 0; // conexion fallada
		virtual void onRecv(string &msg) = 0; // packete recibido
		virtual void onSent() = 0;
		virtual void onLostConnection(string err) = 0; // conexion perdida

	private:
		//// Variables de boost 
		boost::scoped_ptr<boost::asio::ip::tcp::socket> mySocket;
		ip::tcp::acceptor myAcceptor;
		io_service *ioService;
		char readBuffer[bufferSize], writeBuffer[bufferSize];
		bool connected;

		boost::posix_time::ptime last_ping;
		deadline_timer timer;
		int timeoutRecv, flagWaiting , failure;
		int timerOn;
		bool acceptorOn;
		/*** Funciones internas: se le pasan a boost para que llamen a las funciones para sobre-escribir ***/
		void handleConnect(const boost::system::error_code& error);
		void handleRecv(const boost::system::error_code& error, size_t bytes);
		void handleSent(const boost::system::error_code& error, size_t bytes);
		void handleTimeout();
		void handleRecvTimeout(const boost::system::error_code& error);
};