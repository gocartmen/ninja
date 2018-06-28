#include <iostream>
#include "namegenerator.h"

using namespace std;

int main()
{
    NameGenerator * nameGen = new NameGenerator();

    string ninjaName = nameGen->generateName();

    cout << "Your Ninja name is: " << ninjaName << endl;

    return 0;
}
