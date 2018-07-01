#include "map.h"

Map::Map()
{

}

Map::Map(string filename)
{
    ifstream file;
    file.open(filename.c_str());

    string data;
    while(file.good()){
        getline(file, data);
        map.push_back(data);
        h++;
    }
    w = map[0].length();

    file.close();

    //test output
    cout << "w: " << w << endl;
    cout << "h: " << h << endl << endl;

    for(int i=0;i<h;i++){
        cout << map[i] << endl;
    }

    cout << endl;
}

void Map::findTokens()
{
    struct pos newPos;
    struct portalPos newPortalPos;
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            switch(map[i][j]){
            case '@':{
                newPos.x = i;
                newPos.y = j;
                startPoint.push_back(newPos);
                break;
            }
            case '$':{
                holySymbol.x = i;
                holySymbol.y = j;
                break;
            }
            case '#':{
                newPos.x = i;
                newPos.y = j;
                unbreakableWalls.push_back(newPos);
                break;
            }
            case 'X':{
                newPos.x = i;
                newPos.y = j;
                breakableWalls.push_back(newPos);
                break;
            }
            case 'F':{
                if(Fbool == false){
                    newPortalPos.position[0].x = i;
                    newPortalPos.position[0].y = j;
                    int count = 0;
                    for(int l=j;l<h;l++)
                    for(int k=0;k<w;k++){
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
                if(Gbool == false){
                    newPortalPos.position[0].x = i;
                    newPortalPos.position[0].y = j;
                    int count = 0;
                    for(int l=j;l<h;l++)
                    for(int k=0;k<w;k++){
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
                if(Hbool == false){
                    newPortalPos.position[0].x = i;
                    newPortalPos.position[0].y = j;
                    int count = 0;
                    for(int l=j;l<h;l++)
                    for(int k=0;k<w;k++){
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
                if(Ibool == false){
                    newPortalPos.position[0].x = i;
                    newPortalPos.position[0].y = j;
                    int count = 0;
                    for(int l=j;l<h;l++)
                    for(int k=0;k<w;k++){
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
                if(Jbool == false){
                    newPortalPos.position[0].x = i;
                    newPortalPos.position[0].y = j;
                    int count = 0;
                    for(int l=j;l<h;l++)
                    for(int k=0;k<w;k++){
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
                if(Kbool == false){
                    newPortalPos.position[0].x = i;
                    newPortalPos.position[0].y = j;
                    int count = 0;
                    for(int l=j;l<h;l++)
                    for(int k=0;k<w;k++){
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
                if(Lbool == false){
                    newPortalPos.position[0].x = i;
                    newPortalPos.position[0].y = j;
                    int count = 0;
                    for(int l=j;l<h;l++)
                    for(int k=0;k<w;k++){
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
            }
        }
    }
}
