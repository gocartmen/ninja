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
    bool alive = true;
    bool isPlayer = false;

    bool isFight = false;
    char lastStep = '';
public:
    NinjaData();
    NinjaData(int x, int y);

    void throwShuriken();
    void changeDirection();
    void addShuriken();

    int calcStrength();

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
    bool getAlive() const;
    void setAlive(bool value);
    bool getIsPlayer() const;
    void setIsPlayer(bool value);
    bool getIsFight() const;
    void setIsFight(bool value);
    char getLastStep() const;
    void setLastStep(char value);
};

#endif // NINJADATA_H
