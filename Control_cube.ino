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
        //cube.drawGlyph(LETTERS[currentGlyph], currentLayer);
        
        for (byte x = 0; x < 8; x++)
        {
            
        }

    }
}