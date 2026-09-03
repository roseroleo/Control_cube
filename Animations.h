#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "ControlCube.h"
#include "TestFont.h"

class Animations
{
private:

    ControlCube* cube;

    byte glyphLayer = 0;

    unsigned long lastMove = 0;

    const unsigned long moveTime = 400;

public:

    Animations(ControlCube& cube);

    void moveGlyphUp(const Glyph& glyph);

};

#endif