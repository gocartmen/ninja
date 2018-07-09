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
            if((actualMap->getPortals()[i].position[0].x == ninjaData->getX()+x && actualMap->getPortals()[i].position[0].y == ninjaData->getY()+y)){
                ninjaData->setX(actualMap->getPortals()[i].position[1].x);
                ninjaData->setY(actualMap->getPortals()[i].position[1].y);
                allSteps << "Secret path used!" << endl;
            }else if((actualMap->getPortals()[i].position[1].x == ninjaData->getX()+x && actualMap->getPortals()[i].position[1].y == ninjaData->getY()+y)){
                ninjaData->setX(actualMap->getPortals()[i].position[0].x);
                ninjaData->setY(actualMap->getPortals()[i].position[0].y);
                allSteps << "Secret path used!" << endl;
            }
        }
    }
}

bool Engine::loopDetection()
{
    //cout << "MapID: " << actualMapNum << endl;
    int checkLength = 0;
    if(actualMap->getH() > actualMap->getW()){
        checkLength = actualMap->getH();
    }else{
        checkLength = actualMap->getW();
    }
    bool isLoop = false;
    if(prevSteps.size()-1 > checkLength*4){
        for(int j=checkLength;j<prevSteps.size()/2.0;j++){
            isLoop = true;
            for(int i=prevSteps.size()-1;i>prevSteps.size()-1-j;i--){
                //cout << prevSteps[i] << " , " << prevSteps[i-j] << " , " << prevSteps[i-j*2] << " , " << prevSteps[i-j*3] << endl;
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

void Engine::throwShuriken(bool &obstacle){
    if(ninjaData->getIsMirrored() == false){
        for(int i=ninjaData->getX();i<actualMap->getH();i++){
            //cout << "11++" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[i][ninjaData->getY()] == '#'){
                    obstacle = true;
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
        obstacle = false;
        for(int i=ninjaData->getY();i<actualMap->getW();i++){
            //cout << "12++" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[ninjaData->getX()][i] == '#'){
                    obstacle = true;
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
        }
        obstacle = false;
        for(int i=ninjaData->getX();i>0;i--){
            //cout << "13--" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[i][ninjaData->getY()] == '#'){
                    obstacle = true;
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
        obstacle = false;
        for(int i=ninjaData->getY();i>0;i--){
            //cout << "14--" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[ninjaData->getX()][i] == '#'){
                    obstacle = true;
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
        }
    }else{
        for(int i=ninjaData->getX();i<actualMap->getH();i++){
            //cout << "21++" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[i][ninjaData->getY()] == '#'){
                    obstacle = true;
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
        obstacle = false;
        for(int i=ninjaData->getY();i>0;i--){
            //cout << "22--" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[ninjaData->getX()][i] == '#'){
                    obstacle = true;
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
        }
        obstacle = false;
        for(int i=ninjaData->getX();i>0;i--){
            //cout << "23--" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[i][ninjaData->getY()] == '#'){
                    obstacle = true;
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
        obstacle = false;
        for(int i=ninjaData->getY();i<actualMap->getW();i++){
            //cout << "24++" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[ninjaData->getX()][i] == '#'){
                    obstacle = true;
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
        }
    }
    obstacle = false;
    if(ninjaData->getIsMirrored() == false){
        for(int i=ninjaData->getX();i<actualMap->getH();i++){
            //cout << "11++" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[i][ninjaData->getY()] == '#'){
                    obstacle = true;
                }
                if(actualMap->getMap()[i][ninjaData->getY()] == 'X' && ninjaData->getShurikens() > 0 && shuriken == false){
                    ninjaData->throwShuriken();
                    actualMap->setMap(i, ninjaData->getY(), '*');
                    shuriken = true;
                    allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                    prevSteps.push_back('T');
                }
            }
        }
        obstacle = false;
        for(int i=ninjaData->getY();i<actualMap->getW();i++){
            //cout << "12++" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[ninjaData->getX()][i] == '#'){
                    obstacle = true;
                }
                if(actualMap->getMap()[ninjaData->getX()][i] == 'X' && ninjaData->getShurikens() > 0 && shuriken == false){
                    ninjaData->throwShuriken();
                    actualMap->setMap(ninjaData->getX(), i, '*');
                    shuriken = true;
                    allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                    prevSteps.push_back('T');
                }
            }
        }
        obstacle = false;
        for(int i=ninjaData->getX();i>0;i--){
            //cout << "13--" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[i][ninjaData->getY()] == '#'){
                    obstacle = true;
                }
                if(actualMap->getMap()[i][ninjaData->getY()] == 'X' && ninjaData->getShurikens() > 0 && shuriken == false){
                    ninjaData->throwShuriken();
                    actualMap->setMap(i, ninjaData->getY(), '*');
                    shuriken = true;
                    allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                    prevSteps.push_back('T');
                }
            }
        }
        obstacle = false;
        for(int i=ninjaData->getY();i>0;i--){
            //cout << "14--" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[ninjaData->getX()][i] == '#'){
                    obstacle = true;
                }
                if(actualMap->getMap()[ninjaData->getX()][i] == 'X' && ninjaData->getShurikens() > 0 && shuriken == false){
                    ninjaData->throwShuriken();
                    actualMap->setMap(ninjaData->getX(), i, '*');
                    shuriken = true;
                    allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                    prevSteps.push_back('T');
                }
            }
        }
    }else{
        for(int i=ninjaData->getX();i<actualMap->getH();i++){
            //cout << "21++" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[i][ninjaData->getY()] == '#'){
                    obstacle = true;
                }
                if(actualMap->getMap()[i][ninjaData->getY()] == 'X' && ninjaData->getShurikens() > 0 && shuriken == false){
                    ninjaData->throwShuriken();
                    actualMap->setMap(i, ninjaData->getY(), '*');
                    shuriken = true;
                    allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                    prevSteps.push_back('T');
                }
            }
        }
        obstacle = false;
        for(int i=ninjaData->getY();i>0;i--){
            //cout << "22--" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[ninjaData->getX()][i] == '#'){
                    obstacle = true;
                }
                if(actualMap->getMap()[ninjaData->getX()][i] == 'X' && ninjaData->getShurikens() > 0 && shuriken == false){
                    ninjaData->throwShuriken();
                    actualMap->setMap(ninjaData->getX(), i, '*');
                    shuriken = true;
                    allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                    prevSteps.push_back('T');
                }
            }
        }
        obstacle = false;
        for(int i=ninjaData->getX();i>0;i--){
            //cout << "23--" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[i][ninjaData->getY()] == '#'){
                    obstacle = true;
                }
                if(actualMap->getMap()[i][ninjaData->getY()] == 'X' && ninjaData->getShurikens() > 0 && shuriken == false){
                    ninjaData->throwShuriken();
                    actualMap->setMap(i, ninjaData->getY(), '*');
                    shuriken = true;
                    allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                    prevSteps.push_back('T');
                }
            }
        }
        obstacle = false;
        for(int i=ninjaData->getY();i<actualMap->getW();i++){
            //cout << "24++" << endl;
            if(obstacle == false){
                if(actualMap->getMap()[ninjaData->getX()][i] == '#'){
                    obstacle = true;
                }
                if(actualMap->getMap()[ninjaData->getX()][i] == 'X' && ninjaData->getShurikens() > 0 && shuriken == false){
                    ninjaData->throwShuriken();
                    actualMap->setMap(ninjaData->getX(), i, '*');
                    shuriken = true;
                    allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                    prevSteps.push_back('T');
                }
            }
        }
    }

    //OLD shuriken targeting
    /*for(int i=0;i<actualMap->getW();i++){
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
    }*/
}

