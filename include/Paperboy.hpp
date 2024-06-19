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
    int _vidas;
    const int _vidasIniciales = 3;
    int _puntos;
    const int _puntosIniciales = 0;
    void update();
    void animacion();
    void verificarColisiones();
    void actualizarInvulnerabilidad(float dt);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture _textura;
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

    
    bool _invulnerable = false;
    float _tiempoInvulnerabilidad = 0.0f; 

    const int anchoVentana = 800;
    const int altoVentana = 600;

    float _velocidadObstaculo;

    Periodico _periodico; // Agregar la instancia de Periodico como miembro de Paperboy

    void spawnearObstaculos(); 
    void spawnearPeriodico(); 
    sf::Clock _periodicoClock; 
    float _periodicoCooldown; 
};

#endif // PAPERBOY_HPP