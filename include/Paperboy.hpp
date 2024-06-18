#pragma once
#include<SFML/Graphics.hpp>

class Paperboy: public sf::Drawable
{
private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Clock _clock;
    float _velocidad;
    float frametime ;
    int currentFrame;
    int numFrames;
    int frameWidth;
    int frameHeight;
public:
    Paperboy(sf::Vector2f position);
    void update();
    void animacion();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};