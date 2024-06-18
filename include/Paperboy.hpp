#ifndef PAPERBOY_HPP
#define PAPERBOY_HPP

#include <SFML/Graphics.hpp>

class Paperboy : public sf::Drawable
{
public:
    Paperboy(sf::Vector2f position);

    void update();
    void animacion();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Texture _backgroundTexture;
    sf::Sprite _backgroundSprite;
    sf::Sprite _backgroundSprite2;

    int _velocidad;
    float frametime;
    int currentFrame;
    int numFrames;
    int frameWidth;
    int frameHeight;
    sf::Clock _clock;

    const int windowWidth = 800;
    const int windowHeight = 600;
};

#endif // PAPERBOY_HPP
