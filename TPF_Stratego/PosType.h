#pragma once

class PosType // Used by "Token" type objects only
{
public:
	PosType();
	PosType get_token_pos();
	void set_token_pos(unsigned char new_x, unsigned new_y);
	~PosType();
private:
	unsigned char x; /// Range: {A-B-C-D-E-F-G-H-I-J}
	unsigned char y; /// Range: {1-2-3-4-5-6-7-8-9-10}
};

