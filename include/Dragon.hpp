#include <SFML/Graphics.hpp>

#ifndef DRAGON_H
#define DRAGON_H
class Dragon
{
public:
    Dragon(sf::Vector2f, sf::Color);
    void move(float, float);
    void draw(sf::RenderWindow&);
    void update();
    double velocidad = 0.5;
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