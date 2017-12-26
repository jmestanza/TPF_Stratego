#pragma once

class PosType // Utilizado solo por objetos tipo "Token"
{
public:
	PosType();
	~PosType();
	unsigned char x; /// Rango de validez: {A-B-C-D-E-F-G-H-I-J}
	unsigned char y; /// Rango de validez: {1-2-3-4-5-6-7-8-9-10}
};

