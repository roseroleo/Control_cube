#ifndef TEST_CONTROL_CUBE_H
#define TEST_CONTROL_CUBE_H

#include <Arduino.h>
#include "ControlCube.h"

void testSetVoxel(ControlCube& cube);
void testClear(ControlCube& cube);
void testGetVoxel(ControlCube& cube);
void testToggle(ControlCube& cube);
void testGlyph(ControlCube& cube);

void moveGlyphUp(ControlCube& cube);
void moveGlyphBackToFront(ControlCube& cube);

#endif

