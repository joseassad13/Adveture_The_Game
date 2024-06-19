#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>

using namespace std;
const int FILAS = 20;
const int COLUMNAS = 20;

char laberinto[FILAS][COLUMNAS] = {
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1'},
    {'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '0', '1', '0', '0', '0', '1'},
    {'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
    {'1', '0', '1', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '0', '1'},
    {'1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '0', '1', '0', '0', '0', '1'},
    {'1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
    {'1', '0', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '1', '1', '1', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

struct Personaje
{
    int x;
    int y;
};

Personaje personaje = {1, 1}; // Posición inicial del personaje

bool esMovimientoValido(int nuevaX, int nuevaY)
{
    if (nuevaX < 0 || nuevaX >= FILAS || nuevaY < 0 || nuevaY >= COLUMNAS)
    {
        return false; // Fuera de los límites del laberinto
    }
    if (laberinto[nuevaX][nuevaY] == '1')
    {
        return false; // Es una pared
    }
    return true;
}

void moverPersonaje(char direccion)
{
    int nuevaX = personaje.x;
    int nuevaY = personaje.y;

    switch (direccion)
    {
    case 'w':
        nuevaX--;
        break; // Mover arriba
    case 's':
        nuevaX++;
        break; // Mover abajo
    case 'a':
        nuevaY--;
        break; // Mover izquierda
    case 'd':
        nuevaY++;
        break; // Mover derecha
    }

    if (esMovimientoValido(nuevaX, nuevaY))
    {
        personaje.x = nuevaX;
        personaje.y = nuevaY;
    }
    else
    {
        std::cout << "Movimiento no válido!\n";
    }
}

void mostrarLaberinto()
{
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            if (i == personaje.x && j == personaje.y)
            {
                std::cout << 'P'; // Representar al personaje
            }
            else
            {
                std::cout << laberinto[i][j];
            }
        }
        std::cout << '\n';
    }
}

int main()
{
    char input;
    while (true)
    {
        mostrarLaberinto();
        std::cout << "Mueve al personaje (w: arriba, s: abajo, a: izquierda, d: derecha, q: salir): ";
        std::cin >> input;

        if (input == 'q')
            break;

        moverPersonaje(input);
    }

    return 0;
}
