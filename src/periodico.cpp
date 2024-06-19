#include "../include/Periodico.hpp"

Periodico::Periodico()
{
    if (!_texture.loadFromFile("assets/images/periodico.png"))
    {
        // Manejar error de carga de la textura
    }
    _sprite.setTexture(_texture);
    _sprite.setScale(0.1f, 0.1f); // Ajustar la escala para que sea más pequeño
}

void Periodico::respawn(float posX, float posY)
{
    _sprite.setPosition(posX, posY);
}

void Periodico::update(float speed)
{
    _sprite.move(0, speed);
}

void Periodico::draw(sf::RenderTarget& target) const
{
    target.draw(_sprite);
}

sf::FloatRect Periodico::getBounds() const
{
    return _sprite.getGlobalBounds();
}

bool Periodico::isOutOfBounds(float windowHeight) const
{
    return _sprite.getPosition().y > windowHeight;
}
