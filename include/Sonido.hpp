#include <SFML/Audio.hpp>

class Sonido
{
private:
    sf::SoundBuffer _musicaFondo;
    sf::Sound _sonido; 
public:
    Sonido() {}
    ~Sonido() {}
    void cargarMusicaFondo();
};

void Sonido::cargarMusicaFondo()
{
    if (!_musicaFondo.loadFromFile("assets/music/MSCPAPER.ogg"))
    {
        
    }
    _sonido.setBuffer(_musicaFondo);
    _sonido.play();
}