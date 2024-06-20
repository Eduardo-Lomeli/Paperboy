#include <SFML/Audio.hpp> //Libreria de audio de SFML

class Sonido
{
private:
    sf::SoundBuffer _musicaFondo;
    sf::Sound _sonido;

public:
    Sonido() {}
    ~Sonido() {}
    void CargarMusicaFondo();
};

void Sonido::CargarMusicaFondo()
{
    if (!_musicaFondo.loadFromFile("assets/music/MSCPAPER.ogg"))
    {
    }
    _sonido.setBuffer(_musicaFondo);
    _sonido.play();
}