#pragma once
#include <Jugador.hpp>
#include <SFML/Graphics.hpp>

class Juego
{
private:
    Jugador jugador;
    sf::Vector2f calculateDirection(const sf::Vector2f &enemyPos, const sf::Vector2f &playerPos)
    {
        sf::Vector2f dir = playerPos - enemyPos;
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (length != 0)
            dir /= length;
        return dir;
    }
    sf::CircleShape player(10.f);
    sf::CircleShape enemy(10.f);
    sf::Font font;
    sf::Event event;
    float enemySpeed = 0.5f; // Enemy speed
    float moveSpeed = 1.f;   // Player speed
    bool gameStarted = false;

public:
    Juego() {}
    ~Juego() {}
    void IniciarJuego() {}
};

void Juego::IniciarJuego(sf::RenderWindow &window)
{
    // Load font
    if (!font.loadFromFile("assets/Font/adventure-atari-2600.ttf"))
    {
        // Handle error
    }

    // Setup text
    sf::Text startGame("Start Game", font, 20);
    sf::Text exitGame("Exit Game", font, 20);
    startGame.setPosition(350.f, 250.f);
    exitGame.setPosition(350.f, 300.f);

    // Game loop
    while (window.isOpen())
    {
        // Event handling
        while (window.pollEvent(event))
        {
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

        // Start screen
        if (!gameStarted)
        {
            window.clear();
            window.draw(startGame);
            window.draw(exitGame);
            window.display();
        }
        else
        {
            // Game started - implement game logic here
        }
    }


}