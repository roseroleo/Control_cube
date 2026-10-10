/* 
 * ====================================================================
 *       PROYECTO CUBO LED 8x8x8 (ESP32) — Control_cube.ino
 * ====================================================================
 * Consulta el archivo README.md para ver el registro completo de 
 * funciones implementadas, arquitectura de hardware y avance.
 */++

#include "Communications.h" //Controla conexion WiFi
#include "ControlCube.h"
#include "CubeAnimations.h"
#include "TestFont.h"
#include "TestControlCube.h"

constexpr byte DATA_PIN  = 13;
constexpr byte CLOCK_PIN = 14;
constexpr byte LATCH_PIN = 27;

Communications comm;

// =================================================
// MODO DE PRUEBA
// 1 = Animación aprobada (CubeAnimations)
// 2 = Borrador propio (TestControlCube)
// =================================================
const byte MODO_PRUEBA = 1;

ControlCube cube(DATA_PIN, CLOCK_PIN, LATCH_PIN);
CubeAnimations anim(cube);

// --------------------------------------------------
// SETUP
// --------------------------------------------------

void setup()
{ 
    
    // Configuracion de OTA (WiFi)
    Serial.begin(115200);
    comm.begin();
    
    // Inicializar cubo
    cube.begin();
    cube.clearCube();
    Serial.begin(115200);
}

// --------------------------------------------------
// NUEVO LOOP (Ejecución continua para animaciones)
// --------------------------------------------------
void loop()
{
    // Mantener conexion WiFi
    comm.handle();

    // Refresco continuo del hardware (multiplexado a alta frecuencia)
    cube.updateDisplay();

    // Ejecución continua de la prueba o animación activa
    if (MODO_PRUEBA == 1)
    {
        testCurrentFunction(cube); // Llamada directa a CubeAnimations
    }
    // Ejecución de funcion en construcción
    else if (MODO_PRUEBA == 2)
    {
        testUserDraft(cube); 
    }
    // Prueba directa de funcion construida y aprobada
    else if (MODO_PRUEBA == 3)
    {
        //anim.AnimateCubeReduce2();
        
        //cube.drawGlyphXZ(LETTERS[5], 3);

        cube.AnimateGlyphBackToFront(LETTERS[4]);
    }
}

