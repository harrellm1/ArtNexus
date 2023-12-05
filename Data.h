#ifndef ARTNEXUS_FINALPROJECT_DATA_H
#define ARTNEXUS_FINALPROJECT_DATA_H


#include<vector>
#include<sstream>
#include <unordered_map>
#include "ArtPiece.h"
using namespace std;

class Data{
private:
    vector<ArtPiece> allPieces;
    unordered_map<int,vector<pair<int,float>>> adjList;

public:
    Data();

    void writeToFile();
    string checkString(string temp, string defaultStr);
    void filterData();
    static float calcWeight(ArtPiece piece1, ArtPiece piece2);

};


#endif //ARTNEXUS_FINALPROJECT_DATA_H
