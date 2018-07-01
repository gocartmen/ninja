#include "ninjadata.h"

int NinjaData::getDirection() const
{
    return direction;
}

void NinjaData::setDirection(int value)
{
    direction = value;
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
