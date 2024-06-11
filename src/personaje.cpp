#include "Personaje.hpp"


Personaje::Personaje(sf::Vector2f position, sf::Color color)
    {
        shape.setSize(sf::Vector2f(50, 50));
        shape.setPosition(position); // Posición inicial cuadro
        shape.setFillColor(color);

        // Cargar la imagen desde un archivo
        
        if (!texture.loadFromFile("assets/jugador_adventure.png"))
        {
        
        }
        this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(position); // Posición inicial sprite
    }


void Personaje::move(float offsetX, float offsetY)
    {
        sprite.move(offsetX, offsetY);
        shape.move(offsetX, offsetY);
    }

void Personaje::draw(sf::RenderWindow &window)
    {
        window.draw(this->shape);
        window.draw(this->sprite);
    }

void Personaje::update(){
        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            sprite.setTextureRect(sf::IntRect((currentFrame * 64)+17, 133, 64, 36));
            clock.restart();
        }
    }

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Personaje");

    Personaje personaje(sf::Vector2f(350, 350), sf::Color::Red);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            personaje.move(personaje.velocidad * -1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            personaje.move(personaje.velocidad, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            personaje.move(0, personaje.velocidad * -1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            personaje.move(0, personaje.velocidad);
        
        

        // Actualizar animacion 
        //personaje.update();

        window.clear();
        personaje.draw(window);
        window.display();
    }

    return 0;
}