/*#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace ftxui;

int main(int argc, char const *argv[])
{
    list<string> textos;
    fstream dragon;
    dragon.open("./assets/dragon.txt");

    string linea;
    while (getline(dragon, linea))
    {
        textos.push_back(linea);
    }
    dragon.close();

    int fotograma = 0;

    string reset;
    int posX = 0;
    int posY = 6;
    while (true)
    {
        fotograma++;

        Element personaje = spinner(10, fotograma);
        Decorator colorFondo = bgcolor(Color::Aquamarine1);
        Decorator colorTexto = color(Color::Yellow1);
        Element dibujo = border({hbox(personaje)}) | colorFondo | colorTexto;

        Dimensions Alto = Dimension::Full();
        Dimensions Ancho = Dimension::Full();

        Screen pantalla = Screen::Create(Ancho, Alto);
        Render(pantalla, dibujo);

        int l = 0;
        for (auto &&texto : textos)
        {
            int i = 0;
            for (auto &&letra : texto)
            {
                pantalla.PixelAt(posX + i, posY + l).character = letra;
                i++;
            }
            l++;
        }
        posX++;

        pantalla.Print();
        reset = pantalla.ResetPosition();
        cout << reset;
        this_thread::sleep_for(0.1s);
    }

    return 0;
}*/
#include<SFML/Graphics.hpp>
#include "pared.cpp"
#include "sala.cpp"

int main(){
    float windowHeight = 400;
    float windowWidth = 400;

    sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight),"ADVENTURE");
    
    Sala sala = Sala();

    while(window.isOpen()){
        sf::Event event;


        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }

            window.clear();

            for (int i = 0; i < sala.tamanioPared; i++ ) {
                for (int j = 0; j < sala.tamanioPared; j++ ) {
                    window.draw(sala.paredes[i][j]->sprite);
                }
            }

            window.display();
        }
    }
}