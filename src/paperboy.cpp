#include <SFML/Graphics.hpp>
#include "../include/Paperboy.hpp"

Paperboy::Paperboy(sf::Vector2f position)
{
    _velocidad = 4;
    frametime = 0.1f;
    currentFrame = 0;
    numFrames = 9;
    frameWidth = 26;
    frameHeight = 40;

    if (!_texture.loadFromFile("assets/images/paperboy.png"))
    {
        // Manejar error de carga
    }
    this->_sprite.setTexture(_texture);
    this->_sprite.scale(4, 4);
    this->_sprite.setPosition(position);

    if (!_backgroundTexture.loadFromFile("assets/images/background.png"))
    {
        // Manejar error de carga
    }
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite2.setTexture(_backgroundTexture);

    // Ajustar el tamaño del fondo para que coincida con la ventana
    float scaleX = static_cast<float>(windowWidth) / _backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(windowHeight) / _backgroundTexture.getSize().y;
    
    _backgroundSprite.setScale(scaleX, scaleY);
    _backgroundSprite2.setScale(scaleX, scaleY);

    _backgroundSprite.setPosition(0, 0);
    _backgroundSprite2.setPosition(0, -windowHeight);
}

void Paperboy::update()
{
    // Movimiento Paperboy
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        _sprite.move(0, -_velocidad);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        _sprite.move(-_velocidad, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        _sprite.move(0, _velocidad);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        _sprite.move(_velocidad, 0);
    }

    // Condiciones para que no se salga de la pantalla
    if (_sprite.getPosition().x < 190)
    {
        _sprite.setPosition(190, _sprite.getPosition().y);
    }
    if (_sprite.getPosition().y < 0)
    {
        _sprite.setPosition(_sprite.getPosition().x, 0);
    }
    if (_sprite.getPosition().x + _sprite.getGlobalBounds().width > 600)
    {
        _sprite.setPosition(600 - _sprite.getGlobalBounds().width, _sprite.getPosition().y);
    }
    if (_sprite.getPosition().y + _sprite.getGlobalBounds().height > windowHeight)
    {
        _sprite.setPosition(_sprite.getPosition().x, windowHeight - _sprite.getGlobalBounds().height);
    }

    // Movimiento del fondo
    float backgroundSpeed = 2.0f; // Velocidad del fondo
    _backgroundSprite.move(0, backgroundSpeed);
    _backgroundSprite2.move(0, backgroundSpeed);

    // Reaparecer el fondo cuando salga de la pantalla
    if (_backgroundSprite.getPosition().y >= windowHeight)
    {
        _backgroundSprite.setPosition(0, -windowHeight);
    }
    if (_backgroundSprite2.getPosition().y >= windowHeight)
    {
        _backgroundSprite2.setPosition(0, -windowHeight);
    }
}

void Paperboy::animacion()
{
    if (_clock.getElapsedTime().asSeconds() >= frametime)
    {
        currentFrame = (currentFrame + 1) % numFrames;
        _sprite.setTextureRect(sf::IntRect((currentFrame * frameWidth), 0, frameWidth, frameHeight));
        _clock.restart();
    }
}

void Paperboy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_backgroundSprite, states);
    target.draw(_backgroundSprite2, states);
    target.draw(_sprite, states);
}
