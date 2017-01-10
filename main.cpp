#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <list>

using namespace std;

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


/*list <note> notes;

void init() {
    notes
    note n1;
    n1.name = (char *) "C_7";
    n1.freq = 2093.005;

    notes

    note n2;
    n1.name = (char *) "C_#";
    n1.freq = 2217.461;


    0.153m
    D
    7
    2349.318
    0.145m
    D# / Eb
    7
    2489.016
    0.137m
    E
    7
    2637.021
    0.129m
    F
    7
    2793.826
    0.122m
    F# / Gb
    7
    2959.955
    0.115m
    G
    7
    3135.964
    0.109m
    G# / Ab
    7
    3322.438
    0.102m
    A
    7
    3520
    0.097m
    A# / Bb
    7
    3729.31
    0.091m
    B
    7
    3951.066
    0.086m

    C
    8
    418
}*/

int readFile(const char *file_name, uint32_t samp_rt = 8000) {
    FILE *infile = fopen(file_name, "rb");        // Open wave file in read mode

    int BUFSIZE = 512;                    // BUFSIZE can be changed according to the frame size required (eg:512)
    int count = 0;                        // For counting number of frames in wave file.
    short int buff16[BUFSIZE];                // short int used for 16 bit as input data format is 16 bit PCM audio
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
    const char *str = "/home/max/Projects/sound_learning/test.wav";
    readFile(str);
    return 0;
}