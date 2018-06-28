#ifndef NAMEGENERATOR_H
#define NAMEGENERATOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

class NameGenerator
{
private:
    map<char, string> tags;
public:
    NameGenerator();

    string generateName();
};

#endif // NAMEGENERATOR_H
