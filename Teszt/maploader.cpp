#include "maploader.h"

int MapLoader::getMapCount() const
{
    return mapCount;
}

MapLoader::MapLoader()
{
    ifstream file;
    file.open("input-all.list");

    string data;
    while(file.good()){
        getline(file, data);
        mapnames.push_back(data);
        mapCount++;
    }

    mapCount--;

    file.close();

    maps = new Map*[mapCount];
    for(int i=0;i<mapCount;i++){
        maps[i] = new Map(mapnames[i]);
        //cout << "map : " << i << endl;
        maps[i]->findTokens();
        //cout << "map tokens found!" << endl;
    }
}

MapLoader::~MapLoader()
{
    for(int i=0;i<mapCount;i++){
        delete maps[i];
    }
    delete [] maps;
}

Map *MapLoader::getMap(int num)
{
    return maps[num];
}
