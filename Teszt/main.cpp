#include <iostream>
#include "engine.h"

using namespace std;

int main()
{
    Engine * engine = new Engine();

    engine->update();

    delete engine;

    return 0;
}
