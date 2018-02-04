#pragma once

const int msg_size = 1024;

class NetworkManager {
public:
	NetworkManager();
	~NetworkManager();
private:
	//boost::posix_time::ptime last_ping;
	//deadline_timer timer;

	char readBuffer[msg_size], writeBuffer[msg_size];

};

