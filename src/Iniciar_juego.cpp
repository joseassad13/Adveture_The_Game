#include <SFML/Graphics.hpp>
#include <cmath>

// Function to calculate the direction vector from the enemy to the player
sf::Vector2f calculateDirection(const sf::Vector2f& enemyPos, const sf::Vector2f& playerPos) {
    sf::Vector2f dir = playerPos - enemyPos;
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0) dir /= length;
    return dir;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Enemy Chase Player");
    sf::CircleShape player(10.f);
    sf::CircleShape enemy(10.f);
    player.setFillColor(sf::Color::Green);
    enemy.setFillColor(sf::Color::Red);

    // Set initial positions
    player.setPosition(400.f, 300.f);
    enemy.setPosition(100.f, 100.f);

    float enemySpeed = 0.5f; // Enemy speed
    float moveSpeed = 1.f; // Player speed

    // Start screen
    bool gameStarted = false;
    sf::Font font;
    if (!font.loadFromFile("assets/Font/adventure-atari-2600.ttf")) {
        // Handle error
    }
    
    sf::Text startGame("Start Game", font, 20);
    sf::Text exitGame("Exit Game", font, 20);
    
    startGame.setPosition(350.f, 250.f);
    exitGame.setPosition(350.f, 300.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (startGame.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    gameStarted = true;
                }
                if (exitGame.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    window.close();
                }
            }
        }

        if (!gameStarted) {
            window.clear();
            window.draw(startGame);
            window.draw(exitGame);
            window.display();
            continue;
        }

        // Game loop
        // ... rest of your game loop code ...
        
        window.clear();
        window.draw(player);
        window.draw(enemy);
        window.display();
    }

    return 0;
}
