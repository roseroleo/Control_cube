#include "CubeAnimations.h"
#include "TestFont.h"
//#include "ControlCube.h"

CubeAnimations::CubeAnimations(ControlCube& cubeInstance) : cube(cubeInstance)
{

}

// Control de tiempo no bloqueante con millis()
bool CubeAnimations::isTimeUp(unsigned long speed)
{
    if (millis() - lastStep < speed)
    {
        return false;
    }
    lastStep = millis();
    return true;
}

void CubeAnimations::AnimateGlyphBackToFront(Glyph& glyph, unsigned long speed)
{
    static byte y = 7;

    if (!isTimeUp(speed))
    {
        return;
    }

    // Borramos el fotograma anterior
    cube.clearCube();
    
    // Dibujamos el glyph en la capa Y actual
    cube.drawGlyphXZ(glyph, y);
    if (y > 0)
    {
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

    if (!isTimeUp(speed))
    {
        return;
    }

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

    if (!isTimeUp(speed))
    {
        return;
    }

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

    if (!isTimeUp(speed))
    {
        return;
    }

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

    if (!isTimeUp(speed))
    {
        return;
    }

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


//--------------------------------------------
// Animación lluvia
//--------------------------------------------



// --- Función principal de lluvia ---
void CubeAnimations::AnimateRain()
{

    // --- Estructura de cada gota ---
struct Drop {
  byte x;
  byte y;
  byte z;
  byte speed;              // velocidad de caída (ms entre pasos)
  unsigned long lastMove;  // control de tiempo individual
};


  const byte dd = 35;  
  static Drop drops[dd]; // arreglo de ## gotas
  static bool initialized = false;

  // Inicializar gotas solo una vez
  if (!initialized) {
    for (int i = 0; i < dd; i++) {
      drops[i].x = random(8);
      drops[i].y = random(8);
      drops[i].z = 7;
      drops[i].speed = random(50, 150);   // Cada gota con velocidad distinta
      drops[i].lastMove = millis();
    }
    initialized = true;
  }

  // Limpiar cubo antes de dibujar
  cube.clearCube();

  // Actualizar cada gota
  for (int i = 0; i < dd; i++) {
    cube.setVoxel(drops[i].x, drops[i].y, drops[i].z);

    if (millis() - drops[i].lastMove >= drops[i].speed) {
      drops[i].lastMove = millis();

      if (drops[i].z > 0) {
        drops[i].z--;
      } else {
        // reinicia arriba con nueva posición y velocidad
        drops[i].x = random(8);
        drops[i].y = random(8);
        drops[i].z = 7;
        drops[i].speed = random(50, 150);
      }
    }
  }

  //cube.updateDisplay();
}