#include "NetworkAgent.h"

using namespace boost::asio;

NetworkAgent::NetworkAgent(io_service *_ioService){
	ioService = _ioService;
	socket = ip::tcp::socket(*ioService);
}

void NetworkAgent::send(string msg) {

}
void NetworkAgent::onRecv(void(*func)(string)){ _onRecv = func;  }