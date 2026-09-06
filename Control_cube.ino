/* CONTROLCUBE */

#include "ControlCube.h"
#include "TestFont.h"
#include "TestControlCube.h"

constexpr byte DATA_PIN  = 13;
constexpr byte CLOCK_PIN = 14;
constexpr byte LATCH_PIN = 27;

// =================================================
// MENU - PANEL DE PRUEBAS
// =================================================

#define TEST_VOXEL                  1
#define TEST_CLEAR                  2
#define TEST_GET_VOXEL              3
#define TEST_TOGGLE                 4
#define TEST_GLYPH                  5

#define MOVE_GLYPH_UP               6
#define MOVE_GLYPH_BACK_TO_FRONT    7

// Seleccionar aquí la prueba que queremos ejecutar
const byte TEST = MOVE_GLYPH_BACK_TO_FRONT;
bool testInitialized = false;

ControlCube cube(DATA_PIN, CLOCK_PIN, LATCH_PIN);

// --------------------------------------------------
// SETUP
// --------------------------------------------------

void setup()
{ 
    cube.begin();
    cube.clearCube();
    Serial.begin(115200);
}


// --------------------------------------------------
// LOOP
// --------------------------------------------------

void loop()
{
    cube.updateDisplay();

    if(!testInitialized)
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
            
            testInitialized = true;
        }
    }
}

