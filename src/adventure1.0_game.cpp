#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <list>
#include "Laberinto.hpp"  // Incluir la definición de la clase Laberinto
using namespace std;

// Function to calculate the direction vector from the enemy to the player
sf::Vector2f calculateDirection(const sf::Vector2f &enemyPos, const sf::Vector2f &playerPos)
{
    sf::Vector2f dir;
    float deltaX = playerPos.x - enemyPos.x;
    float deltaY = playerPos.y - enemyPos.y;

    // Move only horizontally or vertically
    if (std::abs(deltaX) > std::abs(deltaY))
    {
        dir.x = (deltaX > 0) ? 1.f : -1.f;
        dir.y = 0;
    }
    else
    {
        dir.x = 0;
        dir.y = (deltaY > 0) ? 1.f : -1.f;
    }
    return dir;
}

// Function to update enemy animation
void updateEnemyAnimation(sf::Sprite &enemySprite, sf::Clock &clock, int &frame, int frameCount, int frameWidth, int frameHeight)
{
    if (clock.getElapsedTime().asSeconds() > 0.2f)
    { // Change frame every 0.2 seconds
        frame = (frame + 1) % frameCount;
        enemySprite.setTextureRect(sf::IntRect(frame * frameWidth, 0, frameWidth, frameHeight));
        clock.restart();
    }
}

int main()
{
    sf::Music music;
    // Load music
    if (!music.openFromFile("./assets/Music/Musica_Base.mp3"))
    {
        std::cerr << "Error al cargar el archivo de música." << std::endl;
        return -1;
    }

    music.setLoop(true);
    music.play();

    // Window dimensions
    float windowHeight = 640;
    float windowWidth = 640;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Lector laberinto");

    // Textures for player, enemy, and sword
    sf::Texture playerTexture, enemyTexture, swordTexture;
    if (!playerTexture.loadFromFile("assets/Images/jugador_adventure.png") ||
        !enemyTexture.loadFromFile("assets/Images/dragon_adventure.png") ||
        !swordTexture.loadFromFile("assets/Images/arma.png"))
    {
        std::cerr << "Error al cargar una o más texturas." << std::endl;
        return -1;
    }

    // Sprites for player, enemy, and sword
    sf::Sprite playerSprite(playerTexture);
    sf::Sprite enemySprite(enemyTexture);
    sf::Sprite swordSprite(swordTexture);

    // Initial positions and settings
    playerSprite.setPosition(400.f, 300.f);
    enemySprite.setPosition(100.f, 100.f);
    enemySprite.setScale(0.2f, 0.1f);
    swordSprite.setPosition(200.f, 200.f);

    // Game variables
    float enemySpeed = 0.05f;
    float moveSpeed = 0.1f;
    bool hasSword = false;
    bool spacePressedLastFrame = false;

    const int FRAME_WIDTH = 64;
    const int FRAME_HEIGHT = 64;
    const int ANIMATION_FRAMES = 4;
    int currentFrame = 0;
    sf::Clock animationClock;

    // Laberinto variables
    std::string filename = "./assets/salas/laberinto1.txt";
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
        return 1;
    }

    // Texture for laberinto blocks
    sf::Texture blockTexture;
    if (!blockTexture.loadFromFile("./assets/images/textura_salas.png"))
    {
        std::cerr << "Error al cargar la textura de bloques del laberinto." << std::endl;
        return -1;
    }

    Laberinto laberinto; // Crear instancia de la clase Laberinto

    // Leer y crear el laberinto
    int y = 0;
    std::string line;
    while (std::getline(inputFile, line))
    {
        int x = 0;
        for (auto &&symbol : line)
        {
            sf::Sprite blockSprite;
            switch (symbol)
            {
                case '0':
                    blockSprite = laberinto.generarBloque(0, blockTexture);
                    break;
                case '1':
                    blockSprite = laberinto.generarBloque(1, blockTexture);
                    break;
                case '2':
                    blockSprite = laberinto.generarBloque(2, blockTexture);
                    break;
                default:
                    // Handle unrecognized symbols
                    break;
            }
            blockSprite.setPosition(sf::Vector2f(x * 32, y * 32));
            laberinto.generarBloque(blockSprite); // Agregar bloque al laberinto
            x++;
        }
        y++;
    }
    inputFile.close();

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Player movement
        bool moveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        bool moveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        bool moveUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool moveDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

        if (moveLeft && playerSprite.getPosition().x > 0)
            playerSprite.move(-moveSpeed, 0.f);
        else if (moveRight && playerSprite.getPosition().x < window.getSize().x - playerTexture.getSize().x)
            playerSprite.move(moveSpeed, 0.f);
        else if (moveUp && playerSprite.getPosition().y > 0)
            playerSprite.move(0.f, -moveSpeed);
        else if (moveDown && playerSprite.getPosition().y < window.getSize().y - playerTexture.getSize().y)
            playerSprite.move(0.f, moveSpeed);

        // Enemy movement
        sf::Vector2f direction = calculateDirection(enemySprite.getPosition(), playerSprite.getPosition());
        enemySprite.move(direction * enemySpeed);

        // Sword interaction
        bool spacePressedThisFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        if (spacePressedThisFrame && !spacePressedLastFrame)
        {
            if (!hasSword)
            {
                float distance = std::sqrt(std::pow(playerSprite.getPosition().x - swordSprite.getPosition().x, 2) +
                                           std::pow(playerSprite.getPosition().y - swordSprite.getPosition().y, 2));
                if (distance < 50.f)
                {
                    hasSword = true;
                    swordSprite.setPosition(playerSprite.getPosition() + sf::Vector2f(50.f, 0.f));
                }
            }
            else
            {
                hasSword = false;
                swordSprite.setPosition(playerSprite.getPosition());
            }
        }
        spacePressedLastFrame = spacePressedThisFrame;

        // Draw everything
        window.clear();
        laberinto.Draw(window); // Dibujar el laberinto

        window.draw(playerSprite);
        if (!hasSword)
            window.draw(swordSprite);
        window.draw(enemySprite);

        window.display();
    }

    return 0;
}


