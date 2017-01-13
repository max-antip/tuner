#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <list>
#include <AL/al.h>
#include <AL/alc.h>

using namespace std;

const int SRATE = 44100;
const int SSIZE = 1024;

ALbyte buffer[22050];
ALint sample;

// WAVE PCM soundfile format (you can find more in https://ccrma.stanford.edu/courses/422/projects/WaveFormat/ )
typedef struct header_file {
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;            // sample_rate denotes the sampling rate.
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;            // subchunk2_size denotes the number of samples.
} header;

typedef struct header_file *header_p;

struct note {
    char *name;
    double freq;
};


list <note> notes;

void init() {
    note n1;
    n1.name = (char *) "C";
    n1.freq = 2093.005;

    note n2;
    n2.name = (char *) "C_#";
    n2.freq = 2217.461;

    note n3;
    n3.name = (char *) "D";
    n3.freq = 2349.318;


    note n4;
    n4.name = (char *) "D_#";
    n4.freq = 2489.01;

    note n5;
    n5.name = (char *) "E";
    n5.freq = 2637.021;


    note n6;
    n6.name = (char *) "F";
    n6.freq = 2793.826;


    note n7;
    n7.name = (char *) "F_#";
    n7.freq = 2959.955;


    note n8;
    n8.name = (char *) "G";
    n8.freq = 3135.964;

    note n9;
    n9.name = (char *) "G_#";
    n9.freq = 3322.438;

    note n10;
    n10.name = (char *) "A";
    n10.freq = 3520;


    note n11;
    n11.name = (char *) "A_#";
    n11.freq = 3729.31;


    note n12;
    n12.name = (char *) "B";
    n12.freq = 3951.066;

    notes.push_back(n1);
    notes.push_back(n2);
    notes.push_back(n3);
    notes.push_back(n4);
    notes.push_back(n5);
    notes.push_back(n6);
    notes.push_back(n7);
    notes.push_back(n8);
    notes.push_back(n9);
    notes.push_back(n10);
    notes.push_back(n11);
    notes.push_back(n12);
}

int min_gap = 100;

int readFile(const char *file_name, uint32_t samp_rt = 8000) {
    FILE *infile = fopen(file_name, "rb");        // Open wave file in read mode

    int BUFSIZE = 512;                    // BUFSIZE can be changed according to the frame size required (eg:512)
    int count = 0;                        // For counting number of frames in wave file.
    float buff16[BUFSIZE];                // short int used for 16 bit as input data format is 16 bit PCM audio
    header_p meta = (header_p) malloc(
            sizeof(header));    // header_p points to a header struct that contains the wave file metadata fields
    int nb;                            // variable storing number of byes returned
    if (infile) {
        fread(meta, 1, sizeof(header), infile);
        cout << " Size of Header file is " << sizeof(*meta) << " bytes" << endl;
        cout << " Sampling rate of the input wave file is " << meta->sample_rate << " Hz" << endl;
        cout << " Number of samples in wave file are " << meta->subchunk2_size << " samples" << endl;
        cout << " Chunk size " << meta->chunk_size << endl;

        short int totalBuff[meta->chunk_size];

        while (!feof(infile)) {
            nb = fread(totalBuff, 1, meta->chunk_size, infile);        // Reading data in chunks of BUFSIZE
        }

        for (int k = 0; k < meta->chunk_size; k++) {
            for (list<note>::iterator it = notes.begin(); it != notes.end(); ++it) {
                if (abs(totalBuff[k]) + min_gap >= it->freq && abs(totalBuff[k]) - min_gap <= it->freq) {
                    cout << it->name << endl;
                }
            }
        }

        static const pa_sample_spec ss = {
                .format = PA_SAMPLE_U8,
                .rate =  samp_rt,
                .channels = 1
        };

        pa_simple *s = NULL;
        int error;
        const char *name = "synth";
        if (!(s = pa_simple_new(NULL, name, PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error))) {
            fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
            return 1;
        }
        if (pa_simple_write(s, totalBuff, (size_t) nb, &error)) {
            fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
            return 3;
        }


        if (pa_simple_drain(s, &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_drain() failed: %s\n", pa_strerror(error));
            return 4;
        }

        cout << " Number of frames in the input wave file are " << count << endl;
    }
    return 0;
}

int main() {
    ALCdevice *device = alcOpenDevice(NULL);
    if (!device)
        fprintf(stderr, "Cant  creat audio device");
    const char *str = "/home/max/Projects/sound_learning/test.wav";
    init();
    readFile(str);
    return 0;
}