#ifndef ARTNEXUS_FINALPROJECT_ARTNEXUS_H
#define ARTNEXUS_FINALPROJECT_ARTNEXUS_H

#include<unordered_map>
#include <queue>
#include<vector>
#include "ArtPiece.h"

using namespace std;

class ArtNexus {

private:
    //class containers
    vector<ArtPiece*> vertices;
    unordered_map<int,vector<pair<int,float>>> adjList;

    //containers for Dijkstra and Bellman Ford
    unordered_map<int, float> distances;
    unordered_map<int, int> predecessors;
    vector<float> distFinal;
    vector<int> predFinal;

    //helper functions for algorithms
    void dijkstraHelper(int source, int destination);
    void bellmanFordHelper(int source, int destination);

    //helper functions for printing paths
    void findPathDiksHelper(int destination);
    void findPathBellHelper(int destination);

public:
    //Constructor and Destructor
    ArtNexus();
    ~ArtNexus();

    //Algorithms
    void dijkstra(int source, int destination);
    void bellmanFord(int source, int destination);

    //Functions to print paths
    void findPathDiks(int destination);
    void findPathBell(int destination);

    //accessor function
    void getVertex(int id);
};



#endif //ARTNEXUS_FINALPROJECT_ARTNEXUS_H
