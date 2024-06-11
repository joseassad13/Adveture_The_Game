#include <SFML/Graphics.hpp>
#include "Pared.hpp"
#include <vector>

#ifndef SALA_H
#define SALA_H
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
    std::vector< std::vector<Pared *> > paredes;
    int tamanioPared;
    Sala();
};


#endif