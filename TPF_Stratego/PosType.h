#pragma once

class PosType // Utilizado solo por objetos tipo "Token"
{
public:
	PosType();
	~PosType();
	unsigned char x; /// Rango de validez: {A-B-C-D-E-F-G-H-I-J}
	unsigned char y; /// Rango de validez: {1-2-3-4-5-6-7-8-9-10}
};

bool operator== (PosType p1, PosType p2) {
	if ((p1.x == p2.x) && (p1.y == p2.y)) {
		return true;
	}
	else {
		return false;
	}
}