#include "namegenerator.h"

NameGenerator::NameGenerator()
{
    ifstream file;
    file.open("input/tags.list");

    while (file.good()){
        char x;
        string y;
        file >> x;
        file >> y;

        tags[x] = y;
    }

    file.close();
}

string NameGenerator::generateName()
{
    cout << "Type your name to generate your Ninja name (first, last): ";

    string name1, name1b;

    cin >> name1;
    cin >> name1b;

    stringstream name2;
    name2.str("");

    int c1 = 0;
    int c2 = 0;
    bool lastName = false;

    for(int i=0;i<name1.length();i++){//first name add to stringstream
        if(lastName == false && c1 < 3){
            if(c1 == 0){
                string newTag = tags[toupper(name1[i])];
                newTag[0] = toupper(newTag[0]);
                name2 << newTag;
            }else{
                name2 << tags[toupper(name1[i])];
            }

            c1++;
        }
        if(',' == name1[i]){//check for end of first name
            lastName = true;
        }
    }
    name2 << " ";
    for(int i=0;i<name1b.length();i++){//last name add to stringstream
        if(lastName == true && c2 < 4){
            if(c2 == 0){
                string newTag = tags[toupper(name1b[i])];
                newTag[0] = toupper(newTag[0]);
                name2 << newTag;
            }else{
                name2 << tags[toupper(name1b[i])];
            }

            c2++;
        }
    }

    return name2.str();
}
