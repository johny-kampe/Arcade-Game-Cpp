#ifndef HiScore_h
#define HiScore_h

#include "Potter.h"
#include "Engine.h"
#include "Map.h"

using namespace std;

class HiScore{
    private:
        char names[5][10];
        int scores[5];
        string file;
    public:
        HiScore(char *);
        void operator<<(Engine &);
};

#endif