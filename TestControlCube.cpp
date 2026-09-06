#include "TestControlCube.h"
#include "ControlCube.h"
#include "TestFont.h"

void testSetVoxel(ControlCube& cube)
{
    cube.clearCube();
    cube.setVoxel(0, 0, 0);
}

void testClearVoxel(ControlCube& cube)
{
    cube.clearCube();
    cube.setVoxel(0, 0, 0);
}

void testGetVoxel(ControlCube& cube)
{
    cube.clearCube();

    cube.setVoxel(0, 0, 0);
    cube.setVoxel(3, 3, 3);
    cube.setVoxel(7, 7, 7);

    Serial.println(cube.getVoxel(0, 0, 0));
    Serial.println(cube.getVoxel(3, 3, 3));
    Serial.println(cube.getVoxel(7, 7, 7));

    Serial.println(cube.getVoxel(1, 0, 0));
    Serial.println(cube.getVoxel(4, 3, 3));
    Serial.println(cube.getVoxel(6, 7, 7));

    cube.updateDisplay();
}

void testToggleVoxel(ControlCube& cube)
{
    cube.clearCube();

    cube.setVoxel(3, 3, 3);

    cube.toggleVoxel(3, 3, 3);
    cube.toggleVoxel(3, 3, 3);

    cube.updateDisplay();
}

//=====================================================
// MOSTRAR GLIFO SUBIENTO POR CAPAS
//=====================================================

byte currentGlyph = 0;
byte currentLayer = 0;

unsigned long lastChange = 0;
constexpr unsigned long LAYER_TIME = 100;


void moveGlyphUp(ControlCube& cube)
{
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
}


//=====================================================
// MOSTRAR GLIFO DE ATRAS A ADELANTE
//=====================================================

byte currentY = 7; // 7 = atrás, 0 = adelante

const uint16_t STEP_TIME = 100; // velocidad de atrás hacia adelante. 80 rápido, 250 lento

void moveGlyphBackToFront(ControlCube& cube)
{
    // Tiempo de permanencia en cada posición Y
    if (millis() - lastChange >= STEP_TIME)
    {
        lastChange = millis();

        // Dibuja el glifo PARADO en esa Y
        cube.drawGlyphXZ(LETTERS[currentGlyph], currentY);

        // Siguiente posición en profundidad
        currentY--;

        // Cuando terminamos de recorrer de atrás hacia adelante
        if (currentY < 1)
        {
            cube.drawGlyphXZ(LETTERS[currentGlyph], currentY);
            currentY = 7; // vuelve atrás
            currentGlyph++;

            if (currentGlyph >= TOTAL_LETTERS)
            {
                currentGlyph = 0;
            }
        }

        
    }
}
