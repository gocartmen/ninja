#include "map.h"

vector<Map::pos> Map::getStartPoint()
{
    return startPoint;
}

Map::pos Map::getHolySymbol() const
{
    return holySymbol;
}

vector<Map::pos> Map::getShurikens() const
{
    return shurikens;
}

vector<Map::portalPos> Map::getPortals() const
{
    return portals;
}

vector<Map::pos> Map::getBreakableWalls() const
{
    return breakableWalls;
}

vector<Map::pos> Map::getUnbreakableWalls() const
{
    return unbreakableWalls;
}

int Map::getW() const
{
    return w;
}

int Map::getH() const
{
    return h;
}

vector<string> Map::getMap() const
{
    return map;
}

void Map::setMap(int x, int y, char value)
{
    map[x][y] = value;
}

Map::Map()
{

}

Map::Map(string filename)
{
    unbreakableWalls.reserve(400);
    breakableWalls.reserve(400);
    portals.reserve(200);
    shurikens.reserve(400);

    ifstream file;
    file.open(filename.c_str());

    string data;
    while(file.good()){
        getline(file, data);
        map.push_back(data);
        h++;
    }
    h--;//it gets one extra because of reading file
    w = map[0].length();

    file.close();

    //test output
    /*cout << "w: " << w << endl;
    cout << "h: " << h << endl << endl;

    for(int i=0;i<h;i++){
        cout << map[i] << endl;
    }

    cout << endl;*/
}

void Map::findTokens()
{
    struct pos newPos;
    struct portalPos newPortalPos;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            //cout << "switch : ";
            switch(map[i][j]){
                case '@':{
                    //cout << "@" << endl;
                    newPos.x = i;
                    newPos.y = j;
                    map[i][j] = ' ';
                    startPoint.push_back(newPos);
                    break;
                }
                case '$':{
                    //cout << "$" << endl;
                    holySymbol.x = i;
                    holySymbol.y = j;
                    break;
                }
                case '#':{
                    //cout << "#" << endl;
                    newPos.x = i;
                    newPos.y = j;
                    unbreakableWalls.push_back(newPos);
                    break;
                }
                case 'X':{
                    //cout << "X" << endl;
                    newPos.x = i;
                    newPos.y = j;
                    breakableWalls.push_back(newPos);
                    break;
                }
                case 'F':{
                    //cout << "F" << endl;
                    if(Fbool == false){
                        newPortalPos.position[0].x = i;
                        newPortalPos.position[0].y = j;
                        int count = 0;
                        for(int l=i;l<w;l++)
                        for(int k=0;k<h;k++){
                            if(map[k][l] == 'F'){
                                count++;
                                if(count == 2){
                                    newPortalPos.position[1].x = k;
                                    newPortalPos.position[1].y = l;
                                }
                            }
                        }
                        portals.push_back(newPortalPos);
                        Fbool = true;
                    }
                    break;
                }
                case 'G':{
                    //cout << "G" << endl;
                    if(Gbool == false){
                        newPortalPos.position[0].x = i;
                        newPortalPos.position[0].y = j;
                        int count = 0;
                        for(int l=i;l<w;l++)
                        for(int k=0;k<h;k++){
                            if(map[k][l] == 'G'){
                                count++;
                                if(count == 2){
                                    newPortalPos.position[1].x = k;
                                    newPortalPos.position[1].y = l;
                                }
                            }
                        }
                        portals.push_back(newPortalPos);
                        Gbool = true;
                    }
                    break;
                }
                case 'H':{
                    //cout << "H" << endl;
                    if(Hbool == false){
                        newPortalPos.position[0].x = i;
                        newPortalPos.position[0].y = j;
                        int count = 0;
                        for(int l=i;l<w;l++)
                        for(int k=0;k<h;k++){
                            if(map[k][l] == 'H'){
                                count++;
                                if(count == 2){
                                    newPortalPos.position[1].x = k;
                                    newPortalPos.position[1].y = l;
                                }
                            }
                        }
                        portals.push_back(newPortalPos);
                        Hbool = true;
                    }
                    break;
                }
                case 'I':{
                    //cout << "I" << endl;
                    if(Ibool == false){
                        newPortalPos.position[0].x = i;
                        newPortalPos.position[0].y = j;
                        int count = 0;
                        for(int l=i;l<w;l++)
                        for(int k=0;k<h;k++){
                            if(map[k][l] == 'I'){
                                count++;
                                if(count == 2){
                                    newPortalPos.position[1].x = k;
                                    newPortalPos.position[1].y = l;
                                }
                            }
                        }
                        portals.push_back(newPortalPos);
                        Ibool = true;
                    }
                    break;
                }
                case 'J':{
                    //cout << "J" << endl;
                    if(Jbool == false){
                        newPortalPos.position[0].x = i;
                        newPortalPos.position[0].y = j;
                        int count = 0;
                        for(int l=i;l<w;l++)
                        for(int k=0;k<h;k++){
                            if(map[k][l] == 'J'){
                                count++;
                                if(count == 2){
                                    newPortalPos.position[1].x = k;
                                    newPortalPos.position[1].y = l;
                                }
                            }
                        }
                        portals.push_back(newPortalPos);
                        Jbool = true;
                    }
                    break;
                }
                case 'K':{
                    //cout << "K" << endl;
                    if(Kbool == false){
                        newPortalPos.position[0].x = i;
                        newPortalPos.position[0].y = j;
                        int count = 0;
                        for(int l=i;l<w;l++)
                        for(int k=0;k<h;k++){
                            if(map[k][l] == 'K'){
                                count++;
                                if(count == 2){
                                    newPortalPos.position[1].x = k;
                                    newPortalPos.position[1].y = l;
                                }
                            }
                        }
                        portals.push_back(newPortalPos);
                        Kbool = true;
                    }
                    break;
                }
                case 'L':{
                    //cout << "L" << endl;
                    if(Lbool == false){
                        newPortalPos.position[0].x = i;
                        newPortalPos.position[0].y = j;
                        int count = 0;
                        for(int l=i;l<w;l++)
                        for(int k=0;k<h;k++){
                            if(map[k][l] == 'L'){
                                count++;
                                if(count == 2){
                                    newPortalPos.position[1].x = k;
                                    newPortalPos.position[1].y = l;
                                }
                            }
                        }
                        portals.push_back(newPortalPos);
                        Lbool = true;
                    }
                    break;
                }
                case '*':{
                    //cout << "*" << endl;
                    newPos.x = i;
                    newPos.y = j;
                    shurikens.push_back(newPos);
                    break;
                }
            }
        }
    }
}
