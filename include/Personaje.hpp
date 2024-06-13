#pragma once
#include <Entidad.hpp>
#include <SFML/Graphics.hpp>
#include <experimental/random>

class Personaje : public Entidad
{
public:
    // Personaje() : Entidad(sf::Vector2f(350, 350), sf::Color::Red){
    Personaje() : Entidad(sf::Vector2f(std::rand(), std::rand()), sf::Color::Red){

    }
private:
    void update(){
        Entidad::update();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            Entidad::move(Entidad::velocidad * -1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            Entidad::move(Entidad::velocidad, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            Entidad::move(0, Entidad::velocidad * -1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            Entidad::move(0, Entidad::velocidad);
    }
    
};



