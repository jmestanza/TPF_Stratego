#pragma once

class PosType // Used by "Token" type objects
{
public:
	PosType();
	PosType get_token_pos();
	void set_token_pos(unsigned char new_col, unsigned new_row);
	~PosType();
private:
	unsigned char col; /// Range: {A-B-C-D-E-F-G-H-I-J}
	unsigned char row; /// Range: {1-2-3-4-5-6-7-8-9-10}
};

