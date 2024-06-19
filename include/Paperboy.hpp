#ifndef PAPERBOY_HPP
#define PAPERBOY_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime> // Para usar time()
#include "Periodico.hpp"

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

    Periodico _periodico; // Agregar la instancia de Periodico como miembro de Paperboy

    void spawnObstacles(); // Método para spawnear obstáculos al inicio
    void spawnPeriodico(); // Método para spawnear un periódico
    sf::Clock _periodicoClock; // Reloj para controlar el tiempo de aparición del periódico
    float _periodicoCooldown; // Tiempo de enfriamiento para el periódico
};

#endif // PAPERBOY_HPP