//
// Created by max on 1/16/17.
//

#ifndef SOUND_LEARNING_SOUNDREADER_H
#define SOUND_LEARNING_SOUNDREADER_H


#include <AL/al.h>
#include <cstdint>


class soundreader {

private:
    const int SRATE = 44100;
    const int SSIZE = 1024;
    const float min_freq= 20;
    const float max_freq= 20000;

    ALint sample;

public:

    void read_from_mic(ALbyte buffer [] );

    void read_from_file(const char *file_name, uint32_t samp_rt = 8000);
};


#endif //SOUND_LEARNING_SOUNDREADER_H
