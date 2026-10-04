/* 
 * ====================================================================
 *       PROYECTO CUBO LED 8x8x8 (ESP32) — Control_cube.ino
 * ====================================================================
 * Consulta el archivo README.md para ver el registro completo de 
 * funciones implementadas, arquitectura de hardware y avance.
 */
//#include <WiFi.h>
//#include <ArduinoOTA.h>
#include "ControlCube.h"
#include "CubeAnimations.h"
#include "TestFont.h"
#include "TestControlCube.h"

constexpr byte DATA_PIN  = 13;
constexpr byte CLOCK_PIN = 14;
constexpr byte LATCH_PIN = 27;

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
    /*
    // Configuracion de OTA (Bluetooth)
    Serial.begin(115200);
    WiFi.begin("ESP32_WROOM", "LEROs20fe");
    //ArduinoOTA.setHostname("ESP32_WROOM");
    ArduinoOTA.begin();
    */
    cube.begin();
    cube.clearCube();
    Serial.begin(115200);
}


// --------------------------------------------------
// LOOP
// LOOP ANTERIOR (Comentado como referencia histórica)
// --------------------------------------------------
/*
void loop_anterior()
{
    // Refresco del cubo
    cube.updateDisplay();

    // Menu anterior con switch
    if (!testInitialized)
    {
        switch (TEST)
        {
            case TEST_VOXEL:
                testSetVoxel(cube);
                break;
            
            case TEST_CLEAR:
                testClear(cube);
                break;

            case TEST_GET_VOXEL:
                testGetVoxel(cube);
                break;

            case TEST_TOGGLE:
                testToggle(cube);
                break;

            case TEST_GLYPH:
                testGlyph(cube);
                break;
            
            case MOVE_GLYPH_UP:
                moveGlyphUp(cube);
                break;

            case MOVE_GLYPH_BACK_TO_FRONT:
                moveGlyphBackToFront(cube);
                break;            
            
            case TEST_DRAW_LINE_X:
                testDrawLineX(cube);
                break;
        }

        testInitialized = true;
    }
}
*/

// --------------------------------------------------
// NUEVO LOOP (Ejecución continua para animaciones)
// --------------------------------------------------
void loop()
{
    /*
    // Mantener conexion WiFi
    ArduinoOTA.handle();
    */

    // 1. Refresco continuo del hardware (multiplexado a alta frecuencia)
    cube.updateDisplay();

    // 2. Ejecución continua de la prueba o animación activa
    if (MODO_PRUEBA == 1)
    {
        anim.AnimatePerimeterLine(); // Llamada directa a CubeAnimations
    }
    else if (MODO_PRUEBA == 2)
    {
        testUserDraft(cube);
    }
}

