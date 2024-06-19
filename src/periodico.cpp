#include "../include/Periodico.hpp"

Periodico::Periodico()
{
    if (!_textura.loadFromFile("assets/images/periodico.png"))
    {
        // Manejar error de carga de la textura
    }
    _sprite.setTexture(_textura);
    _sprite.setScale(0.1f, 0.1f); // Ajustar la escala para que sea más pequeño
}

void Periodico::respawn(float posX, float posY)
{
    _sprite.setPosition(posX, posY);
}

void Periodico::update(float velocidadPeriodico)
{
    _sprite.move(0, velocidadPeriodico);
}

void Periodico::draw(sf::RenderTarget &target) const
{
    target.draw(_sprite);
}

sf::FloatRect Periodico::getBounds() const
{
    return _sprite.getGlobalBounds();
}

bool Periodico::isOutOfBounds(float altoVentana) const
{
    return _sprite.getPosition().y > altoVentana;
}
