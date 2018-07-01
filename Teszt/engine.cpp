#include "engine.h"

Engine::Engine()
{
    nameGen = new NameGenerator();

    string ninjaName = nameGen->generateName();

    cout << "Your Ninja name is: " << ninjaName << endl;

    mapLoader = new MapLoader();

}

void Engine::update()
{
    while(state == true){

        if(mapSolvable == false){
            state = false;
        }
    }
}