void Engine::moveAction(string direction){
    int x=0;
    int y=0;

    switch(direction[0]){
        case 'W':{
            x = 0;
            y = -1;
            break;
        }
        case 'S':{
            x = 1;
            y = 0;
            break;
        }
        case 'E':{
            x = 0;
            y = 1;
            break;
        }
        case 'N':{
            x = -1;
            y = 0;
        }
    }

    switch(actualMap->getMap()[ninjaData->getX()+x][ninjaData->getY()+y]){
        case ' ':{
            move = true;
            //actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
            ninjaData->setX(ninjaData->getX() + x);
            ninjaData->setY(ninjaData->getY() + y);
            //actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
            allSteps << direction << " (move)" << endl;
            prevSteps.push_back(direction[0]);
            break;
        }
        case 'M':{
            move = true;
            ninjaData->setX(ninjaData->getX() + x);
            ninjaData->setY(ninjaData->getY() + y);
            ninjaData->setIsMirrored(!(ninjaData->getIsMirrored()));
            allSteps << direction << " (move, after that mirrored priority in movement)" << endl;
            prevSteps.push_back('M');
            break;
        }
        case '*':{
            move = true;
            actualMap->setMap(ninjaData->getX()+x, ninjaData->getY()+y, ' ');
            //actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
            ninjaData->setX(ninjaData->getX() + x);
            ninjaData->setY(ninjaData->getY() + y);
            //actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
            ninjaData->addShuriken();
            allSteps << direction << " (move, after that collected a shuriken)" << endl;
            prevSteps.push_back('*');
            break;
        }
        case 'B':{
            move = true;
            ninjaData->setX(ninjaData->getX() + x);
            ninjaData->setY(ninjaData->getY() + y);
            ninjaData->setBreakerMode(!(ninjaData->getBreakerMode()));
            if(ninjaData->getBreakerMode() == true){
                allSteps << direction << " (move, after that entered into breaker mode)" << endl;
            }else{
                allSteps << direction << " (move, after that moved out of breaker mode)" << endl;
            }
            prevSteps.push_back('B');
            break;
        }
    }

    setNewDirection(x,y);
    secretPaths(x,y);
}

