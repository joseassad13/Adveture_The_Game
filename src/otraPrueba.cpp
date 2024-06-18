#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <list>
#include <Personaje.hpp>
#include <Pared.hpp>
#include <Entidad.hpp>
#include <SFML/Audio.hpp>
#include <Personaje.hpp>

// #include <Objeto.hpp>
// #include <Key.hpp>
// #include <Game.hpp>
// #include <Enemy.hpp>
// #include <Door.hpp>
// #include <Puntaje.hpp>
// #include <Player.hpp>

class GameObject
{
public:
    sf::Sprite sprite;

    GameObject(const sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &scale = sf::Vector2f(1.f, 1.f))
    {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(scale);
    }

    void setPosition(const sf::Vector2f &position)
    {
        sprite.setPosition(position);
    }

    sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }

    void move(const sf::Vector2f &offset)
    {
        sprite.move(offset);
    }
};

class Player : public GameObject
{
public:
    float moveSpeed;
    bool hasSword;
    bool hasKey;
    sf::Vector2f swordOffset;

    Player(const sf::Texture &texture, const sf::Vector2f &position, float speed)
        : GameObject(texture, position), moveSpeed(speed), hasSword(false), hasKey(false), swordOffset(50.f, 0.f) {}

    void update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x > 0)
            sprite.move(-moveSpeed, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sprite.getPosition().x < 800 - sprite.getTexture()->getSize().x)
            sprite.move(moveSpeed, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sprite.getPosition().y > 0)
            sprite.move(0.f, -moveSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sprite.getPosition().y < 600 - sprite.getTexture()->getSize().y)
            sprite.move(0.f, moveSpeed);
    }
};

class Enemy : public GameObject
{
public:
    float speed;
    bool alive;
    sf::Clock respawnClock;

    Enemy(const sf::Texture &texture, const sf::Vector2f &position, float speed)
        : GameObject(texture, position, sf::Vector2f(0.3f, 0.3f)), speed(speed), alive(true)
    {
        sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    }

    void updateAnimation(int frameCount, int frameWidth, int frameHeight, sf::Clock &animationClock, int &currentFrame)
    {
        if (animationClock.getElapsedTime().asSeconds() > 0.2f)
        {
            currentFrame = (currentFrame + 1) % frameCount;
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            animationClock.restart();
        }
    }

    void updateMovement(const sf::Vector2f &targetPosition)
    {
        if (alive)
        {
            sf::Vector2f direction = targetPosition - sprite.getPosition();
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length != 0)
                direction /= length;
            sprite.move(direction * speed);
        }
    }

    void checkRespawn()
    {
        if (!alive && respawnClock.getElapsedTime().asSeconds() > 3.f)
        {
            alive = true;
            sprite.setPosition(100.f, 100.f);
        }
    }

    void kill()
    {
        alive = false;
        respawnClock.restart();
    }
};

class Door : public GameObject
{
public:
    Door(const sf::Texture &texture, const sf::Vector2f &position)
        : GameObject(texture, position) {}
};

class Key : public GameObject
{
public:
    bool collected;

    Key(const sf::Texture &texture, const sf::Vector2f &position)
        : GameObject(texture, position), collected(false) {}

    void respawn()
    {
        float x = static_cast<float>(rand() % (800 - static_cast<int>(sprite.getTexture()->getSize().x)));
        float y = static_cast<float>(rand() % (600 - static_cast<int>(sprite.getTexture()->getSize().y)));
        sprite.setPosition(x, y);
        collected = false;
    }
};

class Scoreboard
{
public:
    sf::Font font;
    sf::Text scoreText;
    sf::Text timeText;
    int score;
    sf::Clock gameClock;

    Scoreboard()
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

class Game
{
public:
    sf::RenderWindow window;
    sf::Texture playerTexture;
    sf::Texture enemyTexture;
    sf::Texture swordTexture;
    sf::Texture doorTexture;
    sf::Texture keyTexture;
    Player *player;
    Enemy *enemy;
    GameObject *sword;
    Door *door;
    Key *key;
    Scoreboard *scoreboard;
    bool spacePressedLastFrame;
    int currentFrame;
    sf::Clock animationClock;

    Game()
        
        : window(sf::VideoMode(800, 600), "Enemy Chase Player"), spacePressedLastFrame(false), currentFrame(0)
    {
        if (!playerTexture.loadFromFile("assets/Images/jugador_adventure.png") ||
            !enemyTexture.loadFromFile("assets/Images/dragon_adventure_actions2.png") ||
            !swordTexture.loadFromFile("assets/Images/arma.png") ||
            !doorTexture.loadFromFile("assets/Images/puerta_adventure.png") ||
            !keyTexture.loadFromFile("assets/Images/lanza_adventure.png"))
        {
            // Handle error
        }

        srand(static_cast<unsigned>(time(0)));

        player = new Player(playerTexture, sf::Vector2f(400.f, 300.f), 0.1f);
        enemy = new Enemy(enemyTexture, sf::Vector2f(100.f, 100.f), 0.05f);
        sword = new GameObject(swordTexture, sf::Vector2f(200.f, 200.f));
        door = new Door(doorTexture, sf::Vector2f(700.f, 500.f));
        key = new Key(keyTexture, sf::Vector2f(600.f, 100.f));
        scoreboard = new Scoreboard();
    }

