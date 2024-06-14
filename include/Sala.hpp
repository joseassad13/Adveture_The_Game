#include <SFML/Graphics.hpp>
#include <Pared.hpp>
#include <vector>
#pragma once

class Sala
{
private:
    sf::Vector2i posSalida;
    sf::Vector2i posJugador;
    std::vector<sf::Vector2i> posEnemigo;
    void setUpInitialState();
    void setUpPosEnemigo();
    void setUpParedes();

public:
    std::vector<std::vector<Pared *>> paredes;
    int tamanioPared;
    Sala();
};

Sala::Sala::Sala()
{
    tamanioPared = 8;
    setUpInitialState();
}

void Sala::setUpInitialState()
{
    posSalida = sf::Vector2i(1, 0);
    posJugador = sf::Vector2i(tamanioPared - 1, tamanioPared - 1);
    setUpPosEnemigo();
    setUpParedes();
}

void Sala::setUpPosEnemigo()
{
    posEnemigo.clear();
    posEnemigo.push_back(sf::Vector2i(0, 2));
    posEnemigo.push_back(sf::Vector2i(6, 0));
    posEnemigo.push_back(sf::Vector2i(2, 7));
}

void Sala::setUpParedes()
{
    paredes.clear();
    std::vector<Pared *> primeraLinea;
    primeraLinea.push_back(new Pared("assets/pared_adventure.png", 0, 0, false, false));
    primeraLinea.push_back(new Pared("assets/puerta_adventure.png", 50, 0, true, true));
    primeraLinea.push_back(new Pared("assets/pared_adventure.png", 100, 0, false, false));
    primeraLinea.push_back(new Pared("assets/pared_adventure.png", 150, 0, false, false));
    primeraLinea.push_back(new Pared("assets/pared_adventure.png", 200, 0, false, false));
    primeraLinea.push_back(new Pared("assets/pared_adventure.png", 250, 0, false, false));
    primeraLinea.push_back(new Pared("assets/dragon_adventure.png", 300, 0, true, false));
    primeraLinea.push_back(new Pared("assets/pared_adventure.png", 350, 0, false, false));
    paredes.push_back(primeraLinea);

    std::vector<Pared *> segundaLinea;
    segundaLinea.push_back(new Pared("assets/pared_adventure.png", 0, 50, false, false));
    segundaLinea.push_back(new Pared("assets/suelo_adventure.png", 50, 50, true, false));
    segundaLinea.push_back(new Pared("assets/suelo_adventure.png", 100, 50, true, false));
    segundaLinea.push_back(new Pared("assets/suelo_adventure.png", 150, 50, true, false));
    segundaLinea.push_back(new Pared("assets/suelo_adventure.png", 200, 50, true, false));
    segundaLinea.push_back(new Pared("assets/suelo_adventure.png", 250, 50, true, false));
    segundaLinea.push_back(new Pared("assets/suelo_adventure.png", 300, 50, true, false));
    segundaLinea.push_back(new Pared("assets/suelo_adventure.png", 350, 50, true, false));
    paredes.push_back(segundaLinea);

    std::vector<Pared *> terceraLinea;
    terceraLinea.push_back(new Pared("assets/dragon_adventure.png", 0, 100, true, false));
    terceraLinea.push_back(new Pared("assets/suelo_adventure.png", 50, 100, true, false));
    terceraLinea.push_back(new Pared("assets/suelo_adventure.png", 100, 100, true, false));
    terceraLinea.push_back(new Pared("assets/pared_adventure.png", 150, 100, false, false));
    terceraLinea.push_back(new Pared("assets/suelo_adventure.png", 200, 100, true, false));
    terceraLinea.push_back(new Pared("assets/suelo_adventure.png", 250, 100, true, false));
    terceraLinea.push_back(new Pared("assets/pared_adventure.png", 300, 100, false, false));
    terceraLinea.push_back(new Pared("assets/pared_adventure.png", 350, 100, false, false));
    paredes.push_back(terceraLinea);

    std::vector<Pared *> cuartaLinea;
    cuartaLinea.push_back(new Pared("assets/pared_adventure.png", 0, 150, false, false));
    cuartaLinea.push_back(new Pared("assets/suelo_adventure.png", 50, 150, true, false));
    cuartaLinea.push_back(new Pared("assets/suelo_adventure.png", 100, 150, true, false));
    cuartaLinea.push_back(new Pared("assets/pared_adventure.png", 150, 150, false, false));
    cuartaLinea.push_back(new Pared("assets/suelo_adventure.png", 200, 150, true, false));
    cuartaLinea.push_back(new Pared("assets/suelo_adventure.png", 250, 150, true, false));
    cuartaLinea.push_back(new Pared("assets/suelo_adventure.png", 300, 150, true, false));
    cuartaLinea.push_back(new Pared("assets/pared_adventure.png", 350, 150, false, false));
    paredes.push_back(cuartaLinea);

    std::vector<Pared *> quintaLinea;
    quintaLinea.push_back(new Pared("assets/pared_adventure.png", 0, 200, false, false));
    quintaLinea.push_back(new Pared("assets/suelo_adventure.png", 50, 200, true, false));
    quintaLinea.push_back(new Pared("assets/suelo_adventure.png", 100, 200, true, false));
    quintaLinea.push_back(new Pared("assets/pared_adventure.png", 150, 200, false, false));
    quintaLinea.push_back(new Pared("assets/pared_adventure.png", 200, 200, false, false));
    quintaLinea.push_back(new Pared("assets/suelo_adventure.png", 250, 200, true, false));
    quintaLinea.push_back(new Pared("assets/suelo_adventure.png", 300, 200, true, false));
    quintaLinea.push_back(new Pared("assets/suelo_adventure.png", 350, 200, true, false));
    paredes.push_back(quintaLinea);

    std::vector<Pared *> sextaLinea;
    sextaLinea.push_back(new Pared("assets/suelo_adventure.png", 0, 250, true, false));
    sextaLinea.push_back(new Pared("assets/suelo_adventure.png", 50, 250, true, false));
    sextaLinea.push_back(new Pared("assets/suelo_adventure.png", 100, 250, true, false));
    sextaLinea.push_back(new Pared("assets/suelo_adventure.png", 150, 250, true, false));
    sextaLinea.push_back(new Pared("assets/pared_adventure.png", 200, 250, false, false));
    sextaLinea.push_back(new Pared("assets/suelo_adventure.png", 250, 250, true, false));
    sextaLinea.push_back(new Pared("assets/suelo_adventure.png", 300, 250, true, false));
    sextaLinea.push_back(new Pared("assets/pared_adventure.png", 350, 250, false, false));
    paredes.push_back(sextaLinea);

    std::vector<Pared *> septimaLinea;
    septimaLinea.push_back(new Pared("assets/pared_adventure.png", 0, 300, false, false));
    septimaLinea.push_back(new Pared("assets/pared_adventure.png", 50, 300, false, false));
    septimaLinea.push_back(new Pared("assets/suelo_adventure.png", 100, 300, true, false));
    septimaLinea.push_back(new Pared("assets/suelo_adventure.png", 150, 300, true, false));
    septimaLinea.push_back(new Pared("assets/suelo_adventure.png", 200, 300, true, false));
    septimaLinea.push_back(new Pared("assets/suelo_adventure.png", 250, 300, true, false));
    septimaLinea.push_back(new Pared("assets/pared_adventure.png", 300, 300, false, false));
    septimaLinea.push_back(new Pared("assets/pared_adventure.png", 350, 300, false, false));
    paredes.push_back(septimaLinea);

    std::vector<Pared *> octabaLinea;
    octabaLinea.push_back(new Pared("assets/pared_adventure.png", 0, 350, false, false));
    octabaLinea.push_back(new Pared("assets/pared_adventure.png", 50, 350, false, false));
    octabaLinea.push_back(new Pared("assets/dragon_adventure.png", 100, 350, true, false));
    octabaLinea.push_back(new Pared("assets/pared_adventure.png", 150, 350, false, false));
    octabaLinea.push_back(new Pared("assets/pared_adventure.png", 200, 350, false, false));
    octabaLinea.push_back(new Pared("assets/suelo_adventure.png", 250, 350, true, false));
    octabaLinea.push_back(new Pared("assets/suelo_adventure.png", 300, 350, true, false));
    octabaLinea.push_back(new Pared("assets/jugador_adventure.png", 350, 350, true, false));
    paredes.push_back(octabaLinea);
}
