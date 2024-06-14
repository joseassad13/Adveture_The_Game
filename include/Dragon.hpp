#pragma once
#include <Entidad.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class FileNotFoundException
{
private:
    std::string file;

public:
    FileNotFoundException(std::string File)
    {
        this->file = file;
    }
};

class Dragon : public Entidad
{
public:
    sf::RectangleShape dragon;
    sf::Vector2f position;
    sf::Color color;
    Dragon() : Entidad(sf::Vector2f(350, 350), sf::Color::Red)
    {
        this->shape.setSize(sf::Vector2f(69,185));
        this->shape.setPosition(position); // Posición inicial cuadro
        this ->shape.setScale(sf::Vector2(2.5f,2.5f));
        this->shape.setFillColor(color);
        this->shape.setScale(sf::Vector2f(.5f, .5f));

        // Cargar la imagen desde un archivo
        std::string file = "assets/Images/dragon_adventure_actions2.png";
        if (!texture.loadFromFile(file))
        {
            // throw new FileNotFoundException(file);
        }
        this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(position); // Posición inicial sprite
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

// Dragon::Dragon(sf::Vector2f position, sf::Color color)
// {
//     // shape.setSize(sf::Vector2f(100, 100));
//     shape.setPosition(position); // Posición inicial cuadro
//     shape.setFillColor(color);

//     // Cargar la imagen desde un archivo
//     std::string file = "assets/dragon_adventure_actions2.png";
//     if (!texture.loadFromFile(file))
//     {
//         throw new FileNotFoundException(file);
//     }
//     this->sprite = sf::Sprite(texture);
//     this->sprite.setPosition(position); // Posición inicial sprite
// }

// void Dragon::move(float offsetX, float offsetY)
// {
//     sprite.move(offsetX, offsetY);
//     shape.move(offsetX, offsetY);
// }

// void Dragon::Draw(sf::RenderWindow &window)
// {
//     window.Draw(this->shape);
//     window.Draw(this->sprite);
// }

// void Dragon::Update()
// {
//     // Actualizar el frame de la animación
//     if (clock.getElapsedTime().asSeconds() >= frameTime)
//     {
//         currentFrame = (currentFrame + 1) % numFrames;
//         sprite.setTextureRect(sf::IntRect((currentFrame * 69), 0, 69, 185));
//         clock.restart();
//     }
// }