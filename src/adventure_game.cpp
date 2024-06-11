#include<SFML/Graphics.hpp>
#include "pared.cpp"
#include "sala.cpp"
#include "personaje.cpp"

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