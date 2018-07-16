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
    NinjaData ** ninjaData = NULL;

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

    void setNewDirection(NinjaData *ninjaData, int x, int y);
    void secretPaths(NinjaData *ninjaData, int x, int y);
    bool loopDetection();
    void drawMap();

    //checkNextStep helper functions---
    void throwShuriken(NinjaData *ninjaData, bool &obstacle);
    void moveAction(NinjaData *ninjaData, string direction);
    void changeMoveDirection(NinjaData *ninjaData, string direction, string prev, string next);
    //---------------------------------
    void checkNextStep(NinjaData *ninjaData);

    void checkBombs();
    void detonate(int ID);
    void earlyExplode(int x, int y, int actualBombID);
    void ninjaKill(NinjaData *ninjaData, int i, int j);
public:
    Engine();
    ~Engine();

    void update();
};

#endif // ENGINE_H
