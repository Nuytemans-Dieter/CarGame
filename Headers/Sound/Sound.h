//
// Created by Dieter on 7/04/2019.
//

#ifndef UNTITLED_SOUND_H
#define UNTITLED_SOUND_H


class Sound {

public:
    enum music {
        track1,
        track2,
        track3,
        track4,
        track5,
        track6,
        track7,
        track8,
        track9,
        track10
    };

    enum sound
    {
        shoot,
        explosion,
        speedup,
        invincible
    };

    Sound();
    ~Sound();
    virtual void loadSound(sound) = 0;  //Load sound (.wav)
    virtual void loadMusic(music) = 0;  //Load music (.wav)
    virtual void playSound() = 0;       //Play the loaded sound
    virtual void playMusic() = 0;       //Play the loaded music
};


#endif //UNTITLED_SOUND_H
