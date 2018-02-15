#include <stdio.h>
#include <tchar.h>
#include <vector>
#include "PosType.h"
using namespace std;

PosType::PosType(){
	/// Default create setting
	i = 100;
	j = 100;
}

PosType::PosType(int _i,int _j) : i(_i) , j(_j){}
PosType::PosType(pair<int,int> pos) : i(pos.first),j(pos.second) {}

PosType::~PosType(){}

