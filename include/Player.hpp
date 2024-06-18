#pragma once
#include <SFML/Graphics.hpp>
#include <GameObject.hpp>

class Player : public GameObject
{
public:
    float moveSpeed;
    bool hasSword;
    bool hasKey;
    sf::Vector2f swordOffset;

    Player(const sf::Texture &texture, const sf::Vector2f &position, float speed)
        : GameObject(texture, position), moveSpeed(speed), hasSword(false), hasKey(false), swordOffset(50.f, 0.f) {}

    void update()
    {
        bool moved = false;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x >= 1)
        {
            sprite.move(-moveSpeed, 0.f);
            moved = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !moved && sprite.getPosition().x < 640 - sprite.getTexture()->getSize().x)
        {
            sprite.move(moveSpeed, 0.f);
            moved = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !moved && sprite.getPosition().y >= 1)
        {
            sprite.move(0.f, -moveSpeed);
            moved = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !moved && sprite.getPosition().y < 640 - sprite.getTexture()->getSize().y)
        {
            sprite.move(0.f, moveSpeed);
            moved = true;
        }
    }
};





// #pragma once
// #include <SFML/Graphics.hpp>
// #include <GameObject.hpp>



// class Player : public GameObject
// {
// public:
//     float moveSpeed;
//     bool hasSword;
//     bool hasKey;
//     sf::Vector2f swordOffset;

//     Player(const sf::Texture &texture, const sf::Vector2f &position, float speed)
//         : GameObject(texture, position), moveSpeed(speed), hasSword(false), hasKey(false), swordOffset(50.f, 0.f) {}

//     void update()
//     {
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x >= 1)
//             sprite.move(-moveSpeed, 0.f);        
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sprite.getPosition().x < 640 - sprite.getTexture()->getSize().x)
//             sprite.move(moveSpeed, 0.f);
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sprite.getPosition().y >= 1)
//             sprite.move(0.f, -moveSpeed);
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sprite.getPosition().y < 640 - sprite.getTexture()->getSize().y)
//             sprite.move(0.f, moveSpeed);
//     }
// };
