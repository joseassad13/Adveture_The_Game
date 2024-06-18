class Door : public GameObject
{
public:
    Door(const sf::Texture &texture, const sf::Vector2f &position)
        : GameObject(texture, position) {}
};