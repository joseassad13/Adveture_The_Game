#pragma once 
#include <SFML/Graphics.hpp>

class Puntaje
{
public:
    sf::Font font;
    sf::Text scoreText;
    sf::Text timeText;
    sf::Text vidas;
    int cantidadVidas;
    int score;
    sf::Clock gameClock;

    Puntaje()
    {
        if (!font.loadFromFile("assets/Font/adventure-atari-2600.ttf"))
        {
        //    handle error
        }

        cantidadVidas = 5;
        vidas.setFont(font);
        vidas.setCharacterSize(24);
        vidas.setFillColor(sf::Color::White);
        vidas.setPosition(650.f, 600.f);

        score = 0;
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(650.f, 290.f);

        timeText.setFont(font);
        timeText.setCharacterSize(24);
        timeText.setFillColor(sf::Color::White);
        timeText.setPosition(650.f, 10.f);

        updateText();
    }

    void addScore(int points)
    {
        score += points;
        updateText();
    }
    void restarVidas(int danio)
    {
        cantidadVidas -= danio;
        updateText();
    }

    void updateText()
    {
        int elapsedSeconds = static_cast<int>(gameClock.getElapsedTime().asSeconds());
        int minutes = elapsedSeconds / 60;
        int seconds = elapsedSeconds % 60;
        timeText.setString("Time: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
        scoreText.setString("Score: " + std::to_string(score));
        vidas.setString("Vidas: " + std::to_string(cantidadVidas));
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(scoreText);
        window.draw(timeText);
        window.draw(vidas);
    }
};