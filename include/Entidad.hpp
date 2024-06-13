#pragma once
#include <SFML/Graphics.hpp>

class Entidad
{
private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
    float frameTime = 0.1f; // Tiempo entre cada frame en segundos
    int currentFrame = 0;
    int numFrames = 4; // Número total de frames en la animación
    int frameWidth = 32;
    int frameHeight = 32;

protected:
    double velocidad = 0.1;

public:
    Entidad(sf::Vector2f, sf::Color);
    ~Entidad();
    void move(float, float);
    void Draw(sf::RenderWindow &);
    void Update();
};

Entidad::~Entidad()
{
}

Entidad::Entidad(sf::Vector2f position, sf::Color color)
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

void Entidad::move(float offsetX, float offsetY)
{
    sprite.move(offsetX, offsetY);
    shape.move(offsetX, offsetY);
}

void Entidad::Draw(sf::RenderWindow &window)
{
    window.draw(this->shape);
    window.draw(this->sprite);
}

void Entidad::Update()
{
    // Actualizar el frame de la animación
    if (clock.getElapsedTime().asSeconds() >= frameTime)
    {
        currentFrame = (currentFrame + 1) % numFrames;
        sprite.setTextureRect(sf::IntRect((currentFrame * 64) + 17, 133, 64, 36));
        clock.restart();
    }
}
