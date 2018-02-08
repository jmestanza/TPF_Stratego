#include "random_number.h"


mt19937 random_g1 = mt19937(std::chrono::system_clock::now().time_since_epoch().count());;

int randomNumber() {
	return random_g1();
}