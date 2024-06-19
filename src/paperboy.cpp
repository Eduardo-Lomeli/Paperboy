#include <SFML/Graphics.hpp>
#include "../include/Paperboy.hpp"
#include "Juego.hpp"

Paperboy::Paperboy(sf::Vector2f position)
    : _periodico()
{
    _velocidad = 4;
    frametime = 0.1f;
    currentFrame = 0;
    numFrames = 9;
    frameWidth = 26;
    frameHeight = 40;
    _velocidadObstaculo = 2.0f;

    if (!_textura.loadFromFile("assets/images/paperboy.png"))
    {
        
    }
    this->_sprite.setTexture(_textura);
    this->_sprite.scale(4, 4);
    this->_sprite.setPosition(position);

    if (!_backgroundTexture.loadFromFile("assets/images/background.png"))
    {
        
    }
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite2.setTexture(_backgroundTexture);

    // Ajustar el tamaño del fondo para que coincida con la ventana
    float scaleX = static_cast<float>(anchoVentana) / _backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(altoVentana) / _backgroundTexture.getSize().y;
    
    _backgroundSprite.setScale(scaleX, scaleY);
    _backgroundSprite2.setScale(scaleX, scaleY);

    _backgroundSprite.setPosition(0, 0);
    _backgroundSprite2.setPosition(0, -altoVentana);

    // Cargar texturas de obstáculos
    sf::Texture obstacleTexture1;
    if (!obstacleTexture1.loadFromFile("assets/images/obstacle1.png"))
    {
        
    }
    _obstacleTextures.push_back(obstacleTexture1);

    sf::Texture obstacleTexture2;
    if (!obstacleTexture2.loadFromFile("assets/images/obstacle2.png"))
    {
        
    }
    _obstacleTextures.push_back(obstacleTexture2);

    
    for (const auto& texture : _obstacleTextures)
    {
        sf::Sprite obstacleSprite;
        obstacleSprite.setTexture(texture);
        obstacleSprite.setScale(0.1f, 0.1f); // Ajustar la escala para que sea más pequeño
        obstacleSprite.setPosition(static_cast<float>(rand() % (550 - 210 + 1) + 210), static_cast<float>(rand() % altoVentana));
        _obstacleSprites.push_back(obstacleSprite);
    }

    // Inicializar el reloj del periódico y el tiempo de enfriamiento
    _periodicoCooldown = 3.0f; 
    _periodicoClock.restart();

    spawnearObstaculos();

    spawnearPeriodico();

    //Inicializar vidas
    _vidas = _vidasIniciales;
    _puntos = _puntosIniciales;
    _tiempoInvulnerabilidad;
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
    if (_sprite.getPosition().y + _sprite.getGlobalBounds().height > altoVentana)
    {
        _sprite.setPosition(_sprite.getPosition().x, altoVentana - _sprite.getGlobalBounds().height);
    }

    // Movimiento del fondo
    float backgroundvelocidadPeriodico = 2.0f; // Velocidad del fondo
    _backgroundSprite.move(0, backgroundvelocidadPeriodico);
    _backgroundSprite2.move(0, backgroundvelocidadPeriodico);

    // Reaparecer el fondo cuando salga de la pantalla
    if (_backgroundSprite.getPosition().y >= altoVentana)
    {
        _backgroundSprite.setPosition(0, -altoVentana);
    }
    if (_backgroundSprite2.getPosition().y >= altoVentana)
    {
        _backgroundSprite2.setPosition(0, -altoVentana);
    }

    // Movimiento de los obstáculos
    for (auto& obstacleSprite : _obstacleSprites)
    {
        obstacleSprite.move(0, _velocidadObstaculo);

        // Reaparecer el obstáculo cuando salga de la pantalla
        if (obstacleSprite.getPosition().y >= altoVentana)
        {
            obstacleSprite.setPosition(static_cast<float>(rand() % (550 - 210 + 1) + 210), 0);
        }
    }

    // Actualizar el tiempo de aparición del periódico
    float elapsedTime = _periodicoClock.getElapsedTime().asSeconds();
    if (elapsedTime >= _periodicoCooldown)
    {
        _periodico.update(_velocidadObstaculo);

        // Si el periódico se sale de la pantalla, reubicarlo aleatoriamente
        if (_periodico.isOutOfBounds(altoVentana))
        {
            _periodico.respawn(static_cast<float>(rand() % (550 - 210 + 1) + 210), 0);
            _periodicoClock.restart();
            _periodicoCooldown = 3.0f; // Reiniciar el tiempo de enfriamiento del periódico
        }
    }
        verificarColisiones();
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

    // Dibujar los obstáculos
    for (const auto& obstacleSprite : _obstacleSprites)
    {
        target.draw(obstacleSprite, states);
    }

    // Dibujar el periódico
    _periodico.draw(target);
}

