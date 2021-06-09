#ifndef HiScore_h
#define HiScore_h

#include "Map.h"
#include "Potter.h"

using namespace std;

class HiScore{
    private:
        char names[5][11];
        int scores[5];
        string file;
    public:
        HiScore(char *);
        // void operator<< (HiScore &, char, int);
};

#endif