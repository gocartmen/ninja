#include <iostream>
#include "namegenerator.h"
#include "maploader.h"

using namespace std;

int main()
{
    NameGenerator * nameGen = new NameGenerator();

    string ninjaName = nameGen->generateName();

    cout << "Your Ninja name is: " << ninjaName << endl;

    MapLoader * maploader = new MapLoader();

    return 0;
}
