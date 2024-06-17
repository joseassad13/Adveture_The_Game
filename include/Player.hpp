#pragma once
#include <Objeto.hpp>


class Player : public Objeto
{
public:
    float moveSpeed;
    bool hasSword;
    bool hasKey;
    sf::Vector2f swordOffset;

    Player(const sf::Texture &texture, const sf::Vector2f &position, float speed)
        : objetoJuego(texture, position), moveSpeed(speed), hasSword(false), hasKey(false), swordOffset(50.f, 0.f) {}

    void update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x > 0)
            sprite.move(-moveSpeed, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sprite.getPosition().x < 800 - sprite.getTexture()->getSize().x)
            sprite.move(moveSpeed, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sprite.getPosition().y > 0)
            sprite.move(0.f, -moveSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sprite.getPosition().y < 600 - sprite.getTexture()->getSize().y)
            sprite.move(0.f, moveSpeed);
    }
};