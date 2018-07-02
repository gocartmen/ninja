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

    Map * actualMap = NULL;

    bool state = true;//solver run until state is true

    int actualMapNum = 0;//first map to start
    bool mapSolvable = true;//have to check if map is solvable

    bool isFinished = false;

    bool move;
    bool shuriken;
    bool changeDirection;

    void setNewDirection(int x, int y);
    void secretPaths(int x, int y);
    void checkNextStep();
    void drawMap();
public:
    Engine();

    void update();
};

#endif // ENGINE_H
