#pragma once

#include <allegro5\allegro.h>
#include <framework\view\allegro_manager\allegro_manager.h>

/// Funciones auxiliares de allegro

ALLEGRO_BITMAP* copyBitmap(ALLEGRO_BITMAP *input);
void blitBitmap(ALLEGRO_BITMAP *dst,ALLEGRO_BITMAP* who,int x,int y);
void blitTextCentered(Viewer* view,ALLEGRO_BITMAP *dst,string text,string font,string color);
void blitText(Viewer* view,ALLEGRO_BITMAP *dst,string text,string font,string color,int x,int y);