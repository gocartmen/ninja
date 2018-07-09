#include "map.h"

vector<Map::pos> Map::getStartPoint()
{
    return startPoint;
}

vector<Map::portalPos> Map::getPortals() const
{
    return portals;
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
    portals.reserve(200);

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
                case 'F':{
                    //cout << "F" << endl;
                    if(Fbool == false){
                        int count = 0;
                        for(int k=0;k<h;k++){
                            for(int l=0;l<w;l++){
                                if(map[k][l] == 'F'){
                                    newPortalPos.position[count].x = k;
                                    newPortalPos.position[count].y = l;
                                    count++;
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
                        int count = 0;
                        for(int k=0;k<h;k++){
                            for(int l=0;l<w;l++){
                                if(map[k][l] == 'G'){
                                    newPortalPos.position[count].x = k;
                                    newPortalPos.position[count].y = l;
                                    count++;
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
                        int count = 0;
                        for(int k=0;k<h;k++){
                            for(int l=0;l<w;l++){
                                if(map[k][l] == 'H'){
                                    newPortalPos.position[count].x = k;
                                    newPortalPos.position[count].y = l;
                                    count++;
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
                        int count = 0;
                        for(int k=0;k<h;k++){
                            for(int l=0;l<w;l++){
                                if(map[k][l] == 'I'){
                                    newPortalPos.position[count].x = k;
                                    newPortalPos.position[count].y = l;
                                    count++;
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
                        int count = 0;
                        for(int k=0;k<h;k++){
                            for(int l=0;l<w;l++){
                                if(map[k][l] == 'J'){
                                    newPortalPos.position[count].x = k;
                                    newPortalPos.position[count].y = l;
                                    count++;
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
                        int count = 0;
                        for(int k=0;k<h;k++){
                            for(int l=0;l<w;l++){
                                if(map[k][l] == 'K'){
                                    newPortalPos.position[count].x = k;
                                    newPortalPos.position[count].y = l;
                                    count++;
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
                        int count = 0;
                        for(int k=0;k<h;k++){
                            for(int l=0;l<w;l++){
                                if(map[k][l] == 'L'){
                                    newPortalPos.position[count].x = k;
                                    newPortalPos.position[count].y = l;
                                    count++;
                                }
                            }
                        }
                        portals.push_back(newPortalPos);
                        Lbool = true;
                    }
                    break;
                }
            }
        }
    }
}
