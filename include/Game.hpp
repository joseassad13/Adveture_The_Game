#pragma once
#include <SFML/Graphics.hpp>
#include <GameObject.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <list>
#include <Key.hpp>
#include <Enemy.hpp>
#include <Puntaje.hpp>
#include <Player.hpp>
#include <Laberinto.hpp>
#include <Door.hpp>

class Game
{
public:
    sf::RenderWindow window;
    sf::Texture playerTexture;
    sf::Texture enemyTexture;
    sf::Texture swordTexture;
    sf::Texture doorTexture;
    sf::Texture keyTexture;
    Player *player;
    Enemy *enemy;
    GameObject *sword;
    Door *door;
    Key *key;
    Puntaje *puntaje;
    Laberinto laberinto;
    bool spacePressedLastFrame;
    int currentFrame;
    sf::Clock animationClock;

    Game() : window(sf::VideoMode(640, 640), "Enemy Chase Player"), 
        spacePressedLastFrame(false), 
        currentFrame(0),
        laberinto("assets/Salas/laberinto1.txt")
    {
        if (!playerTexture.loadFromFile("assets/Images/jugador_adventure.png") ||
            !enemyTexture.loadFromFile("assets/Images/dragon_adventure_actions2.png") ||
            !swordTexture.loadFromFile("assets/Images/arma.png") ||
            !doorTexture.loadFromFile("assets/Images/puerta_adventure.png") ||
            !keyTexture.loadFromFile("assets/Images/lanza_adventure.png"))
        {
            // Handle error
        }

        srand(static_cast<unsigned>(time(0)));

        player = new Player(playerTexture, sf::Vector2f(400.f, 300.f), 0.5f);
        enemy = new Enemy(enemyTexture, sf::Vector2f(100.f, 100.f), 0.3f);
        sword = new GameObject(swordTexture, sf::Vector2f(200.f, 200.f));
        door = new Door(doorTexture, sf::Vector2f(700.f, 500.f));
        key = new Key(keyTexture, sf::Vector2f(600.f, 100.f));
        puntaje = new Puntaje();
    }

    ~Game()
    {
        delete player;
        delete enemy;
        delete sword;
        delete door;
        delete key;
        delete puntaje;
    }

    void run()
    {
        while (window.isOpen())
        {
            handleEvents();
            update();
            render();
        }
    }

    void handleEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    void update()
    {
        player->update();

        if (enemy->alive)
        {
            enemy->updateMovement(player->getPosition());
            enemy->updateAnimation(4, 64, 64, animationClock, currentFrame);
        }
        else
        {
            enemy->checkRespawn();
        }

        if (player->hasSword)
        {
            sword->setPosition(player->getPosition() + player->swordOffset);

            float distanceToEnemy = std::sqrt(std::pow(player->getPosition().x - enemy->getPosition().x, 2) +
                                              std::pow(player->getPosition().y - enemy->getPosition().y, 2));
            if (distanceToEnemy < 50.f)
            {
                enemy->kill();
            }
        }

        if (!key->collected)
        {
            float distanceToKey = std::sqrt(std::pow(player->getPosition().x - key->getPosition().x, 2) +
                                            std::pow(player->getPosition().y - key->getPosition().y, 2));
            if (distanceToKey < 50.f)
            {
                player->hasKey = true;
                key->collected = true;
            }
        }

        if (player->hasKey)
        {
            float distanceToDoor = std::sqrt(std::pow(player->getPosition().x - door->getPosition().x, 2) +
                                             std::pow(player->getPosition().y - door->getPosition().y, 2));
            if (distanceToDoor < 50.f)
            {
                player->hasKey = false;
                key->respawn();
                puntaje->addScore(10);
            }
        }

        bool spacePressedThisFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        if (spacePressedThisFrame && !spacePressedLastFrame)
        {
            if (!player->hasSword)
            {
                float distanceToSword = std::sqrt(std::pow(player->getPosition().x - sword->getPosition().x, 2) +
                                                  std::pow(player->getPosition().y - sword->getPosition().y, 2));
                if (distanceToSword < 50.f)
                {
                    player->hasSword = true;
                    sword->setPosition(player->getPosition() + player->swordOffset);
                }
            }
            else
            {
                player->hasSword = false;
                sword->setPosition(player->getPosition());
            }
        }
        spacePressedLastFrame = spacePressedThisFrame;

        puntaje->updateText();
    }

    void render()
    {
       

        window.clear();
        laberinto.Draw(window);

        window.draw(player->sprite);
        if (!player->hasSword)
        {
            window.draw(sword->sprite);
        }
        if (enemy->alive)
        {
            window.draw(enemy->sprite);
        }
        if (!key->collected)
        {
            window.draw(key->sprite);
        }
        window.draw(door->sprite);
        puntaje->draw(window);
        window.display();
    }
};