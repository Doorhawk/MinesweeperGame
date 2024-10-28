#pragma once
#include "random.h"
#include <SFML/Audio.hpp>

enum Sounds {tileS, buttonS,boomS, flagS,victoriS, extraBoomS};

class AudioManager :Random {
public:
    AudioManager();

    void playSound(Sounds);
    void playMusic();
    void OnOffMusic();
    void OnOffSound();

    bool isMusicOn();
    bool isSoundOn();

    void setMusicVolume(int vol);
    void setSoundVolume(int vol);


private:
    void loadMusicSound();

    bool musicPlay;
    bool soundPlay;

    sf::Music backgroundMusic;
    std::vector<sf::SoundBuffer> buffers;
    std::vector< sf::Sound> tileSound;
    sf::Sound bombBoomSound;
    sf::Sound flagSound;
    sf::Sound victoriSound;
    sf::Sound buttonSound;
    sf::Sound extraBoomSound;
};