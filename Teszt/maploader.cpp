#include "maploader.h"

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

    file.close();

    maps = new Map*[mapCount];
    for(int i=0;i<mapCount;i++){
        maps[i] = new Map(mapnames[i]);
    }
}
