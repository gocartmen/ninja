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

bool Engine::loopDetection()
{
    bool isLoop = false;
    if(prevSteps.size()-1 > 8){
        for(int j=2;j<prevSteps.size()/2.0;j++){
            isLoop = true;
            for(int i=prevSteps.size()-1;i>prevSteps.size()-1-j;i--){
                cout << prevSteps[i] << " , " << prevSteps[i-j] << endl;
                if(prevSteps[i] != prevSteps[i-j] || prevSteps[i] != prevSteps[i-j*2] || prevSteps[i] != prevSteps[i-j*3]){
                    isLoop = false;
                }
            }
            if(isLoop == true){
                j = prevSteps.size()/2.0;
            }
        }
    }
    return !isLoop;
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
                allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                prevSteps.push_back('T');
            }
            if(actualMap->getMap()[ninjaData->getX()][i] == '$' && ninjaData->getShurikens() > 0 && shuriken == false){
                ninjaData->throwShuriken();
                actualMap->setMap(ninjaData->getX(), i, ' ');
                shuriken = true;
                isFinished = true;
                allSteps << "THROW (throws a shuriken to destroy $)" << endl;
                prevSteps.push_back('T');
            }
        }
        for(int i=0;i<actualMap->getH();i++){
            if(actualMap->getMap()[i][ninjaData->getY()] == 'X' && ninjaData->getShurikens() > 0 && shuriken == false){
                ninjaData->throwShuriken();
                actualMap->setMap(i, ninjaData->getY(), '*');
                shuriken = true;
                allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                prevSteps.push_back('T');
            }
            if(actualMap->getMap()[i][ninjaData->getY()] == '$' && ninjaData->getShurikens() > 0 && shuriken == false){
                ninjaData->throwShuriken();
                actualMap->setMap(i, ninjaData->getY(), ' ');
                shuriken = true;
                isFinished = true;
                allSteps << "THROW (throws a shuriken to destroy $)" << endl;
                prevSteps.push_back('T');
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
                    allSteps << "WEST (move)" << endl;
                    prevSteps.push_back('W');
                }
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == 'M'){
                    move = true;
                    ninjaData->setY(ninjaData->getY() - 1);
                    ninjaData->setIsMirrored(!(ninjaData->getIsMirrored()));
                    allSteps << "WEST (move, after that mirrored priority in movement)" << endl;
                    prevSteps.push_back('M');
                }
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == '*'){
                    move = true;
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY()-1, ' ');
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
                    ninjaData->setY(ninjaData->getY() - 1);
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
                    ninjaData->addShuriken();
                    allSteps << "WEST (move, after that collected a shuriken)" << endl;
                    prevSteps.push_back('*');
                }
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == 'B'){
                    move = true;
                    ninjaData->setY(ninjaData->getY() - 1);
                    ninjaData->setBreakerMode(!(ninjaData->getBreakerMode()));
                    if(ninjaData->getBreakerMode() == false){
                        allSteps << "WEST (move, after that entered into breaker mode)" << endl;
                    }else{
                        allSteps << "WEST (move, after that moved out of breaker mode)" << endl;
                    }
                    prevSteps.push_back('B');
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
                    allSteps << "SOUTH (move)" << endl;
                    prevSteps.push_back('S');
                }
                if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == 'M'){
                    move = true;
                    ninjaData->setX(ninjaData->getX() + 1);
                    ninjaData->setIsMirrored(!(ninjaData->getIsMirrored()));
                    allSteps << "SOUTH (move, after that mirrored priority in movement)" << endl;
                    prevSteps.push_back('M');
                }
                if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == '*'){
                    move = true;
                    actualMap->setMap(ninjaData->getX()+1, ninjaData->getY(), ' ');
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
                    ninjaData->setX(ninjaData->getX() + 1);
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
                    ninjaData->addShuriken();
                    allSteps << "SOUTH (move, after that collected a shuriken)" << endl;
                    prevSteps.push_back('*');
                }
                if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == 'B'){
                    move = true;
                    ninjaData->setX(ninjaData->getX() + 1);
                    ninjaData->setBreakerMode(!(ninjaData->getBreakerMode()));
                    if(ninjaData->getBreakerMode() == false){
                        allSteps << "SOUTH (move, after that entered into breaker mode)" << endl;
                    }else{
                        allSteps << "SOUTH (move, after that moved out of breaker mode)" << endl;
                    }
                    prevSteps.push_back('B');
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
                    allSteps << "EAST (move)" << endl;
                    prevSteps.push_back('E');
                }
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == 'M'){
                    move = true;
                    ninjaData->setY(ninjaData->getY() + 1);
                    ninjaData->setIsMirrored(!(ninjaData->getIsMirrored()));
                    allSteps << "EAST (move, after that mirrored priority in movement)" << endl;
                    prevSteps.push_back('M');
                }
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == '*'){
                    move = true;
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY()+1, ' ');
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
                    ninjaData->setY(ninjaData->getY() + 1);
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
                    ninjaData->addShuriken();
                    allSteps << "EAST (move, after that collected a shuriken)" << endl;
                    prevSteps.push_back('*');
                }
                if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == 'B'){
                    move = true;
                    ninjaData->setY(ninjaData->getY() + 1);
                    ninjaData->setBreakerMode(!(ninjaData->getBreakerMode()));
                    if(ninjaData->getBreakerMode() == false){
                        allSteps << "EAST (move, after that entered into breaker mode)" << endl;
                    }else{
                        allSteps << "EAST (move, after that moved out of breaker mode)" << endl;
                    }
                    prevSteps.push_back('B');
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
                    allSteps << "NORTH (move)" << endl;
                    prevSteps.push_back('N');
                }
                if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == 'M'){
                    move = true;
                    ninjaData->setX(ninjaData->getX() - 1);
                    ninjaData->setIsMirrored(!(ninjaData->getIsMirrored()));
                    allSteps << "NORTH (move, after that mirrored priority in movement)" << endl;
                    prevSteps.push_back('M');
                }
                if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == '*'){
                    move = true;
                    actualMap->setMap(ninjaData->getX()-1, ninjaData->getY(), ' ');
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
                    ninjaData->setX(ninjaData->getX() - 1);
                    actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
                    ninjaData->addShuriken();
                    allSteps << "NORTH (move, after that collected a shuriken)" << endl;
                    prevSteps.push_back('*');
                }
                if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == 'B'){
                    move = true;
                    ninjaData->setX(ninjaData->getX() - 1);
                    ninjaData->setBreakerMode(!(ninjaData->getBreakerMode()));
                    if(ninjaData->getBreakerMode() == false){
                        allSteps << "NORTH (move, after that entered into breaker mode)" << endl;
                    }else{
                        allSteps << "NORTH (move, after that moved out of breaker mode)" << endl;
                    }
                    prevSteps.push_back('B');
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
                            allSteps << "SOUTH (because of #)" << endl;
                        }else{
                            allSteps << "NORTH (because of #)" << endl;
                        }
                        prevSteps.push_back('#');
                    }
                    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == 'X'){
                        changeDirection = true;
                        if(ninjaData->getBreakerMode()){
                            actualMap->setMap(ninjaData->getX(), ninjaData->getY()-1, ' ');
                            ninjaData->setY(ninjaData->getY() - 1);
                            allSteps << "WEST (destroyed X in breaker mode)" << endl;
                            prevSteps.push_back('T');
                        }else{
                            ninjaData->changeDirection();
                            allSteps << "SOUTH (because of X)" << endl;
                            prevSteps.push_back('X');
                        }
                    }
                    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()-1] == '$'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            allSteps << "SOUTH (because of $)" << endl;
                        }else{
                            allSteps << "NORTH (because of $)" << endl;
                        }
                        prevSteps.push_back('$');
                    }
                    break;
                }
                case 0:{
                    //south
                    if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == '#'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            allSteps << "EAST (because of #)" << endl;
                        }else{
                            allSteps << "WEST (because of #)" << endl;
                        }
                        prevSteps.push_back('#');
                    }
                    if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == 'X'){
                        changeDirection = true;
                        if(ninjaData->getBreakerMode()){
                            actualMap->setMap(ninjaData->getX()+1, ninjaData->getY(), ' ');
                            ninjaData->setX(ninjaData->getX() + 1);
                            allSteps << "SOUTH (destroyed X in breaker mode)" << endl;
                            prevSteps.push_back('T');
                        }else{
                            ninjaData->changeDirection();
                            allSteps << "EAST (because of X)" << endl;
                            prevSteps.push_back('X');
                        }
                    }
                    if(actualMap->getMap()[ninjaData->getX()+1][ninjaData->getY()] == '$'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            allSteps << "EAST (because of $)" << endl;
                        }else{
                            allSteps << "WEST (because of $)" << endl;
                        }
                        prevSteps.push_back('$');
                    }
                    break;
                }
                case 1:{
                    //east
                    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == '#'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            allSteps << "NORTH (because of #)" << endl;
                        }else{
                            allSteps << "SOUTH (because of #)" << endl;
                        }
                        prevSteps.push_back('#');
                    }
                    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == 'X'){
                        changeDirection = true;
                        if(ninjaData->getBreakerMode()){
                            actualMap->setMap(ninjaData->getX(), ninjaData->getY()+1, ' ');
                            ninjaData->setY(ninjaData->getY() + 1);
                            allSteps << "EAST (destroyed X in breaker mode)" << endl;
                            prevSteps.push_back('T');
                        }else{
                            ninjaData->changeDirection();
                            allSteps << "NORTH (because of X)" << endl;
                            prevSteps.push_back('X');
                        }
                    }
                    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()+1] == '$'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            allSteps << "NORTH (because of $)" << endl;
                        }else{
                            allSteps << "SOUTH (because of $)" << endl;
                        }
                        prevSteps.push_back('$');
                    }
                    break;
                }
                case 2:{
                    //north
                    if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == '#'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            allSteps << "WEST (because of #)" << endl;
                        }else{
                            allSteps << "EAST (because of #)" << endl;
                        }
                        prevSteps.push_back('#');
                    }
                    if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == 'X'){
                        changeDirection = true;
                        if(ninjaData->getBreakerMode()){
                            actualMap->setMap(ninjaData->getX()-1, ninjaData->getY(), ' ');
                            ninjaData->setX(ninjaData->getX() - 1);
                            allSteps << "NORTH (destroyed X in breaker mode)" << endl;
                            prevSteps.push_back('T');
                        }else{
                            ninjaData->changeDirection();
                            allSteps << "WEST (because of X)" << endl;
                            prevSteps.push_back('X');
                        }
                    }
                    if(actualMap->getMap()[ninjaData->getX()-1][ninjaData->getY()] == '$'){
                        changeDirection = true;
                        ninjaData->changeDirection();
                        if(ninjaData->getIsMirrored() == false){
                            allSteps << "WEST (because of $)" << endl;
                        }else{
                            allSteps << "EAST (because of $)" << endl;
                        }
                        prevSteps.push_back('$');
                    }
                    break;
                }
            }
        }
    }
}

void Engine::drawMap()
{
    allSteps << endl;
    for(int i=0;i<actualMap->getH();i++){
        for(int j=0;j<actualMap->getW();j++){
            allSteps << actualMap->getMap()[i][j];
        }
        allSteps << endl;
    }
    allSteps << endl;
}

void Engine::update()
{
    string answer;
    while(state == true){
        allSteps.str("");
        prevSteps.erase(prevSteps.begin(), prevSteps.end());
        while(isFinished == false){
            drawMap();
            checkNextStep();

            mapSolvable = loopDetection();

            if(mapSolvable == false){
                isFinished = true;
            }
        }
        cout << "GAME OVER! ";
        if(mapSolvable == true){
            cout << "Map solved! : " << endl;
            cout << allSteps.str() << endl;
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
