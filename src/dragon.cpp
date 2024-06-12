#include "Dragon.hpp"


Dragon::Dragon(sf::Vector2f position, sf::Color color)
    {
        //shape.setSize(sf::Vector2f(100, 100));
        shape.setPosition(position); // Posición inicial cuadro
        shape.setFillColor(color);

        // Cargar la imagen desde un archivo
        
        if (!texture.loadFromFile("assets/dragon_adventure_actions.png"))
        {
        
        }
        this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(position); // Posición inicial sprite
    }


void Dragon::move(float offsetX, float offsetY)
    {
        sprite.move(offsetX, offsetY);
        shape.move(offsetX, offsetY);
    }

void Dragon::draw(sf::RenderWindow &window)
    {
        window.draw(this->shape);
        window.draw(this->sprite);
    }

void Dragon::update(){
        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            sprite.setTextureRect(sf::IntRect((currentFrame * 6)+10, 20, 300, 300));
            clock.restart();
        }
    }

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dragon");

    Dragon dragon(sf::Vector2f(350, 350), sf::Color::Red);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            dragon.move(dragon.velocidad * -1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            dragon.move(dragon.velocidad, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            dragon.move(0, dragon.velocidad * -1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            dragon.move(0, dragon.velocidad);
        
        

        // Actualizar animacion 
        dragon.update();

        window.clear();
        dragon.draw(window);
        window.display();
    }

    return 0;
}