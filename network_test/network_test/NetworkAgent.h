#ifndef NETWORK_AGENT
#define NETWORK_AGENT


#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/io_service.hpp"

using namespace std;
using namespace boost::asio;

/// Un networkAgent es como un corredor de bolsa
/// Uno no puede participar en la bolsa sin uno
/// De la misma forma, uno no puede establecer la comunicacion sin un
/// par client/servidor de agentes de network

class NetworkAgent {

	public:
		NetworkAgent(io_service *);
		/// Callbacks!
		void onRecv(void (*func)(string));
		/// acciones comunes!
		void send(string);
	private:
		
		void (*_onRecv)(string); /// cuando llega un nuevo mensaje

		/**** internal functionalities ***/
		io_service *ioService;
		ip::tcp::socket socket;
};


#endif