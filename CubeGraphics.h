#ifndef CUBE_GRAPHICS_H
#define CUBE_GRAPHICS_H

#include "ControlCube.h"

class CubeGraphics
  {
    private:
    ControlCube& cube; //Referencia al hardware del cubo

    public:
    // Constructor que recibe el cubo físico
    explicit CubeGraphics(ControlCube& cubeInstance);

    // DIBUJO DE LÍNEAS ESTRUCTURALES (EJES)
    void drawLineX(byte y, byte z);
    void drawLineY(byte x, byte z);
    void drawLineZ(byte x, byte y);

    // DIBUJO DE PLANOS COMPLETOS
    void drawPlaneX(byte x);
    void drawPlaneY(byte y);
    void drawPlaneZ(byte z);
  };

#endif