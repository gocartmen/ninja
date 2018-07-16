#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "map.h"

using namespace std;

class MapLoader
{
private:
    Map ** maps;
    vector<string> mapnames;
    int mapCount = 0;
public:
    MapLoader();
    ~MapLoader();

    Map * getMap(int num);
    int getMapCount() const;
};

#endif // MAPLOADER_H