void Engine::changeMoveDirection(string direction, string prev, string next){
    int x=0;
    int y=0;

    switch(direction[0]){
        case 'W':{
            x = 0;
            y = -1;
            break;
        }
        case 'S':{
            x = 1;
            y = 0;
            break;
        }
        case 'E':{
            x = 0;
            y = 1;
            break;
        }
        case 'N':{
            x = -1;
            y = 0;
        }
    }

    switch(actualMap->getMap()[ninjaData->getX()+x][ninjaData->getY()+y]){
        case '#':{
            changeDirection = true;
            ninjaData->changeDirection();
            if(ninjaData->getIsMirrored() == false){
                allSteps << next << " (because of #)" << endl;
            }else{
                allSteps << prev << " (because of #)" << endl;
            }
            prevSteps.push_back('#');
            break;
        }
        case 'X':{
            changeDirection = true;
            if(ninjaData->getBreakerMode()){
                actualMap->setMap(ninjaData->getX()+x, ninjaData->getY()+y, ' ');
                ninjaData->setX(ninjaData->getX() + x);
                ninjaData->setY(ninjaData->getY() + y);
                allSteps << direction << " (destroyed X in breaker mode)" << endl;
                prevSteps.push_back('T');
            }else{
                ninjaData->changeDirection();
                allSteps << next << " (because of X)" << endl;
                prevSteps.push_back('X');
            }
            break;
        }
        case '$':{
            changeDirection = true;
            ninjaData->changeDirection();
            if(ninjaData->getIsMirrored() == false){
                allSteps << next << " (because of $)" << endl;
            }else{
                allSteps << prev << " (because of $)" << endl;
            }
            prevSteps.push_back('$');
            break;
        }
    }
}

void Engine::checkNextStep()
{
    shuriken = false;
    bool obstacle = false;
    if(ninjaData->getShurikens() > 0){//Throw Shuriken
        throwShuriken(obstacle);
    }

    move = false;
    if(shuriken == false){
        switch(ninjaData->getDirection()){
            case 3:{
                //west
                moveAction("WEST");
                break;
            }
            case 0:{
                //south
                moveAction("SOUTH");
                break;
            }
            case 1:{
                //east
                moveAction("EAST");
                break;
            }
            case 2:{
                //north
                moveAction("NORTH");
                break;
            }
        }
        changeDirection = false;
        switch(ninjaData->getDirection()){
            case 3:{
                //west
                changeMoveDirection("WEST","NORTH","SOUTH");
                break;
            }
            case 0:{
                //south
                changeMoveDirection("SOUTH","WEST","EAST");
                break;
            }
            case 1:{
                //east
                changeMoveDirection("EAST","SOUTH","NORTH");
                break;
            }
            case 2:{
                //north
                changeMoveDirection("NORTH","EAST","WEST");
                break;
            }
        }
    }
}

void Engine::drawMap()
{
    /*allSteps << endl;
    for(int i=0;i<actualMap->getH();i++){
        for(int j=0;j<actualMap->getW();j++){
            if(ninjaData->getX() == i && ninjaData->getY() == j){
                allSteps << '@';
            }else{
                allSteps << actualMap->getMap()[i][j];
            }
        }
        allSteps << endl;
    }
    allSteps << endl;*/

    cout << endl;
    for(int i=0;i<actualMap->getH();i++){
        for(int j=0;j<actualMap->getW();j++){
            if(ninjaData->getX() == i && ninjaData->getY() == j){
                cout << '@';
            }else{
                cout << actualMap->getMap()[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Engine::update()
{
    string answer;
    while(state == true){
        allSteps.str("");
        prevSteps.erase(prevSteps.begin(), prevSteps.end());
        while(isFinished == false){
            drawMap();//testing purposes
            checkNextStep();

            mapSolvable = loopDetection();

            if(mapSolvable == false){
                isFinished = true;
            }
        }
        if(mapSolvable == true){
            cout << "GAME OVER! Map solved! : " << endl;
            cout << allSteps.str() << endl;
        }else{
            cout << "LOOP (Map cannot be solved!)" << endl;
        }
        do{
            cout << "Do you wish to continue with next map? (y, n)" << endl;
            cin >> answer;
            if(toupper(answer[0]) == 'Y'){
                isFinished = false;
                mapSolvable = true;
                actualMapNum++;
                delete ninjaData;
                if(actualMapNum < mapLoader->getMapCount()){
                    //reinit some data
                    actualMap = mapLoader->getMap(actualMapNum);

                    ninjaData = new NinjaData(actualMap->getStartPoint()[0].x, actualMap->getStartPoint()[0].y);
                    //----------------
                }else{
                    cout << endl << "All maps are done!" << endl;
                    state = false;
                }
            }
            if(toupper(answer[0]) == 'N'){
                state = false;
            }
        }while(toupper(answer[0]) != 'Y' && toupper(answer[0]) != 'N');
    }
}
