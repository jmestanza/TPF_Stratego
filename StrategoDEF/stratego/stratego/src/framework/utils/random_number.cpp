#include "random_number.h"
#include "getMillisFromEpoch.h"

mt19937 random_g1 = mt19937(std::chrono::system_clock::now().time_since_epoch().count());

int randomNumber() {
	return random_g1();
}
int randrange(int a,int b) {
	int val = abs( randomNumber() );
	return val % (b-a) + a;
}