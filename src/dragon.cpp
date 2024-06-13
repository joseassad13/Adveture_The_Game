#include <Dragon.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 640), "Dragon");
    Dragon dragon;

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
        // Actualizar animacion
        dragon.Update();

        window.clear();
        dragon.Draw(window);
        window.display();
    }

    return 0;
}