void Paperboy::spawnearObstaculos()
{
    // Spawnear obstáculos en posiciones aleatorias dentro del área jugable
    _obstacleSprites.clear(); // Limpiar los obstáculos existentes

    for (const auto& texture : _obstacleTextures)
    {
        sf::Sprite obstacleSprite;
        obstacleSprite.setTexture(texture);
        obstacleSprite.setScale(0.1f, 0.1f); // Ajustar la escala para que sea más pequeño
        obstacleSprite.setPosition(static_cast<float>(rand() % (550 - 210 + 1) + 210), static_cast<float>(rand() % altoVentana));
        _obstacleSprites.push_back(obstacleSprite);
    }
}

void Paperboy::spawnearPeriodico()
{
    // Spawnear el periódico en una posición aleatoria al inicio
    _periodico.respawn(static_cast<float>(rand() % (550 - 210 + 1) + 210), static_cast<float>(rand() % altoVentana));
    _periodicoClock.restart();
    _periodicoCooldown = 3.0f; // Ajustar el tiempo de aparición del periódico
}


void Paperboy::verificarColisiones()
{
    // Obtener el rectángulo de colisión del jugador
    if (_invulnerable) return;
    

    sf::FloatRect playerBounds = _sprite.getGlobalBounds();

    // Verificar colisiones con los obstáculos
    for (auto& obstacleSprite : _obstacleSprites)
    {
        sf::FloatRect obstacleBounds = obstacleSprite.getGlobalBounds();

        if (playerBounds.intersects(obstacleBounds))
        {
            // Colisión detectada, restar una vida y reubicar al jugador
            _vidas -= 1;
            _sprite.setPosition(400, 300);
            _invulnerable = true;
            _tiempoInvulnerabilidad = 1.5f;
            // Si el jugador se queda sin vidas cambia el estado del Juego y reincia los contadores
            if (_vidas <= 0)
            {
                estado = GameOver;
                _vidas = _vidasIniciales;
                _puntos = _puntosIniciales;
            }
                
        }
    }

    // Verificar colisión con el periódico
    sf::FloatRect periodicoBounds = _periodico.getBounds();

    if (playerBounds.intersects(periodicoBounds))
    {
        // Colisión con el periódico, incrementar la velocidad de los obstáculos
        _puntos += 10;
        _velocidadObstaculo += 0.5f;
        _periodico.respawn(static_cast<float>(rand() % (550 - 210 + 1) + 210), 0); // Reubicar el periódico
        _periodicoClock.restart(); // Reiniciar el reloj del periódico

    }
}
void Paperboy::actualizarInvulnerabilidad(float deltaTime)  //Funcion para actualizar el tiempo de invulnerabilidad
{
    if (_invulnerable)
    {
        _tiempoInvulnerabilidad -= deltaTime;
        if (_tiempoInvulnerabilidad <= 0)
        {
            _invulnerable = false;
            _tiempoInvulnerabilidad = 0.0f;
        }
    }
}