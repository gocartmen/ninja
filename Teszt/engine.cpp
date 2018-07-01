#include "engine.h"

Engine::Engine()
{
    nameGen = new NameGenerator();

    string ninjaName = nameGen->generateName();

    cout << "Your Ninja name is: " << ninjaName << endl;

    mapLoader = new MapLoader();

    actualMap = mapLoader->getMap(actualMapNum);

    ninjaData = new NinjaData(actualMap->getStartPoint()[0].x, actualMap->getStartPoint()[0].y);
}

void Engine::checkNextStep()
{

}

void Engine::update()
{
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
            if(actualMapNum < mapLoader->getMapCount()){
                cout << "Do you wish to continue with next map? (y, n)" << endl;
                cin >> answer;
                if(toupper(answer[0]) == 'Y'){
                    isFinished = false;
                    mapSolvable = true;
                    actualMapNum++;
                    delete ninjaData;
                    //reinit some data
                    actualMap = mapLoader->getMap(actualMapNum);

                    ninjaData = new NinjaData(actualMap->getStartPoint()[0].x, actualMap->getStartPoint()[0].y);
                    //----------------
                }
                if(toupper(answer[0]) == 'N'){
                    state = false;
                }
            }else{
                cout << "Played all maps! Exiting now!" << endl;
                state = false;
            }
        }while(toupper(answer[0]) != 'Y' && toupper(answer[0]) != 'N');
    }
}
