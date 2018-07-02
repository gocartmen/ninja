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

    bool breakerMode = false;
public:
    NinjaData();
    NinjaData(int x, int y);

    void throwShuriken();
    void changeDirection();
    void addShuriken();

    int getDirection() const;
    void setDirection(int value);
    int getX() const;
    void setX(int value);
    int getY() const;
    void setY(int value);
    int getShurikens() const;
    bool getIsMirrored() const;
    void setIsMirrored(bool value);
    bool getBreakerMode() const;
    void setBreakerMode(bool value);
};

#endif // NINJADATA_H
