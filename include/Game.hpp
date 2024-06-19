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
#include <Door.hpp>
#include <Key.hpp>
#include <Puntaje.hpp>
#include <GameObject.hpp>

class Game
{
public:
    const int TILE_SIZE = 32;
    const int FILAS = 20;
    const int COLUMNAS = 20;
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
    bool gameStarted;

    // Variables para la pantalla de inicio
    sf::Font font;
    sf::Text gameName;
    sf::Text startGame;
    sf::Text exitGame;
    sf::Music music;
    sf::Music gameMusic;
    float musicVolume;
    bool transitioningMusic;

    // Variables para el estado de "Victoria"
    bool gameCompletedState;
    sf::Text victoriaText;
    sf::Clock gameCompletedClock;

    Game() : window(sf::VideoMode(900, 640), "Enemy Chase Player"),
             spacePressedLastFrame(false),
             currentFrame(0),
             laberinto("assets/Salas/laberinto1.txt"),
             gameStarted(false),
             musicVolume(100.f),
             transitioningMusic(false),
             gameCompletedState(false)
    {
        if (!playerTexture.loadFromFile("assets/Images/jugador_adventure.png") ||
            !enemyTexture.loadFromFile("assets/Images/dragon_adventure_actions2.png") ||
            !swordTexture.loadFromFile("assets/Images/arma.png") ||
            !doorTexture.loadFromFile("./assets/images/textura_salas.png") ||
            !keyTexture.loadFromFile("assets/Images/lanza_adventure.png"))
        {
            // Handle error
        }

        if (!font.loadFromFile("assets/Font/adventure-atari-2600.ttf"))
        {
            // Handle error
        }

        if (!music.openFromFile("assets/Music/Inicio_Final.mp3") ||
            !gameMusic.openFromFile("assets/Music/Musica_Base.mp3"))
        {
            // Handle error
        }

        srand(static_cast<unsigned>(time(0)));
        player = new Player(playerTexture, sf::Vector2f(400.f, 300.f), 0.1f);
        enemy = new Enemy(enemyTexture, sf::Vector2f(410.f, 230.f), 0.05f);  // Inicializa la posición del enemigo en la pantalla de inicio
        sword = new GameObject(swordTexture, sf::Vector2f(255.f, 150.f));
        door = new Door(doorTexture, sf::Vector2f(600.f, 500.f));
        key = new Key(keyTexture, sf::Vector2f(550.f, 100.f));
        puntaje = new Puntaje();

        gameName = sf::Text("ADVENTURE_2.0", font, 60);
        startGame = sf::Text("--Start Game--", font, 30);
        exitGame = sf::Text("--Exit Game--", font, 30);

        gameName.setPosition(120.f, 100.f);
        gameName.setFillColor(sf::Color::Yellow);
        startGame.setPosition(250.f, 350.f);
        exitGame.setPosition(265.f, 430.f);

        music.setLoop(true);
        music.play();

        victoriaText.setFont(font);
        victoriaText.setCharacterSize(100);
        victoriaText.setFillColor(sf::Color::Yellow);
        victoriaText.setPosition(110.f, 200.f);
        victoriaText.setString("Victoria");
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
            if (gameCompletedState)
            {
                handleGameCompleted();
            }
            else if (!gameStarted)
            {
                handleStartScreenEvents();
            }
            else
            {
                if (transitioningMusic)
                {
                    transitionMusic();
                }
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
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (startGame.getGlobalBounds().contains(mousePos))
                {
                    transitioningMusic = true;
                    music.stop();
                    gameMusic.play();
                    gameStarted = true;
                    resetGame();
                }
                else if (exitGame.getGlobalBounds().contains(mousePos))
                {
                    window.close();
                    return;
                }
            }
        }

        // Cambiar el color del texto según la posición del mouse
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        startGame.setFillColor(startGame.getGlobalBounds().contains(mousePos) ? sf::Color::Red : sf::Color::White);
        exitGame.setFillColor(exitGame.getGlobalBounds().contains(mousePos) ? sf::Color::Red : sf::Color::White);

        // Actualizar animación del enemigo en la pantalla de inicio
        enemy->updateAnimation(4, 64, 64, animationClock, currentFrame);

        window.clear();
        window.draw(enemy->sprite);
        window.draw(gameName);
        window.draw(startGame);
        window.draw(exitGame);
        window.display();
    }

    void transitionMusic()
    {
        music.stop();
        gameMusic.setLoop(true);
        gameMusic.play();
        transitioningMusic = false;
    }

    void handleGameEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
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
        else
        {
            float distanceToEnemy = std::sqrt(std::pow(player->getPosition().x - enemy->getPosition().x, 2) +
                                              std::pow(player->getPosition().y - enemy->getPosition().y, 2));
            if (distanceToEnemy < 0.5f)
            {
                int danio = 1;
                puntaje->restarVidas(danio);
                enemy->setPosition(sf::Vector2f(50.f, 100.f));
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
                puntaje->addScore(100);
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
        if (puntaje->cantidadVidas <= 0)
        {
            gameOver();
        }
        if (puntaje->score >= 100)
        {
            gameCompleted();
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

    void resetGame()
    {
        delete player;
        delete enemy;
        delete sword;
        delete door;
        delete key;
        delete puntaje;

        player = new Player(playerTexture, sf::Vector2f(400.f, 300.f), 0.1f);
        enemy = new Enemy(enemyTexture, sf::Vector2f(50.f, 100.f), 0.05f);
        sword = new GameObject(swordTexture, sf::Vector2f(255.f, 150.f));
        door = new Door(doorTexture, sf::Vector2f(600.f, 500.f));
        key = new Key(keyTexture, sf::Vector2f(550.f, 100.f));
        puntaje = new Puntaje();
    }

    void gameOver()
    {
        gameStarted = false;
        gameMusic.stop();
        music.play();
        resetGame();
        enemy->setPosition(sf::Vector2f(410.f, 230.f));
    }

    void gameCompleted()
    {
        gameStarted = false;
        gameMusic.stop();
        music.play();
        gameCompletedState = true;
        gameCompletedClock.restart();
    }

    void handleGameCompleted()
    {
        if (gameCompletedClock.getElapsedTime().asSeconds() > 5.f)
        {
            gameCompletedState = false;
            // music.stop();
            // music.play();
            resetGame();
            enemy->setPosition(sf::Vector2f(410.f, 230.f));
        }
        else
        {
            window.clear();
            window.draw(victoriaText);
            window.display();
        }
    }
};
