#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <list>
#include <Pared.hpp>
#include <Entidad.hpp>
#include <SFML/Audio.hpp>
#include <Personaje.hpp>
using namespace std;
//------------------------------------------generador de mapas------------------------------------------------------
int main()
{
    // Nombre del archivo
    std::string filename = "./assets/salas/laberinto1.txt";

    // Crear un objeto ifstream
    std::ifstream inputFile(filename);

    // Verificar si el archivo se abrió correctamente
    if (!inputFile.is_open())
    {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
        return 1;
    }

    float windowHeight = 640;
    float windowWidth = 960;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Lector laberinto");

    sf::Texture texturaBloques;
    if (!texturaBloques.loadFromFile("./assets/images/textura_salas.png"))
    {
        return -1;
    }

    // Leer el archivo línea por línea
    std::string line;
    list<list<sf::Sprite>> mapa1;
    int y = 0;
    while (std::getline(inputFile, line))
    {
        // std::cout << line << std::endl;
        list<sf::Sprite> temp;
        int x = 0;
        for (auto &&simbolo : line)
        {
            sf::Sprite bloque;
            if (simbolo == '0')
            {
                bloque = generarBloque(0, texturaBloques);
            }
            if (simbolo == '1')
            {
                bloque = generarBloque(1, texturaBloques);
            }
            if (simbolo == '2')
            {
                bloque = generarBloque(2, texturaBloques);
            }
            bloque.setPosition(sf::Vector2f(x * 32, y * 32));
            temp.emplace_back(bloque);
            x++;
        }
        mapa1.emplace_back(temp);
        y++;
    }

    // Cerrar el archivo
    inputFile.close();

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        for (auto &&linea : mapa1)
        {
            for (auto &&bloque : linea)
            {
                window.draw(bloque);
            }
        }

        window.display();
    }

    return 0;
}