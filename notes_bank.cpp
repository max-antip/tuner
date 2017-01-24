#include <list>
#include "notes_bank.h"

using namespace std;


void Note_bank::init_notes() {
    vector<double> C_freqs = {16.35, 32.70, 65.41, 130.8, 261.6, 523.3, 1047, 2093, 4186};
    vector<double> C_sharp_freqs = {17.32, 34.65, 69.30, 138.6, 277.2, 554.4, 1109, 2217, 4435};
    vector<double> D_freqs = {18.35, 36.71, 73.42, 146.8, 293.7, 587.3, 1175, 2349, 4699};
    vector<double> Eb_freqs = {19.45, 38.89, 77.78, 155.6, 311.1, 622.3, 1245, 2489, 4978};
    vector<double> E_freqs = {20.60, 41.20, 82.41, 164.8, 329.6, 659.3, 1319, 2637, 5274};
    vector<double> F_freqs = {21.83, 43.65, 87.31, 174.6, 349.2, 698.5, 1397, 2794, 5588};
    vector<double> F_sharp_freqs = {23.12, 46.25, 92.50, 185.0, 370.0, 740.0, 1480, 2960, 5920};
    vector<double> G_freqs = {24.50, 49.00, 98.00, 196.0, 392.0, 784.0, 1568, 3136, 6272};
    vector<double> G_sharp_freqs = {25.96, 51.91, 103.8, 207.7, 415.3, 830.6, 1661, 3322, 6645};
    vector<double> A_freqs = {27.50, 55.00, 110.0, 220.0, 440.0, 880.0, 1760, 3520, 7040};
    vector<double> Bb_freqs = {29.14, 58.27, 116.5, 233.1, 466.2, 932.3, 1865, 3729, 7459};
    vector<double> B_freqs = {30.87, 61.74, 123.5, 246.9, 493.9, 987.8, 1976, 3951, 7902};

    note c;
    c.freq = C_freqs;
    c.name = (char *) "C";
    notes.push_back(c);

    note c_sh;
    c_sh.freq = C_sharp_freqs;
    c_sh.name = (char *) "C#";
    notes.push_back(c_sh);

    note d;
    d.freq = D_freqs;
    d.name = (char *) "D";
    notes.push_back(d);

    note eb;
    eb.freq = Eb_freqs;
    eb.name = (char *) "Eb";
    notes.push_back(eb);

    note e;
    e.freq = E_freqs;
    e.name = (char *) "E";
    notes.push_back(e);

    note f;
    f.freq = F_freqs;
    f.name = (char *) "F";
    notes.push_back(f);

    note f_sh;
    f_sh.freq = F_sharp_freqs;
    f_sh.name = (char *) "F#";
    notes.push_back(f_sh);

    note g;
    g.freq = G_freqs;
    g.name = (char *) "G";
    notes.push_back(g);

    note g_sh;
    g_sh.freq = G_sharp_freqs;
    g_sh.name = (char *) "G#";
    notes.push_back(g_sh);

    note a;
    a.freq = A_freqs;
    a.name = (char *) "A";
    notes.push_back(a);

    note bb;
    bb.freq = Bb_freqs;
    bb.name = (char *) "Bb";
    notes.push_back(bb);

    note b;
    b.freq = B_freqs;
    b.name = (char *) "B";
    notes.push_back(b);
}


