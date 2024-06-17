#include <iostream>
#include <ctime>

using namespace std;

// filas  columnas densidad
void generarLaberinto(int filas, int columnas, float densidad)
{
    // matriz doble para que sea dinamica
    int **matriz;
    matriz = new int *[filas];
    int FParedes = densidad * 10;
    densidad = filas * columnas * densidad / 4;

    // para fila crea numero de columnas
    for (int i = 0; i < filas; i++)
    {
        matriz[i] = new int[columnas];
    }
    // valores
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            // punto donde van los muros creacion de bordes
            if (i == 0 || j == 0 || i == filas - 1 || j == columnas - 1)
            {
                matriz[i][j] = 1;
            }
            else
            {
                matriz[i][j] = 0;
            }
        }
    }
    // laberinto
    srand(time(NULL));
    // ayuda a evitar que se escriba valores dentro de los muros
    for (int i = 0; i < densidad; i++)
    {
        int x = rand() % (columnas - 4) + 2;
        x = (x / 2) * 2;
        int y = rand() % (filas - 4) + 2;
        y = (y / 2) * 2;
        // se vuelve muro
        matriz[y][x] = 1;
        for (int j = 0; j < FParedes; j++)
        {
            int mx[4] = {x, x, x + 2, x - 2};
            int my[4] = {y + 2, y - 2, y, y};
            int r = rand() % 4;
            if (matriz[my[r]][mx[r]] == 0)
            {
                matriz[my[r]][mx[r]] == 1;
                matriz[my[r] + (y - my[r]) / 2][mx[r] + (x - mx[r]) / 2] = 1;
            }
        }
    }
    // pintar
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (matriz[i][j] == 1)
            {
                cout << "1";
            }
            if (matriz[i][j] == 0)
            {
                cout << "0";
            }
        }
        cout << "\n";
    }
}

int main()
{
    generarLaberinto(20, 20, .5);
}