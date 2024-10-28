#include "AudioManager.h"
#include <iostream>
#include <string>

    AudioManager::AudioManager() {

        for (int i = 0; i < 10; i++) {
            sf::SoundBuffer b;
            buffers.push_back(b);
        }
        for (int i = 0; i < 3; i++) {
            sf::Sound so;
            tileSound.push_back(so);
        }

        musicPlay = false;
        soundPlay = true;

        loadMusicSound();

        // настройки
        //botumeSound.setVolume(50);
        //backgroundMusic.setVolume(50);
        //backgroundMusic.setLoop(true);

    }

    void AudioManager::playSound(Sounds sou) {

        if(soundPlay){
            int num = 0;
            switch (sou)
            {
            case tileS:
                num = get_random_int(0, tileSound.size() - 1);
                tileSound[num].play();
                break;
            case buttonS:
                buttonSound.play();
                break;
            case boomS:
                bombBoomSound.play();
                break;
            case flagS:
                flagSound.play();
                break;
            case victoriS:
                victoriSound.play();
                break;
            case extraBoomS:
                extraBoomSound.play();
                break;
            default:
                break;
            }
        }
       
    }
    void AudioManager::playMusic() {
        
        if (!musicPlay){
            backgroundMusic.play();
            musicPlay = true;
        }
        else {
            backgroundMusic.pause();
            musicPlay = false;
        }
                
        
    }
    void AudioManager::OnOffMusic() {

        if (musicPlay) {
            backgroundMusic.pause();
            musicPlay = false;
        }
        else {
            backgroundMusic.play();
            musicPlay = true;
        }
    }
    void AudioManager::OnOffSound() {

        if (soundPlay) {
            soundPlay = false;
        }
        else {
            soundPlay = true;
        }
    }

    bool AudioManager::isMusicOn() {
        return musicPlay;
    }
    bool AudioManager::isSoundOn() {
        return soundPlay;
    }

    void AudioManager::setMusicVolume(int vol) {
        if (vol > 100)
            vol = 100;
        if (vol < 0)
            vol = 0;
       
            backgroundMusic.setVolume(vol);
        
        
    }
    void AudioManager::setSoundVolume(int vol) {
        if (vol > 100)
            vol = 100;
        if (vol < 0)
            vol = 0;

        bombBoomSound.setVolume(vol);
        for (auto so : tileSound) {
            so.setVolume(vol);
        }
        buttonSound.setVolume(vol);
        bombBoomSound.setVolume(vol);
        flagSound.setVolume(vol);
        victoriSound.setVolume(vol);
        extraBoomSound.setVolume(vol);


    }
    void AudioManager::loadMusicSound() {

        if (!backgroundMusic.openFromFile("resources/audio/devilThem.mp3")) {
            std::cout << "music errror" << std::endl;
        }

        int j = 0;
        for (int i = 0; i < 3; i++,j++) {

            if (!buffers[j].loadFromFile("resources/audio/tileSound("+std::to_string(i+1)+").ogg")) {
                std::cerr << "sound error" << std::endl;
            }
            tileSound[i].setBuffer(buffers[j]);
        }

        
        if (!buffers[j].loadFromFile("resources/audio/bombBoom.ogg")) {
            std::cerr << "sound error" << std::endl;
        }
        bombBoomSound.setBuffer(buffers[j]);

        j++;
        if (!buffers[j].loadFromFile("resources/audio/flag.ogg")) {
            std::cerr << "sound error" << std::endl;
        }
        flagSound.setBuffer(buffers[j]);

        j++;
        if (!buffers[j].loadFromFile("resources/audio/victori.ogg")) {
            std::cerr << "sound error" << std::endl;
        }
        victoriSound.setBuffer(buffers[j]);

        j++;
        if (!buffers[j].loadFromFile("resources/audio/buttone.ogg")) {
            std::cerr << "sound error" << std::endl;
        }
        buttonSound.setBuffer(buffers[j]);

        j++;
        if (!buffers[j].loadFromFile("resources/audio/extraBoom.ogg")) {
            std::cerr << "sound error" << std::endl;
        }
        extraBoomSound.setBuffer(buffers[j]);

        
        
    }
    
 

