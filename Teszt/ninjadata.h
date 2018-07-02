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
    bool isMirrored = false;
public:
    NinjaData();
    NinjaData(int x, int y);

    void throwShuriken();
    void changeDirection();

    int getDirection() const;
    void setDirection(int value);
    int getX() const;
    void setX(int value);
    int getY() const;
    void setY(int value);
    int getShurikens() const;
};

#endif // NINJADATA_H
