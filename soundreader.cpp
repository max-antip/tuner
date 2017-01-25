#include <AL/alc.h>
#include <cstdio>
#include <iostream>
#include <list>
#include <algorithm>
#include "notes_bank.h"
#include "soundreader.h"

using namespace std;

struct note_score {
    char *name;
    int score;

    bool operator==(const note_score &nt1) {
        return nt1.name == name;
    }

    bool operator<(const note_score &ns) const { return score < ns.score; }
};


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

    vector<note_score> bucket;

    int kuant = 70;
    int m = 0;
    while (true) {
        alcGetIntegerv(device, ALC_CAPTURE_SAMPLES, (ALCsizei) sizeof(ALint), &sample);
        alcCaptureSamples(device, (ALCvoid *) buffer, sample);
        m++;

        for (int i = 0; i < SSIZE; i++) {

            ALuint frequency;
            frequency = buffer[i + 3] << 24;
            frequency |= buffer[i + 2] < 16;
            frequency |= buffer[i + 1] < 8;
            frequency |= buffer[i];;

            if (frequency <= max_freq) {

//            float fr = SRATE / (float) buffer[i];
                for (vector<Note_bank::note>::iterator it = notesBank.notes.begin();
                     it != notesBank.notes.end(); ++it) {

                    for (std::vector<double>::iterator vit = it->freq.begin(); vit != it->freq.end(); ++vit) {


                        if (frequency + 10 >= *vit && frequency - 10 <= *vit) {
//                        cout << it->name << endl;

                            note_score nt = note_score{it->name, 1};
                            if (bucket.size() > 0) {
                                vector<note_score>::iterator f = find(bucket.begin(), bucket.end(), nt);
                                if (f->name == NULL) {
                                    bucket.push_back(nt);
                                } else {
                                    f->score += 1;
                                }
                            } else {
                                bucket.push_back(nt);

                            }
                        }
                    }

                }


                if (m % kuant == 0) {
                    sort(bucket.begin(), bucket.end());
                    cout << bucket.back().name << endl;
                    bucket.clear();
                    m = 0;
                }
            }
        }

    }
#pragma clang diagnostic pop

}


