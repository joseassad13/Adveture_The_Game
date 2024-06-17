#pragma once 
#include <SFML/Graphics.hpp>
#include <math.h>


class Puntaje
{
public:
    sf::Font font;
    sf::Text scoreText;
    sf::Text timeText;
    int score;
    sf::Clock gameClock;

    Puntaje()
    {
        if (!font.loadFromFile("assets/Font/adventure-atari-2600.ttf"))
        {
            // Handle error
        }

        score = 0;
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10.f, 10.f);

        timeText.setFont(font);
        timeText.setCharacterSize(24);
        timeText.setFillColor(sf::Color::White);
        timeText.setPosition(10.f, 40.f);

        updateText();
    }

    void addScore(int points)
    {
        score += points;
        updateText();
    }

    void updateText()
    {
        scoreText.setString("Score: " + std::to_string(score));
        int elapsedSeconds = static_cast<int>(gameClock.getElapsedTime().asSeconds());
        int minutes = elapsedSeconds / 60;
        int seconds = elapsedSeconds % 60;
        timeText.setString("Time: " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(scoreText);
        window.draw(timeText);
    }
};
