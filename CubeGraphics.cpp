# include "CubeGraphics.h"

CubeGraphics::CubeGraphics(ControlCube& cubeInstance) : cube(cubeInstance)
  {
    // El cuerpo del constructor queda vacío porque la vinculación ya se realizó arriba
  }
//--------------------------------------------
// Dibuja una línea a lo largo de todo el eje X
//--------------------------------------------
void CubeGraphics::drawLineX(byte y, byte z)
{
    if (y > 7 || z > 7)  //validación rápida
    {
        return;
    }
    for (byte x = 0; x < 8; x++)
    {
        cube.setVoxel(x, y, z);
    }
}

//--------------------------------------------
// Dibuja una línea a lo largo de todo el eje Y
//--------------------------------------------
void CubeGraphics::drawLineY(byte x, byte z)
{
    if (x > 7 || z > 7)  //validación rápida
    {
        return;
    }
    for (byte y = 0; y < 8; y++)
    {
        cube.setVoxel(x, y, z);
    }
}

//--------------------------------------------
// Dibuja una línea a lo largo de todo el eje Z
//--------------------------------------------
void CubeGraphics::drawLineZ(byte x, byte y)
{
    if (x > 7 || y > 7)  //validación rápida
    {
        return;
    }
    for (byte z = 0; z < 8; z++)
    {
        cube.setVoxel(x, y, z);
    }
}