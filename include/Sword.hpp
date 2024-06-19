#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Sword : public sf::Sprite
{
private:
    int danio;
    bool collected;

    sf::Texture texture;

public:
    sf::Sprite sprite;
    sf::Vector2f position;
    Sword(const sf::Texture &texture, const sf::Vector2f &initialPosition)
        : texture(texture), collected(false)
    {
        setTexture(texture);
        setPosition(initialPosition);
        position = initialPosition;
    }

    ~Sword() {}

    void Atacar() {}

    bool isCollected() const { return collected; }

    void collect()
    {
        collected = true;
        // Hide the sword when collected
        setPosition(-100, -100); // Move it off-screen
    }

    void drop(const sf::Vector2f &newPosition)
    {
        collected = false;
        setPosition(newPosition);
    }

    void updatePosition(const sf::Vector2f &playerPosition, const sf::Vector2f &offset)
    {
        setPosition(playerPosition + offset);
    }

    float getDistanceTo(const sf::Vector2f &otherPosition) const
    {
        return std::sqrt(std::pow(getPosition().x - otherPosition.x, 2) +
                         std::pow(getPosition().y - otherPosition.y, 2));
    }
    void move(const sf::Vector2f &offset)
    {
        sprite.move(offset);
    }
};