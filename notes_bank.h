
#ifndef SOUND_LEARNING_NOTES_BANK_H
#define SOUND_LEARNING_NOTES_BANK_H

#endif //SOUND_LEARNING_NOTES_BANK_H

#include <list>
#include <vector>

using namespace std;


class Note_bank {
public:
    struct note {
        char *name;
        vector<double> freq;

        bool operator<(const note &rhs) const { return name < rhs.name; }
    };

    void init_notes();

    vector<note> notes;

};

