#ifndef Map_h
#define Map_h

#include <string>
#include <vector>

using namespace std;

class Map{
private:
    int rows;
    int columns;
    string file_path;
    vector<string> the_map;
public:
    Map(char *);
    vector<string> getMap() const;
    int getRows() const;
    int getColumns() const;
};

#endif
