#include "TestControlCube.h"

// =====================================================
// PRUEBA ACTUAL EN DESARROLLO: Animación de perímetro
// =====================================================

// --- Estructura de cada gota ---
struct Drop {
  byte x;
  byte y;
  byte z;
  byte speed;              // velocidad de caída (ms entre pasos)
  unsigned long lastMove;  // control de tiempo individual
};

// --- Función principal de lluvia ---
void testCurrentFunction(ControlCube& cube)
{
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


// =====================================================
// BORRADOR PARA PRUEBAS Y EXPERIMENTOS PROPIOS
// =====================================================
void testUserDraft(ControlCube& cube)
{


    // Control de tiempo no bloqueante con millis()
    static unsigned long lastStep = 0;
    constexpr unsigned long STEP_TIME = 100; // velocidad de caida de gotas

    // Si aún no ha pasado el tiempo, salimos para no interrumpir el refresco
    if (millis() - lastStep < STEP_TIME)
    {
        return;
    }
    lastStep = millis();
   
    cube.clearCube();

    // GOTAS DE LLUVIA
    randomSeed(analogRead(A0)); // Iniciamos una semilla para random
    byte drops = 32; // Número de gotas
    static byte z = 0;

    if (z < 8)
    {
        for (byte i = 0;i < drops; i++)
        {
            byte x = random(7);
            byte y = random(7);
            cube.setVoxel(x, y, 7-z); 
        }
        z++;
        //cube.updateDisplay();    
    }
    //cube.updateDisplay();
}
