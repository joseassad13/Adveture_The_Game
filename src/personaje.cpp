#include <Personaje.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 640), "Personaje");
    Personaje personaje;

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
        personaje.Update();

        window.clear();
        personaje.Draw(window);
        window.display();
    }

    return 0;
}