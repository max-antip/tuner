#include <iostream>
#include <pulse/simple.h>
#include <pulse/error.h>
#include "notes_bank.h"
#include <AL/al.h>
#include "soundreader.h"


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


int readFile(const char *file_name, uint32_t samp_rt = 8000) {
    Note_bank notesBank;
    notesBank.init_notes();
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

            for (vector<Note_bank::note>::iterator it = notesBank.notes.begin();
                 it < notesBank.notes.end(); ++it) {
                for (std::vector<double>::iterator vit = it->freq.begin(); vit < it->freq.end(); ++vit) {
                    if (abs(totalBuff[k]) + 20 >= 44100 / *vit && abs(totalBuff[k]) - 20 <= 44100 / *vit) {
                        cout << it->name << endl;
                    }
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
    ALbyte buffer[22050];
    soundreader sr;
    sr.read_from_mic(buffer);

//    const char *str = "/home/max/Projects/sound_learning/test.wav";
//    readFile(str);
    return 0;
}