    ~Game()
    {
        delete player;
        delete enemy;
        delete sword;
        delete door;
        delete key;
        delete scoreboard;
    }

    void run()
    {
        while (window.isOpen())
        {
            handleEvents();
            update();
            render();
     
        }
    }

    void handleEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    void update()
    {
        player->update();

        if (enemy->alive)
        {
            enemy->updateMovement(player->getPosition());
            enemy->updateAnimation(4, 64, 64, animationClock, currentFrame);
        }
        else
        {
            enemy->checkRespawn();
        }

        if (player->hasSword)
        {
            sword->setPosition(player->getPosition() + player->swordOffset);

            float distanceToEnemy = std::sqrt(std::pow(player->getPosition().x - enemy->getPosition().x, 2) +
                                              std::pow(player->getPosition().y - enemy->getPosition().y, 2));
            if (distanceToEnemy < 50.f)
            {
                enemy->kill();
            }
        }

        if (!key->collected)
        {
            float distanceToKey = std::sqrt(std::pow(player->getPosition().x - key->getPosition().x, 2) +
                                            std::pow(player->getPosition().y - key->getPosition().y, 2));
            if (distanceToKey < 50.f)
            {
                player->hasKey = true;
                key->collected = true;
            }
        }

        if (player->hasKey)
        {
            float distanceToDoor = std::sqrt(std::pow(player->getPosition().x - door->getPosition().x, 2) +
                                             std::pow(player->getPosition().y - door->getPosition().y, 2));
            if (distanceToDoor < 50.f)
            {
                player->hasKey = false;
                key->respawn();
                scoreboard->addScore(10);
            }
        }

        bool spacePressedThisFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        if (spacePressedThisFrame && !spacePressedLastFrame)
        {
            if (!player->hasSword)
            {
                float distanceToSword = std::sqrt(std::pow(player->getPosition().x - sword->getPosition().x, 2) +
                                                  std::pow(player->getPosition().y - sword->getPosition().y, 2));
                if (distanceToSword < 50.f)
                {
                    player->hasSword = true;
                    sword->setPosition(player->getPosition() + player->swordOffset);
                }
            }
            else
            {
                player->hasSword = false;
                sword->setPosition(player->getPosition());
            }
        }
        spacePressedLastFrame = spacePressedThisFrame;

        scoreboard->updateText();
    }


    void render()
    {
    list<list<sf::Sprite>> mapa1;
    std::string line;
         // Nombre del archivo
    std::string filename = "./assets/salas/laberinto1.txt";

    // Crear un objeto ifstream
    std::ifstream inputFile(filename);

    // Verificar si el archivo se abrió correctamente
    if (!inputFile.is_open())
    {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
    }

    sf::Texture texturaBloques;
    if (!texturaBloques.loadFromFile("./assets/images/textura_salas.png"))
    {
       
    }

    int y = 0;
    while (std::getline(inputFile, line))
    {
        // std::cout << line << std::endl;
        list<sf::Sprite> temp;
        int x = 0;
        for (auto &&simbolo : line)
        {
            sf::Sprite bloque;
            if (simbolo == '0')
            {
                bloque = generarBloque(0, texturaBloques);
            }
            if (simbolo == '1')
            {
                bloque = generarBloque(1, texturaBloques);
            }
            if (simbolo == '2')
            {
                bloque = generarBloque(2, texturaBloques);
            }
            bloque.setPosition(sf::Vector2f(x * 32, y * 32));
            temp.emplace_back(bloque);
            x++;
        }
        mapa1.emplace_back(temp);
        y++;
    }

    // Cerrar el archivo
    inputFile.close();

    
        window.clear();
        for (auto &&linea : mapa1)
        {
            for (auto &&bloque : linea)
            {
                window.draw(bloque);
            }
        }
        window.draw(player->sprite);
        if (!player->hasSword)
        {
            window.draw(sword->sprite);
        }
        if (enemy->alive)
        {
            window.draw(enemy->sprite);
        }
        if (!key->collected)
        {
            window.draw(key->sprite);
        }
        window.draw(door->sprite);
        scoreboard->draw(window);
        window.display();
    }
};

int main()
{
    Game game;
    game.run();
    return 0;
}
