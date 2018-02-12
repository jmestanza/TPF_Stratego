#pragma once

#include <allegro5\allegro.h>

ALLEGRO_BITMAP* copyBitmap(ALLEGRO_BITMAP *input);
void blitBitmap(ALLEGRO_BITMAP *dst,ALLEGRO_BITMAP* who,int x,int y);