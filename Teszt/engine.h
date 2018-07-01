#ifndef ENGINE_H
#define ENGINE_H

#include "namegenerator.h"
#include "maploader.h"
#include "ninjadata.h"

class Engine
{
private:
    NameGenerator * nameGen = NULL;
    MapLoader * mapLoader = NULL;
    NinjaData * ninjaData = NULL;

    bool state = true;//solver run until state is true

    int actualMap = 0;//first map to start
    bool mapSolvable = true;//have to check if map is solvable
public:
    Engine();

    void update();
};

#endif // ENGINE_H
