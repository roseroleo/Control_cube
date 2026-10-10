#include "CubeAnimations.h"
//#include "ControlCube.h"

CubeAnimations::CubeAnimations(ControlCube& cubeInstance) : cube(cubeInstance)
{

}

void CubeAnimations::AnimateGlyphBackToFront(Glyph& glyph)
{
    static byte y = 7;

    // Control de tiempo no bloqueante con millis()
    static unsigned long lastStep = 0;

    // Si aún no ha pasado el tiempo, salimos para no interrumpir el refresco
    if (millis() - lastStep < 80)
    {
        return;
    }
    lastStep = millis();

    // Borramos el fotograma anterior
    cube.clearCube();
    
    if (y >= 0)
    {
        // Dibujamos el glyph en la capa Y
        cube.drawGlyph(LETTERS[5], y);
        cube.
        y--;
    }
    else
    {
        y = 7;
    }
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

    // Borramos el fotograma anterior
    cube.clearCube();
    
    // Dibujamos la columna vertical en la posición actual
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

//--------------------------------------------
// Animación cubo decreciendo
//--------------------------------------------
void CubeAnimations::AnimateCubeReduce(unsigned long speed)
{
    // Coordenadas iniciales
    byte x = 7;
    byte y = 7;
    byte z = 7;
    static int w = 7; // Define el ancho del cubo

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

    // 2. Dibujamos las aristas del cubo
    CubeGraphics gfx(cube);

    if (w > 0)
    {
        x = w;
        y = w;
        z = w;
        
        for (byte i = 0; i < w; i++)
        {
        cube.setVoxel(i, 0, 0);
        cube.setVoxel(i, y, 0);
        cube.setVoxel(i, 0, z);
        cube.setVoxel(i, y, z);

        cube.setVoxel(0, i, 0);
        cube.setVoxel(0, i, z);
        cube.setVoxel(x, i, 0);
        cube.setVoxel(x, i, z);

        cube.setVoxel(0, 0, i);
        cube.setVoxel(x, 0, i);
        cube.setVoxel(0, y, i);
        cube.setVoxel(x, y, i);
        }
        w--;
    }

    else 
    { 
        w = 7;
    }
}

//--------------------------------------------
// Animación cubo creciendo
//--------------------------------------------
void CubeAnimations::AnimateCubeGrow(unsigned long speed)
{
    // Coordenadas iniciales
    byte x = 0;
    byte y = 0;
    byte z = 0;
    static int w = 0; // Define el ancho del cubo

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

    // 2. Dibujamos las aristas del cubo
    CubeGraphics gfx(cube);

    if (w < 8)
    {
        x = w;
        y = w;
        z = w;
        
        for (byte i = 0; i < w; i++)
        {
        cube.setVoxel(i, 0, 0);
        cube.setVoxel(i, y, 0);
        cube.setVoxel(i, 0, z);
        cube.setVoxel(i, y, z);

        cube.setVoxel(0, i, 0);
        cube.setVoxel(0, i, z);
        cube.setVoxel(x, i, 0);
        cube.setVoxel(x, i, z);

        cube.setVoxel(0, 0, i);
        cube.setVoxel(x, 0, i);
        cube.setVoxel(0, y, i);
        cube.setVoxel(x, y, i);
        }
        w++;
    }

    else 
    { 
        w = 0;
    }

    /*
    // perimetro del cubo con lineas
        gfx.drawLineX(y, z); 
        gfx.drawLineX(y+i, z); 
        gfx.drawLineX(y, z+i);
        gfx.drawLineX(y+i, z+i); 

        gfx.drawLineY(x, z); 
        gfx.drawLineY(x+i, z); 
        gfx.drawLineY(x, z+i);
        gfx.drawLineY(x+i, z+i); 
        
        gfx.drawLineZ(x, y); 
        gfx.drawLineZ(x+i, y);
        gfx.drawLineZ(x, y+i); 
        gfx.drawLineZ(x+i, y+i);
    */
}

//--------------------------------------------
// Animación cubo decreciendo al centro
//--------------------------------------------
void CubeAnimations::AnimateCubeReduce2(unsigned long speed)
{
    // Coordenadas iniciales
    byte x;
    byte y;
    byte z;
    static int w = 7; // Define el ancho del cubo

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

    // 2. Dibujamos las aristas del cubo
    //CubeGraphics gfx(cube);

    if (w > 0)
    {
        x = w;
        y = w;
        z = w;
        
        for (byte i = 7-w; i < w; i++)
        {
        // Aristas en X
        cube.setVoxel(i, 7-w, 7-w);
        cube.setVoxel(i, y, 7-w);
        cube.setVoxel(i, 7-w, z);
        cube.setVoxel(i, y, z);
        // Aristas en Y
        cube.setVoxel(7-w, i, 7-w);
        cube.setVoxel(7-w, i, z);
        cube.setVoxel(x, i, 7-w);
        cube.setVoxel(x, i, z);
        // Aristas en Z
        cube.setVoxel(7-w, 7-w, i);
        cube.setVoxel(x, 7-w, i);
        cube.setVoxel(7-w, y, i);
        cube.setVoxel(x, y, i);
        }
        w--;
    }

    else 
    { 
        w = 7;
    }
}

