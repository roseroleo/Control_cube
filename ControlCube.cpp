

#include "ControlCube.h"

//--------------------------------------------
// Constructor
//--------------------------------------------

ControlCube::ControlCube(byte dataPin,
                         byte clockPin,
                         byte latchPin)
{
    this->dataPin  = dataPin;
    this->clockPin = clockPin;
    this->latchPin = latchPin;
}

//--------------------------------------------
// Inicialización
//--------------------------------------------

void ControlCube::begin()
{
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);

    digitalWrite(dataPin, LOW);
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, LOW);

    clearCube();
}

//--------------------------------------------
// Borra la memoria del cubo
//--------------------------------------------

void ControlCube::clearCube()
{
    for (byte z = 0; z < DEPTH; z++)
    {
        for (byte y = 0; y < HEIGHT; y++)
        {
            cube[z][y] = 0x00;
        }
    }
}

//--------------------------------------------
// Pulso de reloj
//--------------------------------------------

inline void ControlCube::clockPulse()
{
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
}

//--------------------------------------------
// Pulso de latch
//--------------------------------------------

inline void ControlCube::latchPulse()
{
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
}

//--------------------------------------------
// Envía un bit
//--------------------------------------------

inline void ControlCube::shiftBit(bool bitValue)
{
    digitalWrite(dataPin, bitValue);

    clockPulse();
}

//--------------------------------------------
// Envía un byte
//--------------------------------------------

void ControlCube::shiftByte(byte value)
{
    for (int bit = 7; bit >= 0; bit--)
    {
        shiftBit(value & (1 << bit));
    }
}


// Validar coordenadas
bool ControlCube::validCoordinates(byte x, byte y, byte z)
{
    if (x > 7 || y > 7 || z > 7)
    {
        return false;
    }

    return true;
}



//================

//--------------------------------------------
// Dibuja un glifo
//--------------------------------------------

void ControlCube::drawGlyph(const Glyph& glyph)
{
    clearCube();

    for (byte y = 0; y < HEIGHT; y++)
    {
        cube[FRONT_LAYER][y] = glyph.rows[y];
    }
}

//--------------------------------------------
// Dibuja un glifo en cualquier capa
//--------------------------------------------

void ControlCube::drawGlyph(const Glyph& glyph, byte layer)
{
    if (layer >= DEPTH)
        return;

    clearCube();

    for (byte y = 0; y < HEIGHT; y++)
    {
        cube[layer][y] = glyph.rows[HEIGHT - 1 - y];
    }
}

//--------------------------------------------
// Envía una capa al hardware
//--------------------------------------------

void ControlCube::sendLayer(byte layer)
{
    // Primer byte → Registro 9 (capas)
    shiftByte(1 << layer);

    // Después los registros 8...1 (filas)
    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        shiftByte(cube[layer][y]);
    }

    // Actualizar todas las salidas
    latchPulse();
}

//--------------------------------------------
// Refresca el cubo
//--------------------------------------------

void ControlCube::updateDisplay()
{
    sendLayer(currentLayer);

    currentLayer++;

    if (currentLayer >= DEPTH)
    {
        currentLayer = 0;
    }
}

//--------------------------------------------
// Mascara de una fila x
//--------------------------------------------

byte ControlCube::bitMask(byte x)
{
    return (1 << (7 - x));
}




