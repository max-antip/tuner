#include <AL/alc.h>
#include <cstdio>
#include <iostream>
#include <list>
#include "notes_bank.h"
#include "soundreader.h"

using namespace std;


void soundreader::read_from_mic(ALbyte buffer[]) {
    Note_bank notesBank;
    notesBank.init_notes();
    ALCdevice *device = alcCaptureOpenDevice(NULL, SRATE, AL_FORMAT_MONO16, SSIZE);
    /* if (alGetError() != AL_NO_ERROR) {
         cout << alGetError() << endl;
         return 0;
     }*/
    alcCaptureStart(device);


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

    while (true) {
        alcGetIntegerv(device, ALC_CAPTURE_SAMPLES, (ALCsizei) sizeof(ALint), &sample);
        alcCaptureSamples(device, (ALCvoid *) buffer, sample);

        for (int i = 0; i < SSIZE; i++) {


            float fr = SRATE / (float) buffer[i];
            for (vector<Note_bank::note>::iterator it = notesBank.notes.begin();
                 it != notesBank.notes.end(); ++it) {

                for (std::vector<double>::iterator vit = it->freq.begin(); vit != it->freq.end(); ++vit) {
                    if (fr + 20 >= SRATE / *vit && fr - 20 <= SRATE / *vit) {
                        cout << it->name << endl;
                    }
                }

            }

        }
    }
#pragma clang diagnostic pop

}
