#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Map
{
private:
    vector<string> map;
    int w = 0;
    int h = 0;
public:
    Map();
    Map(string filename);
};

#endif // MAP_H
