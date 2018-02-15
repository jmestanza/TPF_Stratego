#pragma once

#include <vector>
using namespace std;


class PosType // Utilizado solo por objetos tipo "Token"
{
public:
	PosType();
	PosType(int _i,int _j);
	PosType(pair<int,int> pos);

	bool operator== (PosType p1) {
		if ((p1.i == this->i) && (p1.j == this->j)) {
			return true;
		}
		else {
			return false;
		}
	}

	~PosType();
	int i; /// Rango de validez: {A-B-C-D-E-F-G-H-I-J}
	int j; /// Rango de validez: {1-2-3-4-5-6-7-8-9-10}
};

