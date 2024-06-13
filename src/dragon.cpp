#include <Dragon.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dragon");
    Dragon dragon;

    dragon.Update();

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
        //     Entidad::move(Entidad::velocidad * -1, 0);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        //     dragon.move(dragon.velocidad, 0);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        //     dragon.move(0, dragon.velocidad * -1);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        //     dragon.move(0, dragon.velocidad);

        // Actualizar animacion
        dragon.Update();

        window.clear();
        dragon.Draw(window);
        window.display();
    }

    return 0;
}