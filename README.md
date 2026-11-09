# Control_cube — Cubo LED 8×8×8 con ESP32

Proyecto de construcción, multiplexado y biblioteca modular para un Cubo LED azul de 8×8×8 (512 LEDs) controlado por ESP32 mediante 9 registros de desplazamiento 74HC595 en cascada.

---

## 1. Arquitectura de Hardware

- **Microcontrolador:** ESP32
- **Líneas de control (74HC595):**
  - `DATA_PIN` = GPIO 13
  - `CLOCK_PIN` = GPIO 14
  - `LATCH_PIN` = GPIO 27
- **Registros 74HC595 en cascada:**
  - Registros #1 a #8: 64 columnas (ánodos con resistencias ~330 Ω).
  - Registro #9: 8 capas/pisos (cátodos con transistores BD137).
- **Convención de Coordenadas (0 a 7):**
  - **X:** Izquierda (0) → Derecha (7)
  - **Y:** Frente (0) → Fondo (7)
  - **Z:** Abajo (0) → Arriba (7)
  - `(0, 0, 0)` = Esquina inferior frontal izquierda.
- **Mapeo de Bits:** `bitMask(x) = (1 << (7 - x))`

---

## 2. Registro de Funciones y Avance del Proyecto

### Capa 1: Hardware y Manipulación de Voxeles (`ControlCube`)
- [x] `validCoordinates(x, y, z)` — Verificación de límites espaciales (0..7).
- [x] `bitMask(x)` — Conversión de posición $X$ a máscara de bit física.
- [x] `clearCube()` — Borrado completo de la memoria del cubo (apaga todos los LEDs).
- [x] `setVoxel(x, y, z)` — Encender un voxel/LED específico.
- [x] `clearVoxel(x, y, z)` — Apagar un voxel/LED específico sin alterar los demás.
- [x] `toggleVoxel(x, y, z)` — Invertir el estado de un voxel con operación XOR.
- [x] `getVoxel(x, y, z)` — Consultar el estado de un voxel (`true` / `false`).
- [x] `drawGlyph(glyph, layer)` — Dibujar un glifo 8×8 en cualquier capa horizontal $Z$.
- [x] `drawGlyphXZ(glyph, y_pos)` — Dibujar un glifo vertical en el plano $XZ$.
- [x] `updateDisplay()` — Rutina de refresco de multiplexado continuo.

---

### Capa 2: Motor Gráfico y Geometría (`CubeGraphics`)

#### Nivel 1: Líneas Estructurales (1D)
- [x] `drawLineX(y, z)` — Línea horizontal a lo largo de todo el eje $X$ (izq → der).
- [x] `drawLineY(x, z)` — Línea en profundidad a lo largo de todo el eje $Y$ (frente → fondo).
- [ ] `drawLineZ(x, y)` — Línea vertical a lo largo de todo el eje $Z$ (abajo → arriba) *(En prueba)*.
- [ ] Líneas diagonales 2D y 3D.

#### Nivel 2: Planos y Caras (2D) *(Pendiente)*
- [ ] `drawPlaneX(x)` — Plano vertical completo perpendicular a $X$.
- [ ] `drawPlaneY(y)` — Plano vertical completo perpendicular a $Y$.
- [ ] `drawPlaneZ(z)` — Plano horizontal completo perpendicular a $Z$.
- [ ] Contornos y rectángulos.

#### Nivel 3: Figuras Geométricas (3D) *(Pendiente)*
- [ ] Cajas / Cubos huecos (Wireframe).
- [ ] Cajas / Cubos sólidos.

### Capa 3: Motor de Animaciones (`CubeAnimations`)
- [x] `AnimatePerimeterLine(speed = 80)` — Columna vertical recorriendo el perímetro exterior en sentido horario.
- [ ] Efectos de escáner / rebote *(Pendiente)*.
- [ ] Lluvia / Ascenso *(Pendiente)*.

---

## 3. Entorno de Pruebas (`TestControlCube`)
- `testCurrentFunction(cube)` — Laboratorio activo para la función en desarrollo actual.
- `testUserDraft(cube)` — Espacio reservado para experimentos propios del usuario.
- Modo seleccionable desde `Control_cube.ino` mediante `MODO_PRUEBA`.
