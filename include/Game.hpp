#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <list>
#include <Laberinto.hpp>
#include <Player.hpp>
#include <Enemy.hpp>
#include "Door.hpp"
#include "Key.hpp"
#include "Puntaje.hpp"


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
    bool gameStarted; // Variable para controlar si el juego ha comenzado

    // Variables para la pantalla de inicio
    sf::Font font;
    sf::Text gameName;
    sf::Text startGame;
    sf::Text exitGame;
    sf::Music music;

    Game() : window(sf::VideoMode(640, 640), "Enemy Chase Player"),
             spacePressedLastFrame(false),
             currentFrame(0),
             laberinto("assets/Salas/laberinto1.txt"),
             gameStarted(false)
    {
        if (!playerTexture.loadFromFile("assets/Images/jugador_adventure.png") ||
            !enemyTexture.loadFromFile("assets/Images/dragon_adventure_actions2.png") ||
            !swordTexture.loadFromFile("assets/Images/arma.png") ||
            !doorTexture.loadFromFile("assets/Images/puerta_adventure.png") ||
            !keyTexture.loadFromFile("assets/Images/lanza_adventure.png"))
        {
            // Handle error
        }

        if (!font.loadFromFile("assets/Font/adventure-atari-2600.ttf"))
        {
            // Handle error
        }

        if (!music.openFromFile("assets/Music/Inicio_Final.mp3"))
        {
            // Handle error
        }

        srand(static_cast<unsigned>(time(0)));

        player = new Player(playerTexture, sf::Vector2f(400.f, 300.f), 0.1f);
        enemy = new Enemy(enemyTexture, sf::Vector2f(50.f, 100.f), 0.05f);
        sword = new GameObject(swordTexture, sf::Vector2f(255.f, 150.f));
        door = new Door(doorTexture, sf::Vector2f(700.f, 500.f));
        key = new Key(keyTexture, sf::Vector2f(550.f, 100.f));
        puntaje = new Puntaje();

        gameName = sf::Text("ADVENTURE_2.0", font, 40);
        startGame = sf::Text("Start Game", font, 20);
        exitGame = sf::Text("Exit Game", font, 20);

        gameName.setPosition(90.f, 100.f);
        gameName.setFillColor(sf::Color::Yellow);
        startGame.setPosition(230.f, 350.f);
        exitGame.setPosition(240.f, 400.f);

        music.setLoop(true);
        music.play();
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
            if (!gameStarted)
            {
                handleStartScreenEvents();
            }
            else
            {
                handleGameEvents();
                update();
                render();
            }
        }
    }

    void handleStartScreenEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (startGame.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                startGame.setColor(sf::Color::Red);
            else
                startGame.setColor(sf::Color::White);

            if (exitGame.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                exitGame.setColor(sf::Color::Red);
            else
                exitGame.setColor(sf::Color::White);

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (startGame.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    gameStarted = true;
                }
                if (exitGame.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(gameName);
        window.draw(startGame);
        window.draw(exitGame);
        window.display();
    }

    void handleGameEvents()
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
        // Actualizaciones del juego solo cuando el juego ha comenzado
        if (!gameStarted)
        {
            return;
        }

        player->update();
        enemy->checkRespawn();
        enemy->updateMovement(player->getPosition());
        enemy->updateAnimation(4, 64, 64, animationClock, currentFrame);

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


// #pragma once
// #include <SFML/Graphics.hpp>
// #include <GameObject.hpp>
// #include <cmath>
// #include <string>
// #include <cstdlib>
// #include <ctime>
// #include <list>
// #include <Key.hpp>
// #include <Enemy.hpp>
// #include <Puntaje.hpp>
// #include <Player.hpp>
// #include <Laberinto.hpp>
// #include <Door.hpp>

// class Game
// {
// public:
//     sf::RenderWindow window;
//     sf::Texture playerTexture;
//     sf::Texture enemyTexture;
//     sf::Texture swordTexture;
//     sf::Texture doorTexture;
//     sf::Texture keyTexture;
//     Player *player;
//     Enemy *enemy;
//     GameObject *sword;
//     Door *door;
//     Key *key;
//     Puntaje *puntaje;
//     Laberinto laberinto;
//     bool spacePressedLastFrame;
//     int currentFrame;
//     sf::Clock animationClock;

//     Game() : window(sf::VideoMode(640, 640), "Enemy Chase Player"),
//              spacePressedLastFrame(false),
//              currentFrame(0),
//              laberinto("assets/Salas/laberinto1.txt")
//     {
//         if (!playerTexture.loadFromFile("assets/Images/jugador_adventure.png") ||
//             !enemyTexture.loadFromFile("assets/Images/dragon_adventure_actions2.png") ||
//             !swordTexture.loadFromFile("assets/Images/arma.png") ||
//             !doorTexture.loadFromFile("assets/Images/puerta_adventure.png") ||
//             !keyTexture.loadFromFile("assets/Images/lanza_adventure.png"))
//         {
//             // Handle error
//         }

//         srand(static_cast<unsigned>(time(0)));

//         player = new Player(playerTexture, sf::Vector2f(400.f, 300.f), 0.1f);
//         enemy = new Enemy(enemyTexture, sf::Vector2f(50.f, 100.f), 0.05f);
//         sword = new GameObject(swordTexture, sf::Vector2f(255.f, 150.f));
//         door = new Door(doorTexture, sf::Vector2f(700.f, 500.f));
//         key = new Key(keyTexture, sf::Vector2f(550.f, 100.f));
//         puntaje = new Puntaje();
//     }

//     ~Game()
//     {
//         delete player;
//         delete enemy;
//         delete sword;
//         delete door;
//         delete key;
//         delete puntaje;
//     }

//     void run()
//     {
//         while (window.isOpen())
//         {
//             handleEvents();
//             update();
//             render();
//         }
//     }

//     void handleEvents()
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//     }

//     void update()
//     {
//         // sf::Vector2f playerOldPos = player->getPosition();
//         // sf::Vector2f enemyOldPos = enemy->getPosition();

//         player->update();
//         // // if (laberinto.checkCollision(player->getBoundingBox()))
//         // // {
//         // //     player->setPosition(playerOldPos);
//         // // }

//         // // if (enemy->alive)
//         // // {
//             enemy->updateMovement(player->getPosition());
//         // //     if (laberinto.checkCollision(enemy->getBoundingBox()))
//         // //     {
//         // //         enemy->setPosition(enemyOldPos);
//         // //     }
//             enemy->updateAnimation(4, 64, 64, animationClock, currentFrame);
//         // }
//         // else
//         // {
//             enemy->checkRespawn();
//         // }

//         if (player->hasSword)
//         {
//             sword->setPosition(player->getPosition() + player->swordOffset);

//             float distanceToEnemy = std::sqrt(std::pow(player->getPosition().x - enemy->getPosition().x, 2) +
//                                               std::pow(player->getPosition().y - enemy->getPosition().y, 2));
//             if (distanceToEnemy < 50.f)
//             {
//                 enemy->kill();
//             }
//         }

//         if (!key->collected)
//         {
//             float distanceToKey = std::sqrt(std::pow(player->getPosition().x - key->getPosition().x, 2) +
//                                             std::pow(player->getPosition().y - key->getPosition().y, 2));
//             if (distanceToKey < 50.f)
//             {
//                 player->hasKey = true;
//                 key->collected = true;
//             }
//         }

//         if (player->hasKey)
//         {
//             float distanceToDoor = std::sqrt(std::pow(player->getPosition().x - door->getPosition().x, 2) +
//                                              std::pow(player->getPosition().y - door->getPosition().y, 2));
//             if (distanceToDoor < 50.f)
//             {
//                 player->hasKey = false;
//                 key->respawn();
//                 puntaje->addScore(10);
//             }
//         }

//         bool spacePressedThisFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
//         if (spacePressedThisFrame && !spacePressedLastFrame)
//         {
//             if (!player->hasSword)
//             {
//                 float distanceToSword = std::sqrt(std::pow(player->getPosition().x - sword->getPosition().x, 2) +
//                                                   std::pow(player->getPosition().y - sword->getPosition().y, 2));
//                 if (distanceToSword < 50.f)
//                 {
//                     player->hasSword = true;
//                     sword->setPosition(player->getPosition() + player->swordOffset);
//                 }
//             }
//             else
//             {
//                 player->hasSword = false;
//                 sword->setPosition(player->getPosition());
//             }
//         }
//         spacePressedLastFrame = spacePressedThisFrame;

//         puntaje->updateText();
//     }

//     void render()
//     {
//         window.clear();
//         laberinto.Draw(window);

//         window.draw(player->sprite);
//         if (!player->hasSword)
//         {
//             window.draw(sword->sprite);
//         }
//         if (enemy->alive)
//         {
//             window.draw(enemy->sprite);
//         }
//         if (!key->collected)
//         {
//             window.draw(key->sprite);
//         }
//         window.draw(door->sprite);
//         puntaje->draw(window);
//         window.display();
//     }
// };
