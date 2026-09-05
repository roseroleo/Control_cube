

#ifndef CONTROLCUBE_H
#define CONTROLCUBE_H

#include <Arduino.h>
#include "Glyph.h"

class ControlCube
{
public:

    // Constructor
    ControlCube(byte dataPin,
                byte clockPin,
                byte latchPin);
    
    // Dimensiones del cubo
    static constexpr byte WIDTH  = 8;
    static constexpr byte HEIGHT = 8;
    static constexpr byte DEPTH  = 8;

    // Inicialización del hardware
    void begin();

    // Borra completamente el contenido del cubo
    void clearCube();

    // Validar coordenadas
    bool validCoordinates(byte x, byte y, byte z);
    
    // Dibuja un glifo en la capa frontal
    void drawGlyph(const Glyph& glyph);

    // Dibuja un glifo en cualquier capa
    void drawGlyph(const Glyph& glyph, byte layer);

    // Refresca una capa del cubo
    void updateDisplay();

    // Enciende un led en (z, y, x)
    void setVoxel(byte x, byte y, byte z);

    // Dibuja un glifo en los ejes XZ
    void drawGlyphXZ(const Glyph& glyph, byte y_pos);

    
private:

    // Capa donde se dibujan inicialmente los glifos
    static constexpr byte FRONT_LAYER = 0;

    // Pines de conexión
    byte dataPin;
    byte clockPin;
    byte latchPin;

    // Capa actualmente mostrada
    byte currentLayer = 0;

    // Mascara de una fila x
    byte bitMask(byte x);

    // Memoria del cubo
    byte cube[DEPTH][HEIGHT];

    // Driver del 74HC595
    inline void clockPulse();
    inline void latchPulse();
    inline void shiftBit(bool bitValue);
    void shiftByte(byte value);

    // Envío de una capa al hardware
    void sendLayer(byte layer);
};

#endif