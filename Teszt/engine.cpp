#include "engine.h"

Engine::Engine()
{
    nameGen = new NameGenerator();

    string ninjaName = nameGen->generateName();

    cout << "Your Ninja name is: " << ninjaName << endl;
    string answer = " ";
    while(answer[0] != '0' && answer[0] != '1'){
        cout << endl << "Do you wish to show map in every turn? (0, 1)  :  ";
        cin >> answer;
        showMap = atoi(answer.c_str());
    }

    mapLoader = new MapLoader();

    actualMap = mapLoader->getMap(actualMapNum);

    ninjaData = new NinjaData*[actualMap->getStartPoint().size()];
    for(int i=0;i<actualMap->getStartPoint().size();i++){
        ninjaData[i] = new NinjaData(actualMap->getStartPoint()[i].x, actualMap->getStartPoint()[i].y);
        if(i == 0){
            ninjaData[i]->setIsPlayer(true);
        }
    }

    move = false;

    shuriken = false;

    changeDirection = false;
}

Engine::~Engine()
{
    delete nameGen;
    delete mapLoader;
}

void Engine::setNewDirection(NinjaData * ninjaData, int x, int y)
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

void Engine::secretPaths(NinjaData * ninjaData)
{
    if(actualMap->getMap()[ninjaData->getX()][ninjaData->getY()] == 'F' ||
       actualMap->getMap()[ninjaData->getX()][ninjaData->getY()] == 'G' ||
       actualMap->getMap()[ninjaData->getX()][ninjaData->getY()] == 'H' ||
       actualMap->getMap()[ninjaData->getX()][ninjaData->getY()] == 'I' ||
       actualMap->getMap()[ninjaData->getX()][ninjaData->getY()] == 'J' ||
       actualMap->getMap()[ninjaData->getX()][ninjaData->getY()] == 'K' ||
       actualMap->getMap()[ninjaData->getX()][ninjaData->getY()] == 'L'){
        move = true;
        for(int i=0;i<actualMap->getPortals().size();i++){
            if((actualMap->getPortals()[i].position[0].x == ninjaData->getX() && actualMap->getPortals()[i].position[0].y == ninjaData->getY())){
                ninjaData->setX(actualMap->getPortals()[i].position[1].x);
                ninjaData->setY(actualMap->getPortals()[i].position[1].y);
                if(ninjaData->getIsPlayer()){
                    //allSteps << "Secret path used!" << endl;
                }
            }else if((actualMap->getPortals()[i].position[1].x == ninjaData->getX() && actualMap->getPortals()[i].position[1].y == ninjaData->getY())){
                ninjaData->setX(actualMap->getPortals()[i].position[0].x);
                ninjaData->setY(actualMap->getPortals()[i].position[0].y);
                if(ninjaData->getIsPlayer()){
                    //allSteps << "Secret path used!" << endl;
                }
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
                if(prevSteps[i] != prevSteps[i-j]){
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

void Engine::throwShuriken(NinjaData * ninjaData, bool &obstacle){
    if(ninjaData->getIsPlayer() == true){
        if(ninjaData->getIsMirrored() == false){
            for(int i=ninjaData->getX();i<actualMap->getH();i++){
                //cout << "11++" << endl;
                if(obstacle == false){
                    if(actualMap->getMap()[i][ninjaData->getY()] == '#' || actualMap->getMap()[i][ninjaData->getY()] == 'X'){
                        obstacle = true;
                    }
                    if(actualMap->getMap()[i][ninjaData->getY()] == '$' && ninjaData->getShurikens() > 0 && shuriken == false){
                        ninjaData->throwShuriken();
                        actualMap->setMap(i, ninjaData->getY(), ' ');
                        shuriken = true;
                        isFinished = true;
                        //allSteps << "THROW (throws a shuriken to destroy $)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
                }
            }
            obstacle = false;
            for(int i=ninjaData->getY();i<actualMap->getW();i++){
                //cout << "12++" << endl;
                if(obstacle == false){
                    if(actualMap->getMap()[ninjaData->getX()][i] == '#' || actualMap->getMap()[ninjaData->getX()][i] == 'X'){
                        obstacle = true;
                    }
                    if(actualMap->getMap()[ninjaData->getX()][i] == '$' && ninjaData->getShurikens() > 0 && shuriken == false){
                        ninjaData->throwShuriken();
                        actualMap->setMap(ninjaData->getX(), i, ' ');
                        shuriken = true;
                        isFinished = true;
                        //allSteps << "THROW (throws a shuriken to destroy $)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
                }
            }
            obstacle = false;
            for(int i=ninjaData->getX();i>0;i--){
                //cout << "13--" << endl;
                if(obstacle == false){
                    if(actualMap->getMap()[i][ninjaData->getY()] == '#' || actualMap->getMap()[i][ninjaData->getY()] == 'X'){
                        obstacle = true;
                    }
                    if(actualMap->getMap()[i][ninjaData->getY()] == '$' && ninjaData->getShurikens() > 0 && shuriken == false){
                        ninjaData->throwShuriken();
                        actualMap->setMap(i, ninjaData->getY(), ' ');
                        shuriken = true;
                        isFinished = true;
                        //allSteps << "THROW (throws a shuriken to destroy $)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
                }
            }
            obstacle = false;
            for(int i=ninjaData->getY();i>0;i--){
                //cout << "14--" << endl;
                if(obstacle == false){
                    if(actualMap->getMap()[ninjaData->getX()][i] == '#' || actualMap->getMap()[ninjaData->getX()][i] == 'X'){
                        obstacle = true;
                    }
                    if(actualMap->getMap()[ninjaData->getX()][i] == '$' && ninjaData->getShurikens() > 0 && shuriken == false){
                        ninjaData->throwShuriken();
                        actualMap->setMap(ninjaData->getX(), i, ' ');
                        shuriken = true;
                        isFinished = true;
                        //allSteps << "THROW (throws a shuriken to destroy $)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
                }
            }
        }else{
            for(int i=ninjaData->getX();i<actualMap->getH();i++){
                //cout << "21++" << endl;
                if(obstacle == false){
                    if(actualMap->getMap()[i][ninjaData->getY()] == '#' || actualMap->getMap()[i][ninjaData->getY()] == 'X'){
                        obstacle = true;
                    }
                    if(actualMap->getMap()[i][ninjaData->getY()] == '$' && ninjaData->getShurikens() > 0 && shuriken == false){
                        ninjaData->throwShuriken();
                        actualMap->setMap(i, ninjaData->getY(), ' ');
                        shuriken = true;
                        isFinished = true;
                        //allSteps << "THROW (throws a shuriken to destroy $)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
                }
            }
            obstacle = false;
            for(int i=ninjaData->getY();i>0;i--){
                //cout << "22--" << endl;
                if(obstacle == false){
                    if(actualMap->getMap()[ninjaData->getX()][i] == '#' || actualMap->getMap()[ninjaData->getX()][i] == 'X'){
                        obstacle = true;
                    }
                    if(actualMap->getMap()[ninjaData->getX()][i] == '$' && ninjaData->getShurikens() > 0 && shuriken == false){
                        ninjaData->throwShuriken();
                        actualMap->setMap(ninjaData->getX(), i, ' ');
                        shuriken = true;
                        isFinished = true;
                        //allSteps << "THROW (throws a shuriken to destroy $)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
                }
            }
            obstacle = false;
            for(int i=ninjaData->getX();i>0;i--){
                //cout << "23--" << endl;
                if(obstacle == false){
                    if(actualMap->getMap()[i][ninjaData->getY()] == '#' || actualMap->getMap()[i][ninjaData->getY()] == 'X'){
                        obstacle = true;
                    }
                    if(actualMap->getMap()[i][ninjaData->getY()] == '$' && ninjaData->getShurikens() > 0 && shuriken == false){
                        ninjaData->throwShuriken();
                        actualMap->setMap(i, ninjaData->getY(), ' ');
                        shuriken = true;
                        isFinished = true;
                        //allSteps << "THROW (throws a shuriken to destroy $)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
                }
            }
            obstacle = false;
            for(int i=ninjaData->getY();i<actualMap->getW();i++){
                //cout << "24++" << endl;
                if(obstacle == false){
                    if(actualMap->getMap()[ninjaData->getX()][i] == '#' || actualMap->getMap()[ninjaData->getX()][i] == 'X'){
                        obstacle = true;
                    }
                    if(actualMap->getMap()[ninjaData->getX()][i] == '$' && ninjaData->getShurikens() > 0 && shuriken == false){
                        ninjaData->throwShuriken();
                        actualMap->setMap(ninjaData->getX(), i, ' ');
                        shuriken = true;
                        isFinished = true;
                        //allSteps << "THROW (throws a shuriken to destroy $)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
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
                    if(ninjaData->getIsPlayer() == true){
                        //allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
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
                    if(ninjaData->getIsPlayer() == true){
                        //allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
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
                    if(ninjaData->getIsPlayer() == true){
                        //allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
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
                    if(ninjaData->getIsPlayer() == true){
                        //allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
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
                    if(ninjaData->getIsPlayer() == true){
                        //allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
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
                    if(ninjaData->getIsPlayer() == true){
                        //allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
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
                    if(ninjaData->getIsPlayer() == true){
                        //allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
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
                    if(ninjaData->getIsPlayer() == true){
                        //allSteps << "THROW (throws a shuriken to destroy X)" << endl;
                        allSteps << "THROW" << endl;
                        prevSteps.push_back('T');
                    }
                }
            }
        }
    }
}

void Engine::moveAction(NinjaData * ninjaData, string direction){
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
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case ' ':{
            move = true;
            //actualMap->setMap(ninjaData->getX(), ninjaData->getY(), ' ');
            ninjaData->setX(ninjaData->getX() + x);
            ninjaData->setY(ninjaData->getY() + y);
            //actualMap->setMap(ninjaData->getX(), ninjaData->getY(), '@');
            //allSteps << direction << " (move)" << endl;
            if(ninjaData->getIsPlayer()){
                prevSteps.push_back(direction[0]);
            }
            ninjaData->setLastStep(direction[0]);
            break;
        }
        case 'M':{
            move = true;
            ninjaData->setX(ninjaData->getX() + x);
            ninjaData->setY(ninjaData->getY() + y);
            ninjaData->setIsMirrored(!(ninjaData->getIsMirrored()));
            //allSteps << direction << " (move, after that mirrored priority in movement)" << endl;
            if(ninjaData->getIsPlayer()){
                prevSteps.push_back('M');
            }
            ninjaData->setLastStep('M');
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
            //allSteps << direction << " (move, after that collected a shuriken)" << endl;
            if(ninjaData->getIsPlayer()){
                prevSteps.push_back('*');
            }
            ninjaData->setLastStep('*');
            break;
        }
        case 'B':{
            move = true;
            ninjaData->setX(ninjaData->getX() + x);
            ninjaData->setY(ninjaData->getY() + y);
            ninjaData->setBreakerMode(!(ninjaData->getBreakerMode()));
            if(ninjaData->getBreakerMode() == true){
                //allSteps << direction << " (move, after that entered into breaker mode)" << endl;
            }else{
                //allSteps << direction << " (move, after that moved out of breaker mode)" << endl;
            }
            if(ninjaData->getIsPlayer()){
                prevSteps.push_back('B');
            }
            ninjaData->setLastStep('B');
            break;
        }
    }

    if(move != true){
        setNewDirection(ninjaData, x,y);
    }

    if(ninjaData->getIsPlayer() == true && move == true && shuriken == false){
        allSteps << direction << endl;
    }

    secretPaths(ninjaData);
}

void Engine::changeMoveDirection(NinjaData * ninjaData, string direction, string prev, string next){
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
                //allSteps << next << " (because of #)" << endl;
            }else{
                //allSteps << prev << " (because of #)" << endl;
            }
            if(ninjaData->getIsPlayer()){
                prevSteps.push_back('#');
            }
            break;
        }
        case 'X':{
            changeDirection = true;
            if(ninjaData->getBreakerMode()){
                actualMap->setMap(ninjaData->getX()+x, ninjaData->getY()+y, ' ');
                ninjaData->setX(ninjaData->getX() + x);
                ninjaData->setY(ninjaData->getY() + y);
                //allSteps << direction << " (destroyed X in breaker mode)" << endl;
                if(ninjaData->getIsPlayer()){
                    prevSteps.push_back('T');
                }
            }else{
                ninjaData->changeDirection();
                //allSteps << next << " (because of X)" << endl;
                if(ninjaData->getIsPlayer()){
                    prevSteps.push_back('X');
                }
            }
            break;
        }
        case '$':{
            changeDirection = true;
            if(ninjaData->getIsPlayer()){
                if(ninjaData->getBreakerMode()){
                    isFinished = true;
                }
            }
            ninjaData->changeDirection();
            if(ninjaData->getIsMirrored() == false){
                //allSteps << next << " (because of $)" << endl;
            }else{
                //allSteps << prev << " (because of $)" << endl;
            }
            if(ninjaData->getIsPlayer()){
                prevSteps.push_back('$');
            }
            break;
        }
    }
}

int Engine::compareStrength(int first, int second){
    if(first < second){
        return 2;
    }else if(first > second){
        return 1;
    }else{// first == second
        return 0;
    }
}

void Engine::checkForNinjaFight(){
    //check if battles available--------------------
    int map[actualMap->getH()][actualMap->getW()];

    for(int i=0;i<actualMap->getH();i++){
        for(int j=0;j<actualMap->getW();j++){
            map[i][j] = 0;
            for(int k=0;k<actualMap->getStartPoint().size();k++){
                if(ninjaData[k]->getX() == i && ninjaData[k]->getY() == j){
                    map[i][j]++;
                }
            }
            if(map[i][j] > 1){
                int strongestNinjaID = -1;
                for(int k=0;k<actualMap->getStartPoint().size();k++){
                    if(ninjaData[k]->getX() == i && ninjaData[k]->getY() == j && ninjaData[k]->getAlive() == true){
                        if(ninjaData[k]->getLastStep() == '*'){
                            ninjaData[k]->throwShuriken();
                            ninjaData[k]->setLastStep(' ');
                            actualMap->setMap(i, j, '*');
                        }
                        if(strongestNinjaID == -1){
                            strongestNinjaID = k;
                        }else{
                            int cmp = compareStrength(ninjaData[strongestNinjaID]->calcStrength(), ninjaData[k]->calcStrength());
                            if(cmp == 2){
                                ninjaData[strongestNinjaID]->setAlive(false);
                                strongestNinjaID = k;
                                ninjaData[k]->setIsFight(true);
                            }
                            if(cmp == 1){
                                ninjaData[k]->setAlive(false);
                                ninjaData[strongestNinjaID]->setIsFight(true);
                            }
                            if(cmp == 0){
                                if(ninjaData[k]->calcStrength() == 0){
                                    ninjaData[k]->setAlive(false);
                                    ninjaData[strongestNinjaID]->setAlive(false);
                                }
                                if(ninjaData[k]->calcStrength() == 1){
                                    ninjaData[strongestNinjaID]->setIsFight(true);
                                    ninjaData[k]->setIsFight(true);
                                }
                                if(ninjaData[k]->calcStrength() == 2){
                                    ninjaData[k]->setAlive(false);
                                    ninjaData[strongestNinjaID]->setAlive(false);
                                }
                                if(ninjaData[k]->calcStrength() == 3){
                                    ninjaData[strongestNinjaID]->setIsFight(true);
                                    ninjaData[k]->setIsFight(true);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //----------------------------------------------
    for(int k=0;k<actualMap->getStartPoint().size();k++){//reduce alive ninjas shuriken count by one
        if(ninjaData[k]->getAlive() == true && ninjaData[k]->getIsFight() == true && ninjaData[k]->getShurikens() > 0){
            ninjaData[k]->throwShuriken();
        }
    }
}

void Engine::checkNextStep(NinjaData * ninjaData)
{
    shuriken = false;
    bool obstacle = false;
    if(ninjaData->getShurikens() > 0){//Throw Shuriken
        throwShuriken(ninjaData, obstacle);
    }

    move = false;
    if(shuriken == false){
        changeDirection = true;
        while(changeDirection == true){//change direction to make moving possible
            changeDirection = false;
            switch(ninjaData->getDirection()){
                case 3:{
                    //west
                    changeMoveDirection(ninjaData, "WEST","NORTH","SOUTH");
                    break;
                }
                case 0:{
                    //south
                    changeMoveDirection(ninjaData, "SOUTH","WEST","EAST");
                    break;
                }
                case 1:{
                    //east
                    changeMoveDirection(ninjaData, "EAST","SOUTH","NORTH");
                    break;
                }
                case 2:{
                    //north
                    changeMoveDirection(ninjaData, "NORTH","EAST","WEST");
                    break;
                }
            }
        }
        if(isFinished == false){
            switch(ninjaData->getDirection()){
                case 3:{
                    //west
                    moveAction(ninjaData, "WEST");
                    break;
                }
                case 0:{
                    //south
                    moveAction(ninjaData, "SOUTH");
                    break;
                }
                case 1:{
                    //east
                    moveAction(ninjaData, "EAST");
                    break;
                }
                case 2:{
                    //north
                    moveAction(ninjaData, "NORTH");
                    break;
                }
            }
        }
    }
}

void Engine::ninjaKill(NinjaData * ninjaData, int i, int j){
    if(ninjaData->getX() == i && ninjaData->getY() == j){
        ninjaData->setAlive(false);
    }
}

void Engine::detonate(int ID){
    actualMap->setBombTimer(ID, 0);

    bool obstacle = false;
    int stepCount = 0;
    //cout << "1" << endl;
    for(int k = actualMap->getBombs()[ID].x; k < actualMap->getH() && stepCount <= BOMBRANGE && obstacle != true; k++){
        if(actualMap->getMap()[k][actualMap->getBombs()[ID].y] == '#'){
            obstacle = true;
        }
        if(actualMap->getMap()[k][actualMap->getBombs()[ID].y] == 'X' || actualMap->getMap()[k][actualMap->getBombs()[ID].y] == '*'){
            actualMap->setMap(k, actualMap->getBombs()[ID].y, ' ');
        }
        for(int i=0;i<actualMap->getStartPoint().size();i++){
            ninjaKill(ninjaData[i], k, actualMap->getBombs()[ID].y);
        }
        earlyExplode(k, actualMap->getBombs()[ID].y, ID);
        stepCount++;
    }
    obstacle = false;
    stepCount = 0;
    //cout << "2" << endl;
    for(int k = actualMap->getBombs()[ID].x; k > 0 && stepCount <= BOMBRANGE && obstacle != true; k--){
        if(actualMap->getMap()[k][actualMap->getBombs()[ID].y] == '#'){
            obstacle = true;
        }
        if(actualMap->getMap()[k][actualMap->getBombs()[ID].y] == 'X' || actualMap->getMap()[k][actualMap->getBombs()[ID].y] == '*'){
            actualMap->setMap(k, actualMap->getBombs()[ID].y, ' ');
        }
        for(int i=0;i<actualMap->getStartPoint().size();i++){
            ninjaKill(ninjaData[i], k, actualMap->getBombs()[ID].y);
        }
        earlyExplode(k, actualMap->getBombs()[ID].y, ID);
        stepCount++;
    }
    obstacle = false;
    stepCount = 0;
    //cout << "3" << endl;
    for(int k = actualMap->getBombs()[ID].y; k < actualMap->getW() && stepCount <= BOMBRANGE && obstacle != true; k++){
        if(actualMap->getMap()[actualMap->getBombs()[ID].x][k] == '#'){
            obstacle = true;
        }
        if(actualMap->getMap()[actualMap->getBombs()[ID].x][k] == 'X' || actualMap->getMap()[actualMap->getBombs()[ID].x][k] == '*'){
            actualMap->setMap(actualMap->getBombs()[ID].x, k, ' ');
        }
        for(int i=0;i<actualMap->getStartPoint().size();i++){
            ninjaKill(ninjaData[i], actualMap->getBombs()[ID].x, k);
        }
        earlyExplode(actualMap->getBombs()[ID].x, k, ID);
        stepCount++;
    }
    obstacle = false;
    stepCount = 0;
    //cout << "4" << endl;
    for(int k = actualMap->getBombs()[ID].y; k > 0 && stepCount <= BOMBRANGE && obstacle != true; k--){
        if(actualMap->getMap()[actualMap->getBombs()[ID].x][k] == '#'){
            obstacle = true;
        }
        if(actualMap->getMap()[actualMap->getBombs()[ID].x][k] == 'X' || actualMap->getMap()[actualMap->getBombs()[ID].x][k] == '*'){
            actualMap->setMap(actualMap->getBombs()[ID].x, k, ' ');
        }
        for(int i=0;i<actualMap->getStartPoint().size();i++){
            ninjaKill(ninjaData[i], actualMap->getBombs()[ID].x, k);
        }
        earlyExplode(actualMap->getBombs()[ID].x, k, ID);
        stepCount++;
    }
    actualMap->setMap(actualMap->getBombs()[ID].x, actualMap->getBombs()[ID].y, to_string(actualMap->getBombs()[ID].timer)[0]);
}

void Engine::earlyExplode(int x, int y, int actualBombID)
{
    if(actualMap->getMap()[x][y] == '0' ||
       actualMap->getMap()[x][y] == '1' ||
       actualMap->getMap()[x][y] == '2' ||
       actualMap->getMap()[x][y] == '3' ||
       actualMap->getMap()[x][y] == '4' ||
       actualMap->getMap()[x][y] == '5' ||
       actualMap->getMap()[x][y] == '6' ||
       actualMap->getMap()[x][y] == '7' ||
       actualMap->getMap()[x][y] == '8' ||
       actualMap->getMap()[x][y] == '9'){
        //cout << "earlyExplode" << endl;
        for(int i=0;i<actualMap->getBombs().size();i++){
            if(i != actualBombID && actualMap->getBombs()[i].timer > 0 && actualMap->getBombs()[i].x == x && actualMap->getBombs()[i].y == y){
                detonate(i);
                actualMap->setBombDestroyed(i, true);
            }
        }
    }
}

void Engine::checkBombs()
{
    for(int i=0;i<actualMap->getBombs().size();i++){
        if(actualMap->getBombs()[i].isActive == true && actualMap->getBombs()[i].isDestroyed == false){
            if(actualMap->getBombs()[i].timer > 1){
                //cout << "bomb: " << i << endl;
                actualMap->setBombTimer(i, actualMap->getBombs()[i].timer - 1);
                actualMap->setMap(actualMap->getBombs()[i].x, actualMap->getBombs()[i].y, to_string(actualMap->getBombs()[i].timer)[0]);
            }else{
                //cout << "bomb: " << i << " detonate" << endl;
                detonate(i);
                actualMap->setBombDestroyed(i, true);
            }
        }
        for(int k=0;k<actualMap->getStartPoint().size();k++){
            if((abs(actualMap->getBombs()[i].x - ninjaData[k]->getX()) < 2 && actualMap->getBombs()[i].y == ninjaData[k]->getY()) ||
               (abs(actualMap->getBombs()[i].y - ninjaData[k]->getY()) < 2 && actualMap->getBombs()[i].x == ninjaData[k]->getX())){
                actualMap->setBombActive(i, true);
            }
        }
    }
}

void Engine::drawMap()
{
    cout << endl;
    for(int i=0;i<actualMap->getH();i++){
        for(int j=0;j<actualMap->getW();j++){
            bool isDraw = false;
            for(int k=0;k<actualMap->getStartPoint().size();k++){
                if(ninjaData[k]->getX() == i && ninjaData[k]->getY() == j){
                    if(isDraw == false){
                        if(ninjaData[k]->getAlive()){
                            cout << '@';
                        }else{
                            cout << '!';
                        }
                        isDraw = true;
                    }
                }
            }
            if(isDraw == false){
                cout << actualMap->getMap()[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Engine::putUpShuriken()
{
    for(int i=0;i<actualMap->getStartPoint().size();i++){
        if(ninjaData[i]->getAlive() == true && actualMap->getMap()[ninjaData[i]->getX()][ninjaData[i]->getY()] == '*' && ninjaData[i]->getIsFight() == false){
            actualMap->setMap(ninjaData[i]->getX(), ninjaData[i]->getY(), ' ');
            ninjaData[i]->addShuriken();
        }
    }
}

void Engine::update()
{
    string answer;
    while(state == true){
        allSteps.str("");
        prevSteps.erase(prevSteps.begin(), prevSteps.end());
        while(isFinished == false){
            checkBombs();//bonus 1

            if(showMap){
                drawMap();//testing purposes
            }

            checkForNinjaFight();//bonus 2

            putUpShuriken();

            for(int i=0;i<actualMap->getStartPoint().size();i++){//bonus 2
                if(ninjaData[i]->getAlive() == true && ninjaData[i]->getIsFight() == false){
                    checkNextStep(ninjaData[i]);
                }
                ninjaData[i]->setIsFight(false);
            }

            if(prevSteps.size() > 0){
                mapSolvable = loopDetection();
            }

            if(mapSolvable == false){
                isFinished = true;
            }
            if(ninjaData[0]->getAlive() == false){
                isFinished = true;
            }
        }
        if(mapSolvable == true){
            if(ninjaData[0]->getAlive() == true){
                cout << allSteps.str();
                cout << "GAME OVER!" << endl;
            }else{
                cout << "GAME OVER! Ninja died!" << endl;
            }
        }else{
            cout << "LOOP" << endl;
        }
        do{
            cout << "Do you wish to continue with next map? (y, n)" << endl;
            cin >> answer;
            if(toupper(answer[0]) == 'Y'){
                isFinished = false;
                mapSolvable = true;
                actualMapNum++;
                for(int i=0;i<actualMap->getStartPoint().size();i++){
                    delete ninjaData[i];
                }
                delete [] ninjaData;
                if(actualMapNum < mapLoader->getMapCount()){
                    //reinit some data
                    actualMap = mapLoader->getMap(actualMapNum);

                    ninjaData = new NinjaData*[actualMap->getStartPoint().size()];
                    for(int i=0;i<actualMap->getStartPoint().size();i++){
                        ninjaData[i] = new NinjaData(actualMap->getStartPoint()[i].x, actualMap->getStartPoint()[i].y);
                        if(i == 0){
                            ninjaData[i]->setIsPlayer(true);
                        }
                    }
                    //----------------
                }else{
                    cout << endl << "All maps are done!" << endl;
                    state = false;
                }
            }
            if(toupper(answer[0]) == 'N'){
                for(int i=0;i<actualMap->getStartPoint().size();i++){
                    delete ninjaData[i];
                }
                delete [] ninjaData;
                state = false;
            }
        }while(toupper(answer[0]) != 'Y' && toupper(answer[0]) != 'N');
    }
}