// #include <iostream>
// #include <fstream>
// #include <SFML/Graphics.hpp>
// #include <cmath>
// #include <list>
// #include <SFML/Audio.hpp>
// #include <Laberinto.hpp>
// using namespace std;

// // Function to calculate the direction vector from the enemy to the player
// sf::Vector2f calculateDirection(const sf::Vector2f &enemyPos, const sf::Vector2f &playerPos)
// {
//     sf::Vector2f dir;
//     float deltaX = playerPos.x - enemyPos.x;
//     float deltaY = playerPos.y - enemyPos.y;

//     // Move only horizontally or vertically
//     if (std::abs(deltaX) > std::abs(deltaY))
//     {
//         dir.x = (deltaX > 0) ? 1.f : -1.f;
//         dir.y = 0;
//     }
//     else
//     {
//         dir.x = 0;
//         dir.y = (deltaY > 0) ? 1.f : -1.f;
//     }
//     return dir;
// }

// // Function to update enemy animation
// void updateEnemyAnimation(sf::Sprite &enemySprite, sf::Clock &clock, int &frame, int frameCount, int frameWidth, int frameHeight)
// {
//     if (clock.getElapsedTime().asSeconds() > 0.2f)
//     { // Change frame every 0.2 seconds
//         frame = (frame + 1) % frameCount;
//         enemySprite.setTextureRect(sf::IntRect(frame * frameWidth, 0, frameWidth, frameHeight));
//         clock.restart();
//     }
// }
// //------------------------------------------generador de mapas--------------------------------------------------//
// int main()
// {
//     sf::Music music;
//     // --------------------------- MUSICA -------------------------------
//     if (!music.openFromFile("./assets/Music/Musica_Base.mp3"))
//     {
//         // Error al cargar el archivo de música
//         return -1;
//     }

//     // Reproducir la música
//     music.setLoop(true); // Reproducir en bucle
//     music.play();
//     // --------------------------- MUSICA -------------------------------

//     float windowHeight = 640;
//     float windowWidth = 640;
//     sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Lector laberinto");
//     // Personaje personaje;
//     Laberinto *laberinto;

//     // Leer el archivo línea por línea
//     std::string line;
//     list<list<sf::Sprite>> Personaje;
//     list<list<sf::Sprite>> mapa1;

//     // --------------------------------------------------entidaddes--------------------------------------------------------//

//     // Load textures
//     sf::Texture playerTexture;
//     if (!playerTexture.loadFromFile("assets/Images/jugador_adventure.png"))
//     {
//         // Handle error
//     }

//     sf::Texture enemyTexture;
//     if (!enemyTexture.loadFromFile("assets/Images/dragon_adventure.png"))
//     {
//         // Handle error
//     }

//     sf::Texture swordTexture;
//     if (!swordTexture.loadFromFile("assets/Images/arma.png"))
//     {
//         // Handle error
//     }

//     // Create sprites
//     sf::Sprite playerSprite(playerTexture);
//     sf::Sprite enemySprite(enemyTexture);
//     sf::Sprite swordSprite(swordTexture);

//     // Set initial positions
//     playerSprite.setPosition(400.f, 300.f);
//     enemySprite.setPosition(100.f, 100.f);
//     enemySprite.setScale(0.2f, 0.1f);
//     swordSprite.setPosition(200.f, 200.f); // Set initial position for the sword

//     float enemySpeed = 0.05f;            // Enemy speed
//     float moveSpeed = 0.1f;              // Player speed
//     bool hasSword = false;               // Flag to check if player has grabbed the sword
//     bool spacePressedLastFrame = false;  // To check if space was pressed in the last frame
//     bool enemyAlive = true;              // Flag to check if the enemy is alive
//     sf::Vector2f swordOffset(50.f, 0.f); // Offset of the sword from the player

