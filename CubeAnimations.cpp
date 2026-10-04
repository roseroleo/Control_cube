#include "CubeAnimations.h"

CubeAnimations::CubeAnimations(ControlCube& cubeInstance) : cube(cubeInstance)
{

}

//--------------------------------------------
// Animación linea vertical recorre el perimetro
//--------------------------------------------
void CubeAnimations::AnimatePerimeterLine(unsigned long speed)
{
    // Coordenadas actuales de la columna
    static byte x = 0;
    static byte y = 0;

    // Control de tiempo no bloqueante con millis()
    static unsigned long lastStep = 0;

    // Si aún no ha pasado el tiempo, salimos para no interrumpir el refresco
    if (millis() - lastStep < speed)
    {
        return;
    }
    lastStep = millis();

    // 1. Borramos el fotograma anterior
    cube.clearCube();

    // 2. Dibujamos la columna vertical en la posición actual
    CubeGraphics gfx(cube);
    gfx.drawLineZ(x, y);

    // 3. Calculamos la siguiente posición del perímetro en sentido horario
    if (y == 0 && x < 7)
    {
        x++; // Borde frontal: de izquierda a derecha
    }
    else if (x == 7 && y < 7)
    {
        y++; // Borde derecho: del frente hacia el fondo
    }
    else if (y == 7 && x > 0)
    {
        x--; // Borde posterior: de derecha a izquierda
    }
    else if (x == 0 && y > 0)
    {
        y--; // Borde izquierdo: del fondo hacia el frente
    }

}

