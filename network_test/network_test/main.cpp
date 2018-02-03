#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <string>
#include <iostream>
using namespace boost::asio;
using namespace std;

#include "client.h"

/** un Network Agent es como un corredor de bolsa, uno no puede interactuar en la bolsa sin uno.
/// La unica forma en de mantener una comunicacion en el programa es mediante un par de NetworkAgent 
/// que hagan de intermediarios,
/// uno en el cliente, otro en el servidor
***/



int main() {
	boost::asio::io_service ioService;

	Client client(&ioService);
	client.tryConnection("127.0.0.1", 8001);
	ioService.run();

	system("pause");
}