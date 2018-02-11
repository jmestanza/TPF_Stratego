#include "getMillisFromEpoch.h"

long long getMillisFromEpoch(){
	return std::chrono::system_clock::now().time_since_epoch() /
	std::chrono::milliseconds(1);
}