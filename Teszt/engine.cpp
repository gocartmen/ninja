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

void Engine::setNewDirection(int x, int y)
{
    if(actualMap->getMap()[ninjaData->getX()+x][ninjaData->getY()+y] == 'S'){
        move = true;
        ninjaData->setX(ninjaData->getX() + x);
        ninjaData->setY(ninjaData->getY() + y);
        ninjaData->setDirection(0);
    }
    if(actualMap->getMap()[ninjaData->getX()+x][ninjaData->getY()+y] == 'E'){
        move = true;
        ninjaData->setX(ninjaData->getX() + x);
        ninjaData->setY(ninjaData->getY() + y);
        ninjaData->setDirection(1);
    }
    if(actualMap->getMap()[ninjaData->getX()+x][ninjaData->getY()+y] == 'N'){
        move = true;
        ninjaData->setX(ninjaData->getX() + x);
        ninjaData->setY(ninjaData->getY() + y);
        ninjaData->setDirection(2);
    }
    if(actualMap->getMap()[ninjaData->getX()+x][ninjaData->getY()+y] == 'W'){
        move = true;
        ninjaData->setX(ninjaData->getX() + x);
        ninjaData->setY(ninjaData->getY() + y);
        ninjaData->setDirection(3);
    }
}

void Engine::secretPaths(int x, int y)
{
    if(actualMap->getMap()[ninjaData->getX()+x][ninjaData->getY()+y] == 'F' ||
       actualMap->getMap()[ninjaData->getX()+x][ninjaData->getY()+y] == 'G' ||
       actualMap->getMap()[ninjaData->getX()+x][ninjaData->getY()+y] == 'H' ||
       actualMap->getMap()[ninjaData->getX()+x][ninjaData->getY()+y] == 'I' ||
       actualMap->getMap()[ninjaData->getX()+x][ninjaData->getY()+y] == 'J' ||
       actualMap->getMap()[ninjaData->getX()+x][ninjaData->getY()+y] == 'K' ||
       actualMap->getMap()[ninjaData->getX()+x][ninjaData->getY()+y] == 'L'){
        move = true;
        for(int i=0;i<actualMap->getPortals().size();i++){
            if((actualMap->getPortals()[i].position[0].x == ninjaData->getX() && actualMap->getPortals()[i].position[0].y == ninjaData->getY())){
                ninjaData->setX(actualMap->getPortals()[i].position[1].x);
                ninjaData->setY(actualMap->getPortals()[i].position[1].y);
            }else if((actualMap->getPortals()[i].position[1].x == ninjaData->getX() && actualMap->getPortals()[i].position[1].y == ninjaData->getY())){
                ninjaData->setX(actualMap->getPortals()[i].position[0].x);
                ninjaData->setY(actualMap->getPortals()[i].position[0].y);
            }
        }
    }
}

