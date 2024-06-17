#include <SFML/Graphics.hpp>
#include <iomanip> // For std::setprecision
#include <sstream> // For std::stringstream

int main()
{
    //----------------- CREACION DE VENTANA -----------------------------

    sf::RenderWindow window(sf::VideoMode(800, 600), "Clock and Counter");

    // ---------------- DEFINICION DE FUENTE PARA LETRA -------------------

    sf::Font font;
    if (!font.loadFromFile("assets/Font/adventure-atari-2600.ttf"))
    {
    }

    sf::Text clockText("Time: 0", font, 20);
    sf::Text triesText("Tries: 0", font, 20);
    sf::Text pointsText("Points: 0", font, 20);

    // ---------------- COLOCAR CONTADORES -------------------
    float padding = 10.f;
    clockText.setPosition(window.getSize().x - 200 - padding, padding);
    triesText.setPosition(window.getSize().x - 200 - padding, clockText.getPosition().y + clockText.getLocalBounds().height + padding);
    pointsText.setPosition(window.getSize().x - 197 - padding, triesText.getPosition().y + triesText.getLocalBounds().height + padding);

    // ---------------- VALORES DE CONTADORES -------------------

    sf::Clock gameClock;
    int tries = 0;
    int points = 0;

    // ------------------ LOGICA DE JUEGO --------------------------
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        // Update clock with limited precision
        sf::Time elapsed = gameClock.getElapsedTime();
        std::stringstream timeStream;
        timeStream << std::fixed << std::setprecision(0) << elapsed.asSeconds();
        clockText.setString("Time: " + timeStream.str());

        // Update tries and points 
        // tries++;
        // points += 10;

        triesText.setString("Tries: " + std::to_string(tries));
        pointsText.setString("Points: " + std::to_string(points));


        window.clear();
        window.draw(clockText);
        window.draw(triesText);
        window.draw(pointsText);
        window.display();
    }

    return 0;
}
