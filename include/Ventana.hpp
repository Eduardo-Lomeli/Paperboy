#include <SFML/Graphics.hpp>
#include "Paperboy.hpp" 
void ventana()
{
//inicializacion de la ventana
    sf::RenderWindow window(sf::VideoMode(800,600),"El chico de los Papeles");
    window.setFramerateLimit(60);

    Paperboy paperboy(sf::Vector2f(400,300));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        paperboy.update();
        paperboy.animacion();
        window.clear(sf::Color::White);
        window.draw(paperboy);
        window.display(); 
    }
}