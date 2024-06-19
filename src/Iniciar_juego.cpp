#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

// Function to calculate the direction vector from the enemy to the player
sf::Vector2f calculateDirection(const sf::Vector2f &enemyPos, const sf::Vector2f &playerPos)
{
    sf::Vector2f dir = playerPos - enemyPos;
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0)
        dir /= length;
    return dir;
}

int main()
{
    // --------------------------- MUSICA -------------------------------
    sf::Music music;
    if (!music.openFromFile("assets/Music/Inicio_Final.mp3"))
    {
        // Error al cargar el archivo de música
        return -1;
    }

    // Reproducir la música en bucle
    music.setLoop(true);
    music.play();
    // --------------------------- MUSICA -------------------------------

    sf::RenderWindow window(sf::VideoMode(640, 640), "Inicio de Juego");
    sf::CircleShape player(10.f);
    sf::CircleShape enemy(10.f);
    player.setFillColor(sf::Color::Green);
    enemy.setFillColor(sf::Color::Red);

    // Set initial positions
    player.setPosition(400.f, 300.f);
    enemy.setPosition(100.f, 100.f);

    float enemySpeed = 0.5f; // Enemy speed
    float moveSpeed = 1.f;   // Player speed

    // Start screen
    bool gameStarted = false;
    sf::Font font;
    if (!font.loadFromFile("assets/Font/adventure-atari-2600.ttf"))
    {
        // Handle error
    }

    sf::Text gameName("ADVENTURE_2.0", font, 40);
    sf::Text startGame("Start Game", font, 20);
    sf::Text exitGame("Exit Game", font, 20);

    gameName.setPosition(90.f, 100.f);
    gameName.setFillColor(sf::Color::Yellow);
    startGame.setPosition(230.f, 350.f);
    exitGame.setPosition(240.f, 400.f);

    while (window.isOpen())
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
        if (!gameStarted)
        {
            window.draw(gameName);
            window.draw(startGame);
            window.draw(exitGame);
        }
        else
        {
            // Game loop
            // Update enemy position
            sf::Vector2f direction = calculateDirection(enemy.getPosition(), player.getPosition());
            enemy.move(direction * enemySpeed);

            window.draw(player);
            window.draw(enemy);
                }
        window.display();
    }

    return 0;
}
