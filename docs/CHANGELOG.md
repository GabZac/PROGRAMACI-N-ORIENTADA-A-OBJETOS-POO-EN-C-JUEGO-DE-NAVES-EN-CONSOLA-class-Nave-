# 📑 Changelog - Bitácora de Versionado SemVer (Actividad 8)

Todos los cambios estructurales notables realizados en este juego de simulación espacial individual quedan registrados en este documento bajo las pautas de versionado semántico.

**Proyecto:** Motor de Juego de Naves en Consola Basado en Clases (Actividad 8)  
**Institución:** E.E.S.T. N° 1 "Eduardo Ader" — Vicente López  
**Asignatura:** Laboratorio de Programación (LPR) — 5° Año  
**Estudiante:** Gabriel Zacarías (Entrega Individual)  

---

## - 2026-10-16
### Añadido
- **Módulo de Puntuación (Score):** Inyección de la variable dinámica `int score` alojada en la memoria RAM para realizar la sumatoria acumulativa de créditos de combate.
- **HUD Integrado:** Modificación de la subrutina del bucle de renderizado para proyectar en tiempo real la puntuación actual en las coordenadas `gotoxy(15, 2)`.
- **Aritmética de Colisiones con Estructuras vector:** Adición del algoritmo de asignación `score += 10` que se ejecuta exactamente al momento de validar la intersección binaria entre un objeto de la clase `Bala` y un objeto de la clase `Asteroide`.
- **Pantalla de Cierre:** Integración de un resumen de rendimiento técnico en la ventana final indicando el puntaje neto acumulado por el piloto antes del apagado del hilo del juego.

---

## - 2026-10-15
### Aprobado
- **Baseline Aprobado:** Configuración del paradigma POO con protección estricta de datos (*Encapsulamiento*).

### Añadido
- **Clase Nave:** Definición de los atributos privados `x`, `y` y `vidas`, y los métodos públicos de manipulación de la interfaz física de hardware (`pintar`, `borrar`, `mover`).
- **Clases Asteroide y Bala:** Modelado de amenazas dinámicas y proyectiles mediante instanciaciones secuenciales controladas por asignación en memoria dinámica (`new`).
- **Sistema Anti-Copia:** Bloque de entrada mandatorio por consola (`getline`) encargado de indexar el nombre completo del estudiante en la cabecera visual del videojuego.

### Solucionado
- **Bloqueo por Permisos:** Parametrización del comando de salida unificado (`-o src/juegodenaves.exe`) para mitigar el error de compilación por procesos colgados en memoria (*Permission denied*).
