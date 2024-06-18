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
       
   }
   this->_sprite.setTexture(_texture);
   this->_sprite.scale(4,4);
   this->_sprite.setPosition(position);
   
}


void Paperboy::update()
{
    //movimiento Paperboy
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

    //Condiciones para que no se salga de la pantalla

    if (_sprite.getPosition().x < 0)
    {
        _sprite.setPosition(0, _sprite.getPosition().y);
    }
     if (_sprite.getPosition().y < 0)
    {
        _sprite.setPosition(_sprite.getPosition().x, 0);
    }
     if (_sprite.getPosition().x + _sprite.getGlobalBounds().width > 800)
    {
        _sprite.setPosition(800 - _sprite.getGlobalBounds().width, _sprite.getPosition().y);
    }
     if (_sprite.getPosition().y + _sprite.getGlobalBounds().height > 600)
    {
        _sprite.setPosition(_sprite.getPosition().x,600 - _sprite.getGlobalBounds().height);
    }

    }

    void Paperboy::animacion()
    {
        if(_clock.getElapsedTime().asSeconds() >= frametime)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            _sprite.setTextureRect(sf::IntRect((currentFrame * 26), 0, 26, 40));
            _clock.restart();
        } 
    }


     void Paperboy::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(_sprite, states);
    }

