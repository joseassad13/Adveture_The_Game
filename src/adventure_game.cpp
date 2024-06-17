#include <iostream>
#include <vector>

// Representación simplificada del laberinto (puedes adaptarla según tus necesidades)
std::vector<std::vector<char>> laberinto = {
    {'#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', '#'}};

bool esPared(int fila, int columna)
{
    return laberinto[fila][columna] == '#';
}

int main()
{
    int filaActual = 1;
    int columnaActual = 1;

    // Ejemplo: mover hacia la derecha
    int nuevaFila = filaActual;
    int nuevaColumna = columnaActual + 1;

    if (!esPared(nuevaFila, nuevaColumna))
    {
        // La próxima posición no es una pared, permite el movimiento
        filaActual = nuevaFila;
        columnaActual = nuevaColumna;
        std::cout << "Personaje movido a (" << filaActual << ", " << columnaActual << ")\n";
    }
    else
    {
        std::cout << "¡No puedes atravesar la pared!\n";
    }

    return 0;
}