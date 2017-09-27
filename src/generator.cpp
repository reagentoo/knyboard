#include "knyfile.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cassert>


using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 5) {
        cerr << "Insufficient number of arguments";
        return 1;
    }

    string name = argv[1];
    string mapFileName = argv[2];
    string hppFileName = argv[3];
    string cppFileName = argv[4];

    KnyFile kf(name);

    ifstream mapFile(mapFileName);
    if (!mapFile.is_open()) {
        cerr << "Unable to open map file";
        return 1;
    }

    kf.read(mapFile);
    mapFile.close();

    ofstream hppFile(hppFileName);
    if (!hppFile.is_open()) {
        cerr << "Unable to open pch h-file";
        return 1;
    }

    kf.generateHpp(hppFile);
    hppFile.close();

    ofstream cppFile(cppFileName);
    if (!cppFile.is_open()) {
        cerr << "Unable to open out cpp-file";
        return 1;
    }

    kf.generateCpp(cppFile);
    cppFile.close();

    return 0;
}
