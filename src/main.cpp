/* 
   ====================================================================
   Materia: Laboratorio de Programación (LPR) — 5° Año
   Institución: E.E.S.T. N.º 1 "Eduardo Ader" - Vicente López
   Curso: 5° Año 5° 3° (Grupo Individual)
   Estudiante: Gabriel Zacarias
   Archivo: src/main.cpp
   Actividad 8: Introducción a POO - Motor de Juego de Naves
   ====================================================================
*/

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <ctime>
#include <cctype> 
#include <string>

using namespace std;

// Funciones de control de la consola de Windows
void gotoxy(int x, int y) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x; dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void ocultarCursor() {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

// ====================================================================
// CLASE NAVE (El Jugador - Abstracción y Encapsulamiento)
// ====================================================================
class Nave {
private:
    int x, y;
    int vidas;

public:
    Nave(int _x, int _y, int _vidas) {
        x = _x; y = _y; vidas = _vidas;
    }
    int getX() { return x; }
    int getY() { return y; }
    int getVidas() { return vidas; }
    void reducirVida() { vidas--; }

    void pintar() {
        gotoxy(x, y);     cout << "  ^  ";
        gotoxy(x, y + 1); cout << " (0) ";
        gotoxy(x, y + 2); cout << "vvvvv";
    }

    void borrar() {
        gotoxy(x, y);     cout << "     ";
        gotoxy(x, y + 1); cout << "     ";
        gotoxy(x, y + 2); cout << "     ";
    }

    void mover(char tecla) {
        borrar();
        if (tecla == 'a' && x > 2) x--;
        if (tecla == 'd' && x < 70) x++;
        if (tecla == 'w' && y > 3) y--;
        if (tecla == 's' && y < 20) y++;
        pintar();
    }
};

// ====================================================================
// CLASE ASTEROIDE
// ====================================================================
class Asteroide {
private:
    int x, y;

public:
    Asteroide(int _x, int _y) { x = _x; y = _y; }
    int getX() { return x; }
    int getY() { return y; }
    void pintar() { gotoxy(x, y); cout << "O"; }
    void borrar() { gotoxy(x, y); cout << " "; }
    
    void mover() {
        borrar();
        y++;
        if (y > 23) {
            y = 4;
            x = (rand() % 70) + 2;
        }
        pintar();
    }
};

// ====================================================================
// CLASE BALA (Corregida con el método pintar interno)
// ====================================================================
class Bala {
private:
    int x, y;

public:
    Bala(int _x, int _y) { x = _x; y = _y; }
    int getX() { return x; }
    int getY() { return y; }
    
    void pintar() {
        gotoxy(x, y); cout << "*"; 
    }
    
    void borrar() { 
        gotoxy(x, y); cout << " "; 
    }
    
    void mover() {
        borrar();
        y--;
        pintar();
    }
    
    bool fueraDeRange() { return y < 4; }
};

// ====================================================================
// PROGRAMA PRINCIPAL (GAME LOOP)
// ====================================================================
int main() {
    srand(time(NULL));

    // Inicialización del acumulador de puntuación
    int score = 0; 

    // SISTEMA ANTI-COPIA: Entrada mandatoria de credenciales
    string nombrePiloto;
    cout << "=====================================================" << endl;
    cout << " LPR 2026 - INGRESO AL SIMULADOR TÁCTICO DE COMBATE " << endl;
    cout << "=====================================================" << endl;
    cout << "=> Ingrese su Nombre y Apellido (Piloto): ";
    getline(cin, nombrePiloto);

    system("cls");
    ocultarCursor();
    bool gameOver = false;

    // Instanciación de Objetos en la memoria de Windows
    Nave jugador(35, 20, 3);
    vector<Asteroide*> asteroides;
    vector<Bala*> balas;

    // Generación inicial de amenazas físicas
    for (int i = 0; i < 5; i++) {
        asteroides.push_back(new Asteroide((rand() % 70) + 2, (rand() % 5) + 4));
    }

    jugador.pintar();

    // Bucle Principal del Videojuego
    while (!gameOver) {
        // Proyección constante del HUD táctico
        gotoxy(2, 1);  cout << "PILOTO: " << nombrePiloto;
        gotoxy(2, 2);  cout << "VIDAS: " << jugador.getVidas() << "   ";
        gotoxy(15, 2); cout << "SCORE: " << score << "   ";

        // Captura síncrona de las pulsaciones del teclado del usuario
        if (_kbhit()) {
            char tecla = tolower(_getch());
            if (tecla == ' ') { 
                balas.push_back(new Bala(jugador.getX() + 2, jugador.getY() - 1));
            } else {
                jugador.mover(tecla);
            }
        }

        // Control y descarte dinámico de proyectiles fuera de rango
        for (size_t i = 0; i < balas.size(); i++) {
            balas[i]->mover();
            if (balas[i]->fueraDeRange()) {
                balas[i]->borrar();
                delete balas[i];
                balas.erase(balas.begin() + i);
            }
        }

        // Gestión física y colisiones de amenazas
        for (size_t i = 0; i < asteroides.size(); i++) {
            asteroides[i]->mover();

            // Intersección: Asteroide -> Estructura de la Nave
            if ((asteroides[i]->getX() >= jugador.getX() && asteroides[i]->getX() <= jugador.getX() + 4) &&
                (asteroides[i]->getY() >= jugador.getY() && asteroides[i]->getY() <= jugador.getY() + 2)) {
                
                jugador.borrar();
                jugador.reducirVida();
                asteroides[i]->borrar();
                delete asteroides[i];
                asteroides[i] = new Asteroide((rand() % 70) + 2, 4);
                jugador.pintar();

                if (jugador.getVidas() == 0) gameOver = true;
            }

            // Intersección: Bala -> Asteroide (Suma de créditos del reto Score)
            for (size_t j = 0; j < balas.size(); j++) {
                if (asteroides[i]->getX() == balas[j]->getX() && 
                    (asteroides[i]->getY() == balas[j]->getY() || asteroides[i]->getY() + 1 == balas[j]->getY())) {
                    
                    balas[j]->borrar();
                    delete balas[j];
                    balas.erase(balas.begin() + j);

                    asteroides[i]->borrar();
                    delete asteroides[i];
                    asteroides[i] = new Asteroide((rand() % 70) + 2, 4);
                    
                    score += 10; // Adición de puntaje por impacto de hardware exitoso
                    break;
                }
            }
        }

        Sleep(30); // Sincronización del reloj interno de la RAM
    }

    // Ventana de Cierre de Sesión del Piloto
    system("cls");
    gotoxy(25, 10); cout << "=========================================";
    gotoxy(25, 11); cout << "   SIMULADOR TERMINADO — GAME OVER";
    gotoxy(25, 12); cout << "=========================================";
    gotoxy(25, 14); cout << " PILOTO REGISTRADO: " << nombrePiloto;
    gotoxy(25, 15); cout << " PUNTUACIÓN NETO:   " << score << " PUNTOS";
    gotoxy(25, 17); cout << "=========================================";
    gotoxy(25, 19); system("pause");
    
    return 0;
}

