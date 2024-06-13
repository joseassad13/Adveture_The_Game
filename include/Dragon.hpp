#pragma once
#include <SFML/Graphics.hpp>
#include <Entidad.hpp>
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
    Dragon();
    // Dragon(sf::Vector2f, sf::Color);
    // void move(float, float);
    // void Draw(sf::RenderWindow &);
    // void Update();
    // double velocidad = 0.5;

private:
    // sf::RectangleShape shape;
    // sf::Sprite sprite;
    // sf::Texture texture;
    // sf::Clock clock;
    // float frameTime = 0.1f; // Tiempo entre cada frame en segundos
    // int currentFrame = 0;
    // int numFrames = 4; // Número total de frames en la animación
    // int frameWidth = 32;
    // int frameHeight = 32;
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