#pragma once

#include <framework\view\widgets\text_button.h>

/// Botones con diversas imagenes, que forman una buena combinacion de diseño
/// Se fueron agregando al ver que combinaban bien

imgGroup g_blue();
imgGroup g_green();
imgGroup g_red();
imgGroup g_connectButton();
imgGroup g_connectButtonLong();
imgGroup g_greenSmall();
imgGroup g_greenMedium();
imgGroup g_redMedium();

void generateButtons(Viewer *view);
void getLoadingAImgs(vector <string> &ans);