#pragma once

#ifndef GET_KEY_H
#define GET_KEY_H

#include <allegro5\allegro.h>
#include <map>
using namespace std;

/// Funciones auxiliares de allegro con el teclado

void getKeyInit();
char getKey(int code);

#endif