void Engine::checkNextStep()
{
    shuriken = false;
    if(ninjaData->getShurikens() > 0){
        for(int i=0;i<actualMap->getW();i++){
            if(actualMap->getMap()[ninjaData->getX()][i] == 'X' && ninjaData->getShurikens() > 0 && shuriken == false){
                ninjaData->throwShuriken();
                actualMap->setMap(ninjaData->getX(), i, '*');
                shuriken = true;
                cout << "THROW (throws a shuriken to destroy X)" << endl;
            }
            if(actualMap->getMap()[ninjaData->getX()][i] == '$' && ninjaData->getShurikens() > 0 && shuriken == false){
                ninjaData->throwShuriken();
                actualMap->setMap(ninjaData->getX(), i, ' ');
                shuriken = true;
                isFinished = true;
                cout << "THROW (throws a shuriken to destroy $)" << endl;
            }
        }
        for(int i=0;i<actualMap->getH();i++){
            if(actualMap->getMap()[i][ninjaData->getY()] == 'X' && ninjaData->getShurikens() > 0 && shuriken == false){
                ninjaData->throwShuriken();
                actualMap->setMap(i, ninjaData->getY(), '*');
                shuriken = true;
                cout << "THROW (throws a shuriken to destroy X)" << endl;
            }
            if(actualMap->getMap()[i][ninjaData->getY()] == '$' && ninjaData->getShurikens() > 0 && shuriken == false){
                ninjaData->throwShuriken();
                actualMap->setMap(i, ninjaData->getY(), ' ');
                shuriken = true;
                isFinished = true;
                cout << "THROW (throws a shuriken to destroy $)" << endl;
            }
        }
    }

    move = false;
    if(shuriken == false){
        switch(ninjaData->getDirection()){
            case 3:{
                //west
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == ' '){
                    move = true;
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
                    ninjaData->setY(ninjaData->getY() - 1);
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
                    cout << "WEST (move)" << endl;
                }
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == 'M'){
                    move = true;
                    ninjaData->setY(ninjaData->getY() - 1);
                    ninjaData->setIsMirrored(!(ninjaData->getIsMirrored()));
                    cout << "WEST (move, after that mirrored priority in movement)" << endl;
                }
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == '*'){
                    move = true;
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY()-1, ' ');
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
                    ninjaData->setY(ninjaData->getY() - 1);
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
                    ninjaData->addShuriken();
                    cout << "WEST (move, after that collected a shuriken)" << endl;
                }
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == 'B'){
                    move = true;
                    ninjaData->setY(ninjaData->getY() - 1);
                    ninjaData->setBreakerMode(!(ninjaData->getBreakerMode()));
                    if(ninjaData->getBreakerMode() == false){
                        cout << "WEST (move, after that entered into breaker mode)" << endl;
                    }else{
                        cout << "WEST (move, after that moved out of breaker mode)" << endl;
                    }
                }
                setNewDirection(0,-1);
                secretPaths(0,-1);
                break;
            }
            case 0:{
                //south
                if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == ' '){
                    move = true;
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
                    ninjaData->setX(ninjaData->getX() + 1);
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
                    cout << "SOUTH (move)" << endl;
                }
                if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == 'M'){
                    move = true;
                    ninjaData->setX(ninjaData->getX() + 1);
                    ninjaData->setIsMirrored(!(ninjaData->getIsMirrored()));
                    cout << "SOUTH (move, after that mirrored priority in movement)" << endl;
                }
                if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == '*'){
                    move = true;
                    actualMap->setMap(ninjaData->getX()+1, ninjaData->getY(), ' ');
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
                    ninjaData->setX(ninjaData->getX() + 1);
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
                    ninjaData->addShuriken();
                    cout << "SOUTH (move, after that collected a shuriken)" << endl;
                }
                if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == 'B'){
                    move = true;
                    ninjaData->setX(ninjaData->getX() + 1);
                    ninjaData->setBreakerMode(!(ninjaData->getBreakerMode()));
                    if(ninjaData->getBreakerMode() == false){
                        cout << "SOUTH (move, after that entered into breaker mode)" << endl;
                    }else{
                        cout << "SOUTH (move, after that moved out of breaker mode)" << endl;
                    }
                }
                setNewDirection(1,0);
                secretPaths(1,0);
                break;
            }
            case 1:{
                //east
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == ' '){
                    move = true;
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
                    ninjaData->setY(ninjaData->getY() + 1);
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
                    cout << "EAST (move)" << endl;
                }
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == 'M'){
                    move = true;
                    ninjaData->setY(ninjaData->getY() + 1);
                    ninjaData->setIsMirrored(!(ninjaData->getIsMirrored()));
                    cout << "EAST (move, after that mirrored priority in movement)" << endl;
                }
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == '*'){
                    move = true;
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY()+1, ' ');
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
                    ninjaData->setY(ninjaData->getY() + 1);
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
                    ninjaData->addShuriken();
                    cout << "EAST (move, after that collected a shuriken)" << endl;
                }
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == 'B'){
                    move = true;
                    ninjaData->setY(ninjaData->getY() + 1);
                    ninjaData->setBreakerMode(!(ninjaData->getBreakerMode()));
                    if(ninjaData->getBreakerMode() == false){
                        cout << "EAST (move, after that entered into breaker mode)" << endl;
                    }else{
                        cout << "EAST (move, after that moved out of breaker mode)" << endl;
                    }
                }
                setNewDirection(0,1);
                secretPaths(0,1);
                break;
            }
            case 2:{
                //north
                if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == ' '){
                    move = true;
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
                    ninjaData->setX(ninjaData->getX() - 1);
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
                    cout << "NORTH (move)" << endl;
                }
                if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == 'M'){
                    move = true;
                    ninjaData->setX(ninjaData->getX() - 1);
                    ninjaData->setIsMirrored(!(ninjaData->getIsMirrored()));
                    cout << "NORTH (move, after that mirrored priority in movement)" << endl;
                }
                if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == '*'){
                    move = true;
                    actualMap->setMap(ninjaData->getX()-1, ninjaData->getY(), ' ');
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
                    ninjaData->setX(ninjaData->getX() - 1);
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
                    ninjaData->addShuriken();
                    cout << "NORTH (move, after that collected a shuriken)" << endl;
                }
                if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == 'B'){
                    move = true;
                    ninjaData->setX(ninjaData->getX() - 1);
                    ninjaData->setBreakerMode(!(ninjaData->getBreakerMode()));
                    if(ninjaData->getBreakerMode() == false){
                        cout << "NORTH (move, after that entered into breaker mode)" << endl;
                    }else{
                        cout << "NORTH (move, after that moved out of breaker mode)" << endl;
                    }
                }
                setNewDirection(-1,0);
                secretPaths(-1,0);
                break;
            }
        }
        if(move == false){
            changeDirection = false;
            switch(ninjaData->getDirection()){
                case 3:{
                    //west
                    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == '#'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            cout << "SOUTH (because of #)" << endl;
                        }else{
                            cout << "NORTH (because of #)" << endl;
                        }
                    }
                    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == 'X'){
                        changeDirection = true;
                        if(ninjaData->getBreakerMode()){
                            actualMap->setMap(ninjaData->getX(), ninjaData->getY()-1, ' ');
                            ninjaData->setY(ninjaData->getY() - 1);
                            cout << "WEST (destroyed X in breaker mode)" << endl;
                        }else{
                            ninjaData->changeDirection();
                            cout << "SOUTH (because of X)" << endl;
                        }
                    }
                    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == '$'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            cout << "SOUTH (because of #)" << endl;
                        }else{
                            cout << "NORTH (because of #)" << endl;
                        }
                    }
                    break;
                }
                case 0:{
                    //south
                    if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == '#'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            cout << "EAST (because of #)" << endl;
                        }else{
                            cout << "WEST (because of #)" << endl;
                        }
                    }
                    if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == 'X'){
                        changeDirection = true;
                        if(ninjaData->getBreakerMode()){
                            actualMap->setMap(ninjaData->getX()+1, ninjaData->getY(), ' ');
                            ninjaData->setX(ninjaData->getX() + 1);
                            cout << "SOUTH (destroyed X in breaker mode)" << endl;
                        }else{
                            ninjaData->changeDirection();
                            cout << "EAST (because of X)" << endl;
                        }
                    }
                    if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == '$'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            cout << "EAST (because of #)" << endl;
                        }else{
                            cout << "WEST (because of #)" << endl;
                        }
                    }
                    break;
                }
                case 1:{
                    //east
                    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == '#'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            cout << "NORTH (because of #)" << endl;
                        }else{
                            cout << "SOUTH (because of #)" << endl;
                        }
                    }
                    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == 'X'){
                        changeDirection = true;
                        if(ninjaData->getBreakerMode()){
                            actualMap->setMap(ninjaData->getX(), ninjaData->getY()+1, ' ');
                            ninjaData->setY(ninjaData->getY() + 1);
                            cout << "EAST (destroyed X in breaker mode)" << endl;
                        }else{
                            ninjaData->changeDirection();
                            cout << "NORTH (because of X)" << endl;
                        }
                    }
                    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == '$'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            cout << "NORTH (because of #)" << endl;
                        }else{
                            cout << "SOUTH (because of #)" << endl;
                        }
                    }
                    break;
                }
                case 2:{
                    //north
                    if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == '#'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            cout << "WEST (because of #)" << endl;
                        }else{
                            cout << "EAST (because of #)" << endl;
                        }
                    }
                    if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == 'X'){
                        changeDirection = true;
                        if(ninjaData->getBreakerMode()){
                            actualMap->setMap(ninjaData->getX()-1, ninjaData->getY(), ' ');
                            ninjaData->setX(ninjaData->getX() - 1);
                            cout << "NORTH (destroyed X in breaker mode)" << endl;
                        }else{
                            ninjaData->changeDirection();
                            cout << "WEST (because of X)" << endl;
                        }
                    }
                    if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == '$'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            cout << "WEST (because of #)" << endl;
                        }else{
                            cout << "EAST (because of #)" << endl;
                        }
                    }
                    break;
                }
            }
        }
    }
}

void Engine::drawMap()
{
    for(int i=0;i<actualMap->getW();i++){
        for(int j=0;j<actualMap->getH();j++){
            cout << actualMap->getMap()[i][j];
        }
        cout << endl;
    }
}

void Engine::update()
{
    string answer;
    while(state == true){
        while(isFinished == false){
            drawMap();
            checkNextStep();

            //mapSolvable = false;//temporary
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