//     const int FRAME_WIDTH = 64;     // Width of each animation frame
//     const int FRAME_HEIGHT = 64;    // Height of each animation frame
//     const int ANIMATION_FRAMES = 4; // Number of frames in your animation
//     int currentFrame = 0;
//     sf::Clock animationClock; // Clock to control animation timing

//     // -------------------------------------------------laberinto---------------------------------------------------------//
//     // Nombre del archivo
//     std::string filename = "./assets/salas/laberinto1.txt";

//     // Crear un objeto ifstream
//     std::ifstream inputFile(filename);

//     // Verificar si el archivo se abrió correctamente
//     if (!inputFile.is_open())
//     {
//         std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
//         return 1;
//     }

//     sf::Texture texturaBloques;
//     if (!texturaBloques.loadFromFile("./assets/images/textura_salas.png"))
//     {
//         return -1;
//     }

//     int y = 0;
//     while (std::getline(inputFile, line))
//     {
//         // std::cout << line << std::endl;
//         list<sf::Sprite> temp;
//         int x = 0;
//         for (auto &&simbolo : line)
//         {
//             sf::Sprite bloque;
//             if (simbolo == '0')
//             {
//                 bloque = laberinto->generarBloque(0, texturaBloques);
//             }
//             if (simbolo == '1')
//             {
//                 bloque = laberinto->generarBloque(1, texturaBloques);
//             }
//             if (simbolo == '2')
//             {
//                 bloque = laberinto->generarBloque(2, texturaBloques);
//             }
//             bloque.setPosition(sf::Vector2f(x * 32, y * 32));
//             temp.emplace_back(bloque);
//             x++;
//         }
//         mapa1.emplace_back(temp);
//         y++;
//     }

//     // Cerrar el archivo
//     inputFile.close();
//     // --------------------------------------------abrir pestaña--------------------------------------------------------------//
//     while (window.isOpen())
//     {
//         sf::Event event;

//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//             {
//                 window.close();
//             }
//         }
//         // -----------------------------------------persecucion-----------------------------------------------------------------//
//         bool moveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
//         bool moveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
//         bool moveUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
//         bool moveDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

//         if (moveLeft && playerSprite.getPosition().x > 0)
//         {
//             playerSprite.move(-moveSpeed, 0.f);
//         }
//         else if (moveRight && playerSprite.getPosition().x < window.getSize().x - playerTexture.getSize().x)
//         {
//             playerSprite.move(moveSpeed, 0.f);
//         }
//         else if (moveUp && playerSprite.getPosition().y > 0)
//         {
//             playerSprite.move(0.f, -moveSpeed);
//         }
//         else if (moveDown && playerSprite.getPosition().y < window.getSize().y - playerTexture.getSize().y)
//         {
//             playerSprite.move(0.f, moveSpeed);
//         }

//         // Enemy chases player with speed limit
//         sf::Vector2f direction = calculateDirection(enemySprite.getPosition(), playerSprite.getPosition());
//         enemySprite.move(direction * enemySpeed); // Move enemy towards the player at a slower speed

//         // Update sword position if grabbed
//         if (hasSword)
//         {
//             swordSprite.setPosition(playerSprite.getPosition() + swordOffset);
//         }

//         // Toggle grabbing and dropping the sword
//         bool spacePressedThisFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
//         if (spacePressedThisFrame && !spacePressedLastFrame)
//         {
//             if (!hasSword)
//             {
//                 float distance = std::sqrt(std::pow(playerSprite.getPosition().x - swordSprite.getPosition().x, 2) +
//                                            std::pow(playerSprite.getPosition().y - swordSprite.getPosition().y, 2));
//                 if (distance < 50.f)
//                 { // Arbitrary distance to check if player is near enough to grab the sword
//                     hasSword = true;
//                     swordSprite.setPosition(playerSprite.getPosition() + swordOffset);
//                 }
//             }
//             else
//             {
//                 hasSword = false;
//                 swordSprite.setPosition(playerSprite.getPosition());
//             }
//         }
//         spacePressedLastFrame = spacePressedThisFrame;

//         // --------------------------------------------------imprimir en ventana--------------------------------------------------------//

//         window.clear();
//         for (auto &&linea : mapa1)
//         {
//             for (auto &&bloque : linea)
//             {
//                 window.draw(bloque);
//             }
//         }
//         window.draw(playerSprite);
//         if (!hasSword)
//         {
//             window.draw(swordSprite); // Draw the sword only if it's not grabbed
//         }
//         window.draw(enemySprite);
//         window.display();
//         if (music.getStatus() != sf::Music::Playing)
//         {
//             window.close();
//         }
//         // personaje.Update();
//         // personaje.Draw(window);
//         // window.display();
//     }

//     return 0;
// }
