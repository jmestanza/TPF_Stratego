#include "server.h"

int main() {
	boost::asio::io_service ioService;
	Server server(&ioService);
	server.Listen(8001);
	ioService.run();
}