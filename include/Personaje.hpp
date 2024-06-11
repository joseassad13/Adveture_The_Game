#include <SFML/Graphics.hpp>

#ifndef PERSONAJE_H
#define PERSONAJE_H
class Personaje
{
public:
    Personaje(sf::Vector2f, sf::Color);
    void move(float, float);
    void draw(sf::RenderWindow&);
    void update();
    double velocidad = 0.01;
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
    
};
#endif