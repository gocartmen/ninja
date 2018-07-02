#include "ninjadata.h"

int NinjaData::getDirection() const
{
    return direction;
}

void NinjaData::setDirection(int value)
{
    direction = value;
}

int NinjaData::getX() const
{
    return x;
}

void NinjaData::setX(int value)
{
    x = value;
}

int NinjaData::getY() const
{
    return y;
}

void NinjaData::setY(int value)
{
    y = value;
}

int NinjaData::getShurikens() const
{
    return shurikens;
}

bool NinjaData::getIsMirrored() const
{
    return isMirrored;
}

void NinjaData::setIsMirrored(bool value)
{
    isMirrored = value;
}

bool NinjaData::getBreakerMode() const
{
    return breakerMode;
}

void NinjaData::setBreakerMode(bool value)
{
    breakerMode = value;
}

NinjaData::NinjaData()
{

}

NinjaData::NinjaData(int x, int y)
{
    this->x = x;
    this->y = y;
}

void NinjaData::throwShuriken()
{
    shurikens--;
}

void NinjaData::changeDirection()
{
    if(isMirrored == false){
        if(direction < 4){
            direction++;
            if(direction > 3){
                direction = 0;
            }
        }
    }else{
        if(direction > -1){
            direction--;
            if(direction < 0){
                direction = 3;
            }
        }
    }
}

void NinjaData::addShuriken()
{
    shurikens++;
}
