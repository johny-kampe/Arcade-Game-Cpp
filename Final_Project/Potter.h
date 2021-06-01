#ifndef Potter_h
#define Potter_h

#include "Moving.h"

using namespace std;

class Potter: public Moving{
    public:
        Potter(int, int, char);
        vector<int> moveCharacter();  // moves the character and it returns the new coordinates
};

#endif