#ifndef GLYPH_H
#define GLYPH_H

#include <Arduino.h>

/*
    ===========================================================
                        ControlCube Project
                           Glyph.h
    ===========================================================

    Un Glyph representa una imagen de 8 × 8 píxeles.

    Cada elemento del arreglo 'rows' representa una fila (Y),
    donde cada bit del byte representa un LED sobre el eje X.

    Bit 7 ---------------------------> Bit 0
       X=0                             X=7

    rows[0]  → fila superior
    rows[7]  → fila inferior

    El Glyph es independiente del cubo y puede utilizarse para
    letras, números, iconos o cualquier imagen de 8 × 8.
*/


struct Glyph
{
    static constexpr byte WIDTH  = 8;
    static constexpr byte HEIGHT = 8;

    byte rows[HEIGHT];
};

#endif