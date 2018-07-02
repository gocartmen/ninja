#include "engine.h"

Engine::Engine()
{
    nameGen = new NameGenerator();

    string ninjaName = nameGen->generateName();

    cout << "Your Ninja name is: " << ninjaName << endl;

    mapLoader = new MapLoader();

    actualMap = mapLoader->getMap(actualMapNum);

    ninjaData = new NinjaData(actualMap->getStartPoint()[0].x, actualMap->getStartPoint()[0].y);

    move = false;

    shuriken = false;

    changeDirection = false;
}

void Engine::checkNextStep()
{
    shuriken = false;
    if(ninjaData->getShurikens() > 0){
        for(int i=0;i<actualMap->getH();i++){
            if(actualMap->getMap()[ninjaData->getX()][i] == 'X' && ninjaData->getShurikens() > 0 && shuriken == false){
                ninjaData->throwShuriken();
                actualMap->getMap()[ninjaData->getX()][i] = ' ';
                shuriken = true;
            }
        }
        for(int i=0;i<actualMap->getW();i++){
            if(actualMap->getMap()[i][ninjaData->getY()] == 'X' && ninjaData->getShurikens() > 0 && shuriken == false){
                ninjaData->throwShuriken();
                actualMap->getMap()[i][ninjaData->getY()] = ' ';
                shuriken = true;
            }
        }
    }

    move = false;
    if(shuriken == false){
        switch(ninjaData->getDirection()){
            case 0:{
                //south
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == ' '){
                    move = true;
                    ninjaData->setY(ninjaData->getY() - 1);
                }
                break;
            }
            case 1:{
                //east
                if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == ' '){
                    move = true;
                    ninjaData->setX(ninjaData->getX() + 1);
                }
                break;
            }
            case 2:{
                //north
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == ' '){
                    move = true;
                    ninjaData->setY(ninjaData->getY() + 1);
                }
                break;
            }
            case 3:{
                //west
                if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == ' '){
                    move = true;
                    ninjaData->setX(ninjaData->getX() - 1);
                }
                break;
            }
        }
        if(move == false){
            changeDirection = false;
            switch(ninjaData->getDirection()){
                case 0:{
                    //south
                    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == '#' || actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == 'X'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                    }
                    break;
                }
                case 1:{
                    //east
                    if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == '#' || actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == 'X'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                    }
                    break;
                }
                case 2:{
                    //north
                    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == '#' || actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == 'X'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                    }
                    break;
                }
                case 3:{
                    //west
                    if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == '#' || actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == 'X'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                    }
                    break;
                }
            }
        }
    }
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
