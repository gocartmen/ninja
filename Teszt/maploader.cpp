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

    maps = new Map*[mapCount-1];
    for(int i=0;i<mapCount-1;i++){
        maps[i] = new Map(mapnames[i]);
        //cout << "map : " << i << endl;
        maps[i]->findTokens();
        //cout << "map tokens found!" << endl;
    }
}

Map *MapLoader::getMap(int num)
{
    return maps[num];
}
