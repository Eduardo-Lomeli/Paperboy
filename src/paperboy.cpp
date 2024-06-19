#include <SFML/Graphics.hpp>
#include "../include/Paperboy.hpp"

Paperboy::Paperboy(sf::Vector2f position)
    : _periodico()
{
    _velocidad = 4;
    frametime = 0.1f;
    currentFrame = 0;
    numFrames = 9;
    frameWidth = 26;
    frameHeight = 40;
    _obstacleSpeed = 2.0f;

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

    // Cargar texturas de obstáculos (ejemplo con dos texturas)
    sf::Texture obstacleTexture1;
    if (!obstacleTexture1.loadFromFile("assets/images/obstacle1.png"))
    {
        // Manejar error de carga
    }
    _obstacleTextures.push_back(obstacleTexture1);

    sf::Texture obstacleTexture2;
    if (!obstacleTexture2.loadFromFile("assets/images/obstacle2.png"))
    {
        // Manejar error de carga
    }
    _obstacleTextures.push_back(obstacleTexture2);

    // Crear sprites para los obstáculos y ajustar la escala
    for (const auto& texture : _obstacleTextures)
    {
        sf::Sprite obstacleSprite;
        obstacleSprite.setTexture(texture);
        obstacleSprite.setScale(0.1f, 0.1f); // Ajustar la escala para que sea más pequeño
        obstacleSprite.setPosition(static_cast<float>(rand() % (550 - 210 + 1) + 210), static_cast<float>(rand() % windowHeight));
        _obstacleSprites.push_back(obstacleSprite);
    }

    // Inicializar el reloj del periódico y el tiempo de enfriamiento
    _periodicoCooldown = 5.0f; // 5 segundos de enfriamiento inicial
    _periodicoClock.restart();

    // Spawnear obstáculos al inicio
    spawnObstacles();

    // Spawnear un periódico al inicio
    spawnPeriodico();
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

    // Movimiento de los obstáculos
    for (auto& obstacleSprite : _obstacleSprites)
    {
        obstacleSprite.move(0, _obstacleSpeed);

        // Reaparecer el obstáculo cuando salga de la pantalla
        if (obstacleSprite.getPosition().y >= windowHeight)
        {
            obstacleSprite.setPosition(static_cast<float>(rand() % (550 - 210 + 1) + 210), 0);
        }
    }

    // Actualizar el tiempo de aparición del periódico
    float elapsedTime = _periodicoClock.getElapsedTime().asSeconds();
    if (elapsedTime >= _periodicoCooldown)
    {
        _periodico.update(_obstacleSpeed);

        // Si el periódico se sale de la pantalla, reubicarlo aleatoriamente y reiniciar el tiempo de aparición
        if (_periodico.isOutOfBounds(windowHeight))
        {
            _periodico.respawn(static_cast<float>(rand() % (550 - 210 + 1) + 210), 0);
            _periodicoClock.restart();
            _periodicoCooldown = 5.0f; // Reiniciar el tiempo de enfriamiento del periódico
        }
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

    // Dibujar los obstáculos
    for (const auto& obstacleSprite : _obstacleSprites)
    {
        target.draw(obstacleSprite, states);
    }

    // Dibujar el periódico
    _periodico.draw(target);
}

void Paperboy::spawnObstacles()
{
    // Spawnear obstáculos en posiciones aleatorias dentro del área jugable
    _obstacleSprites.clear(); // Limpiar los obstáculos existentes

    for (const auto& texture : _obstacleTextures)
    {
        sf::Sprite obstacleSprite;
        obstacleSprite.setTexture(texture);
        obstacleSprite.setScale(0.1f, 0.1f); // Ajustar la escala para que sea más pequeño
        obstacleSprite.setPosition(static_cast<float>(rand() % (550 - 210 + 1) + 210), static_cast<float>(rand() % windowHeight));
        _obstacleSprites.push_back(obstacleSprite);
    }
}

void Paperboy::spawnPeriodico()
{
    // Spawnear el periódico en una posición aleatoria al inicio
    _periodico.respawn(static_cast<float>(rand() % (550 - 210 + 1) + 210), static_cast<float>(rand() % windowHeight));
    _periodicoClock.restart();
    _periodicoCooldown = 5.0f; // Ajustar el tiempo de aparición del periódico
}
