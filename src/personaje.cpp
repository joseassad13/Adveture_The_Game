#include <Personaje.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Personaje");
    Personaje personaje;

    Personaje();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        

        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        //     Entidad::move(personaje.velocidad * -1, 0);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        //     personaje.move(personaje.velocidad, 0);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        //     personaje.move(0, personaje.velocidad * -1);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        //     personaje.move(0, personaje.velocidad);

        // Actualizar animacion
        // personaje.update();

        window.clear();
        personaje.draw(window);
        window.display();
    }

    return 0;
}