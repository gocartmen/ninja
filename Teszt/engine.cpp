#include "engine.h"

Engine::Engine()
{
    nameGen = new NameGenerator();

    string ninjaName = nameGen->generateName();

    cout << "Your Ninja name is: " << ninjaName << endl;

    mapLoader = new MapLoader();

    //cout << "1" << endl;
    actualMap = mapLoader->getMap(actualMapNum);

    //cout << "2" << endl;
    ninjaData = new NinjaData(actualMap->getStartPoint()[0].x, actualMap->getStartPoint()[0].y);

    //cout << "3" << endl;
}

void Engine::checkNextStep()
{

}

void Engine::update()
{
    //cout << "Is it updating? " << endl;
    string answer;
    while(state == true){
        while(isFinished == false){
            mapSolvable = false;//temporary
            if(mapSolvable == false){
                isFinished = true;
            }
        }
        cout << "GAME OVER! ";
        if(mapSolvable == true){
            cout << "Map solved!" << endl;
        }else{
            cout << "Map cannot be solved!" << endl;
        }
        do{
            cout << "Do you wish to continue with next map? (y, n)" << endl;
            cin >> answer;
            if(toupper(answer[0]) == 'Y'){
                isFinished = false;
                mapSolvable = true;
            }
            if(toupper(answer[0]) == 'N'){
                state = false;
            }
        }while(toupper(answer[0]) != 'Y' || toupper(answer[0]) != 'N');
    }
}
