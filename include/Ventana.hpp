#include <SFML/Graphics.hpp>
#include "Paperboy.hpp"
#include "Sonido.hpp"
#include "Juego.hpp"

void ventana()
{
    // inicializacion de la ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "El chico de los Papeles");
    window.setFramerateLimit(60);

    Paperboy paperboy(sf::Vector2f(400, 300));
    Sonido sonido;

    sf::Clock clock;

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Minecraft.ttf"))
    {
    }

    sonido.cargarMusicaFondo();

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (estado == Jugando)
        {
            window.clear(sf::Color::Red);
            paperboy.actualizarInvulnerabilidad(deltaTime);
            paperboy.update();
            paperboy.animacion();

            window.draw(paperboy);
            sf::Text textoVidas("Vidas: " + std::to_string(paperboy._vidas), font, 25);
            textoVidas.setFillColor(sf::Color::Black);
            textoVidas.setPosition(10, 10);
            window.draw(textoVidas);
            sf::Text textoPuntos("Puntos: " + std::to_string(paperboy._puntos), font, 25);
            textoPuntos.setFillColor(sf::Color::Black);
            textoPuntos.setPosition(120, 10);
            window.draw(textoPuntos);
        }
        else if (estado == GameOver)
        {
            // Mostrar pantalla de Game Over

            window.clear(sf::Color::Black);
            sf::Text gameOverText("Game Over", font, 50);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(400 - gameOverText.getGlobalBounds().width / 2, 300 - gameOverText.getGlobalBounds().height / 2);
            window.draw(gameOverText);
            sf::Text textoTecla("Presiona espacio para continuar", font, 25);
            textoTecla.setFillColor(sf::Color::Red);
            textoTecla.setPosition(400 - textoTecla.getGlobalBounds().width / 2, 400 - textoTecla.getGlobalBounds().height / 2);
            window.draw(textoTecla);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {

                estado = Jugando;
            }
        }
        window.display();
    }
}
