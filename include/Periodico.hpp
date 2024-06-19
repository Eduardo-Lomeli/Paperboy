#ifndef PERIODICO_HPP
#define PERIODICO_HPP

#include <SFML/Graphics.hpp>

class Periodico
{
public:
    Periodico();

    void respawn(float posX, float posY);
    void update(float speed);
    void draw(sf::RenderTarget& target) const;
    sf::FloatRect getBounds() const;
    bool isOutOfBounds(float windowHeight) const;

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    const int windowWidth = 800;
    const int windowHeight = 600;
};

#endif // PERIODICO_HPP
