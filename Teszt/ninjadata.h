#ifndef NINJADATA_H
#define NINJADATA_H

#include <iostream>

using namespace std;

class NinjaData
{
private:
    int shurikens = 3;
    int direction = 0;//facing south

    int x = 0;
    int y = 0;
public:
    NinjaData();
    NinjaData(int x, int y);
};

#endif // NINJADATA_H
