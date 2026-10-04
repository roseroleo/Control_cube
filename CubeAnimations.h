#ifndef CUBE_ANIMATIONS_H
#define CUBE_ANIMATIONS_H

#include "ControlCube.h"
#include "CubeGraphics.h"

class CubeAnimations
{
    private:
        ControlCube& cube;

    public:
        // Constructor que recibe el cubo físico
        explicit CubeAnimations(ControlCube& cubeInstance);

        // Animación linea vertical recorre el perimetro
        void AnimatePerimeterLine(unsigned long speed = 80);

};

#endif