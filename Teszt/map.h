#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Map
{
public:
    struct pos{
        int x = 0;
        int y = 0;
    };
    struct portalPos{
        struct pos position[2];
    };
private:
    vector<string> map;
    int w = 0;
    int h = 0;

    vector<struct pos> unbreakableWalls;
    vector<struct pos> breakableWalls;

    vector<struct portalPos> portals;
    bool Fbool = false;
    bool Gbool = false;
    bool Hbool = false;
    bool Ibool = false;
    bool Jbool = false;
    bool Kbool = false;
    bool Lbool = false;

    vector<struct pos> shurikens;

    vector<struct pos> startPoint;//this is vector because of later compatibility (if more ninjas)
    struct pos holySymbol;
public:
    Map();
    Map(string filename);

    void findTokens();

    vector<pos> getStartPoint();
    pos getHolySymbol() const;
    vector<pos> getShurikens() const;
    vector<portalPos> getPortals() const;
    vector<pos> getBreakableWalls() const;
    vector<pos> getUnbreakableWalls() const;
    int getW() const;
    int getH() const;
    vector<string> getMap() const;
    void setMap(const vector<string> &value);
};

#endif // MAP_H
