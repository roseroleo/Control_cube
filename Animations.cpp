#include "Animations.h"

//--------------------------------------------
// Constructor
//--------------------------------------------

Animations::Animations(ControlCube& cube)
{
    this->cube = &cube;
}

// Mueve el glifo hacia arriba
void Animations::moveGlyphUp(const Glyph& glyph)
{
    if (millis() - lastMove >= moveTime)
    {
        glyphLayer++;

        if (glyphLayer >= ControlCube::DEPTH)
            glyphLayer = 0;

        cube->drawGlyph(glyph, glyphLayer);

        lastMove = millis();
    }
}