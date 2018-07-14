#ifndef ENGINE_H
#define ENGINE_H

#include "namegenerator.h"
#include "maploader.h"
#include "ninjadata.h"

#define BOMBRANGE 2

class Engine
{
private:
    NameGenerator * nameGen = NULL;
    MapLoader * mapLoader = NULL;
    NinjaData * ninjaData = NULL;

    Map * actualMap = NULL;

    vector<char> prevSteps;
    stringstream allSteps;

    bool state = true;//solver run until state is true

    int actualMapNum = 0;//first map to start
    bool mapSolvable = true;//have to check if map is solvable

    bool isFinished = false;

    bool move;
    bool shuriken;
    bool changeDirection;

    void setNewDirection(int x, int y);
    void secretPaths(int x, int y);
    bool loopDetection();
    void drawMap();

    //checkNextStep helper functions---
    void throwShuriken(bool &obstacle);
    void moveAction(string direction);
    void changeMoveDirection(string direction, string prev, string next);
    //---------------------------------
    void checkNextStep();

    void checkBombs();
    void detonate(int ID);
    void earlyExplode(int x, int y, int actualBombID);
    void ninjaKill(int i, int j);
public:
    Engine();

    void update();
};

#endif // ENGINE_H
