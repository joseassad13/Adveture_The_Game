#pragma once
#include <Entidad.hpp>
#include <SFML/Graphics.hpp>
#include <experimental/random>

class Personaje : public Entidad
{
public:
    sf::Vector2f position;
    sf::Color color;
    Personaje() : Entidad(sf::Vector2f (300, 350), sf::Color::Red)
    {
       this-> shape.setPosition(position); // Posición inicial cuadro
       this-> shape.setFillColor(color);
       this-> shape.setScale(sf::Vector2f(.5f,.5f));

    //Cargar la imagen desde un archivo
    std::string file = "assets/Images/jugador_adventure.png";
    if (!texture.loadFromFile(file))
    {
        //throw new FileNotFoundException(file);
    }
    this->sprite = sf::Sprite(texture);
    this->sprite.setPosition(position);// Posición inicial sprite
    }

    void Update()
    {
        // Que haga lo que ya hacia
        Entidad::Update();

        // Que haga esto nuevo
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            Entidad::move(Entidad::velocidad * -1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            Entidad::move(Entidad::velocidad, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            Entidad::move(0, Entidad::velocidad * -1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            Entidad::move(0, Entidad::velocidad);
    }
};
