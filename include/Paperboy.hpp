#ifndef PAPERBOY_HPP
#define PAPERBOY_HPP

#include <SFML/Graphics.hpp>
#include <vector>

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

    std::vector<sf::Texture> _obstacleTextures;
    std::vector<sf::Sprite> _obstacleSprites;

    std::vector<sf::Time> _obstacleTimers;
    std::vector<sf::Clock> _obstacleClocks;

    int _velocidad;
    float frametime;
    int currentFrame;
    int numFrames;
    int frameWidth;
    int frameHeight;
    sf::Clock _clock;

    const int windowWidth = 800;
    const int windowHeight = 600;

    float _obstacleSpeed;
};
#endif // PAPERBOY_HPP