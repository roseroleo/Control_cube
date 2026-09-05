/* CONTROLCUBE */

#include "ControlCube.h"
#include "TestFont.h"

constexpr byte DATA_PIN  = 13;
constexpr byte CLOCK_PIN = 14;
constexpr byte LATCH_PIN = 27;

ControlCube cube(DATA_PIN, CLOCK_PIN, LATCH_PIN);

byte currentGlyph = 0;
byte currentLayer = 0;

unsigned long lastChange = 0;

constexpr unsigned long LAYER_TIME = 100;


// --------------------------------------------------
// SETUP
// --------------------------------------------------

void setup()
{
    cube.begin();
    cube.clearCube();

    //showGlyph(currentGlyph, currentLayer);

    lastChange = millis();
}


// --------------------------------------------------
// LOOP
// --------------------------------------------------

/* 
=================================
MOSTRAR GLIFO SUBIENTO POR CAPAS
=================================
void loop()
{
    // Refresco continuo del multiplexado
    cube.updateDisplay();

    // Tiempo de permanencia de la capa
    if (millis() - lastChange >= LAYER_TIME)
    {
        lastChange = millis();

        // Siguiente capa
        currentLayer++;

        // Cuando terminamos las 8 capas,
        // pasamos al siguiente glifo
        if (currentLayer >= 8)
        {
            currentLayer = 0;

            currentGlyph++;

            // Cuando terminamos todos los glifos,
            // volvemos a A
            if (currentGlyph >= TOTAL_LETTERS)
            {
                currentGlyph = 0;
            }
        }

        // Mostrar el glifo actual en cada capa
        cube.drawGlyph(LETTERS[currentGlyph], currentLayer);
        
    }
    ===============================
    */

// MOSTRAR GLIFO PARADO

byte currentY = 8; // 7 = atrás, 0 = adelante
//byte currentGlyph = 0;
//unsigned long lastChange = 0;
const uint16_t STEP_TIME = 100; // velocidad de atrás hacia adelante. 80 rápido, 250 lento

void loop()
{
    // Refresco continuo del multiplexado - ESTO SE QUEDA SIEMPRE
    cube.updateDisplay();

    // Tiempo de permanencia en cada posición Y
    if (millis() - lastChange >= STEP_TIME)
    {
        lastChange = millis();

        // Siguiente posición en profundidad
        currentY--;

        // Cuando terminamos de recorrer de atrás hacia adelante
        if (currentY < 1)
        {
            currentY = 7; // vuelve atrás
            currentGlyph++;

            if (currentGlyph >= TOTAL_LETTERS)
            {
                currentGlyph = 0;
            }
        }

        // Dibuja el glifo PARADO en esa Y
        cube.drawGlyphXZ(LETTERS[currentGlyph], currentY);
        
    }
}
