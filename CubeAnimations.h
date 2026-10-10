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
        void AnimatePerimeterLine(unsigned long speed = 50);

        // Animación cubo decreciendo
        void AnimateCubeReduce(unsigned long speed = 100);

        // Animación cubo creciendo
        void AnimateCubeGrow(unsigned long speed = 80);

        // Animación cubo decreciendo al centro
        void AnimateCubeReduce2(unsigned long speed = 150);

        // Animación letras de fondo a frente
        void AnimateGlyphBackToFront(Glyph& glyph);


};

#endif