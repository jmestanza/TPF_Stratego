#pragma once

class PosType // Utilizado solo por objetos tipo "Token"
{
public:
	PosType();

	bool operator== (PosType p1) {
		if ((p1.x == this->x) && (p1.y == this->y)) {
			return true;
		}
		else {
			return false;
		}
	}

	~PosType();
	unsigned char x; /// Rango de validez: {A-B-C-D-E-F-G-H-I-J}
	unsigned char y; /// Rango de validez: {1-2-3-4-5-6-7-8-9-10}
};

