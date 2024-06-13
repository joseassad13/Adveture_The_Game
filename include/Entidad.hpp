#pragma once
#include <SFML/Graphics.hpp>

class Entidad
{
private:
    float frameTime = 0.1f; // Tiempo entre cada frame en segundos
    int currentFrame = 0;
    int numFrames = 4; // Número total de frames en la animación
    int frameWidth = 32;
    int frameHeight = 32;

protected:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
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
    this-> shape.setSize(sf::Vector2f(69, 185));
    this-> shape.setPosition(position); // Posición inicial cuadro
    this-> shape.setFillColor(color);

    // Cargar la imagen desde un archivo

    if (!texture.loadFromFile("assets/Images/dragon_adventure_actions_2.png"))
    {
    }
    this->sprite = sf::Sprite(texture);
    this->sprite.setPosition(position); // Posición inicial sprite
}

void Entidad::move(float offsetX, float offsetY)
{
    this-> sprite.move(offsetX, offsetY);
    this->shape.move(offsetX, offsetY);
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
        this-> currentFrame = (currentFrame + 1) % numFrames;
        this-> sprite.setTextureRect(sf::IntRect((currentFrame * 69), 0, 69, 185));
        this-> clock.restart();
    }
}
