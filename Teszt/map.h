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
    struct timeBomb{
        int timer = 0;
        int x = 0;
        int y = 0;
    };
private:
    vector<string> map;
    int w = 0;
    int h = 0;

    vector<struct portalPos> portals;
    bool Fbool = false;
    bool Gbool = false;
    bool Hbool = false;
    bool Ibool = false;
    bool Jbool = false;
    bool Kbool = false;
    bool Lbool = false;

    vector<struct pos> startPoint;//this is vector because of later compatibility (if more ninjas)
    vector<struct timeBomb> bombs;
public:
    Map();
    Map(string filename);

    void findTokens();

    vector<pos> getStartPoint();
    vector<portalPos> getPortals() const;
    int getW() const;
    int getH() const;
    vector<string> getMap() const;
    void setMap(int x, int y, char value);
    vector<timeBomb> getBombs() const;
    void setBomb(int id, int value);
};

#endif // MAP_H
