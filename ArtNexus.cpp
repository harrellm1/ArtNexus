#include "ArtNexus.h"
#include "ArtPiece.h"

//Constructor
ArtNexus::ArtNexus() {
    ifstream inFile("C:\\Users\\ccstu\\CLionProjects\\ArtNexus_FinalProject\\allPiecesData.txt");

    string lineFromFile;

    //read in number of pieces in graph (i.e. number of vertices)
    getline(inFile,lineFromFile);
    int numPieces = stoi(lineFromFile);

    //read in and deserialize all ArtPieces and add them to the vector.
    for(int i = 0; i < numPieces; i++){
        auto* addedPiece = new ArtPiece();
        addedPiece->deserialize(inFile);
        vertices.push_back(addedPiece);
    }

    //read in adjacency list
    for(int i = 0; i < numPieces; i++){
        getline(inFile,lineFromFile);
        int vertexNeighborsSize = stoi(lineFromFile);

        if(vertexNeighborsSize == 0){
            getline(inFile,lineFromFile);
            int key = stoi(lineFromFile);
            adjList[key] = {};
            continue;
        }

        for(int j = 0; j <vertexNeighborsSize; j++ ){
            getline(inFile,lineFromFile,'|');
            int key = stoi(lineFromFile);

            getline(inFile,lineFromFile,'|');
            int neighbor = stoi(lineFromFile);

            getline(inFile,lineFromFile);
            float weight = stof(lineFromFile);

            adjList[key].emplace_back(make_pair(neighbor,weight));
        }
    }
}
ArtNexus::~ArtNexus() = default;

//helper functions
void ArtNexus::dijkstraHelper(int source, int destination) {
    //implement a minHeap to track minimum distance
    priority_queue<pair<float,int>,vector<pair<float,int>>,greater<>> minHeap;
    minHeap.push({0,source});
    for(int i = 0; i < 100200; i++){
        if(i != source){
            minHeap.push({float(INT_MAX), i});
        }
    }

    //track distances and predecessors of all vertices
    vector<float> dist (100200, float(INT_MAX));
    vector<int> pred(100200,-1);

    //initialize distance and predecessor of source
    dist[source] = 0;
    pred[source] = -1;

    while(!minHeap.empty()){//repeat until all nodes have been visited
        //minimum distance and its index
        float minWeight = minHeap.top().first;
        int minWeightIndex =  minHeap.top().second;

        //remove minimum distance
        minHeap.pop();

        //relax edges
        for(int i = 0; i < adjList[minWeightIndex].size(); i++){
            int neighborIndex = adjList[minWeightIndex][i].first;
            float neighborWeight = adjList[minWeightIndex][i].second;

            if(minWeight + neighborWeight < dist[neighborIndex]){
                dist[neighborIndex] = minWeight + neighborWeight;
                pred[neighborIndex] = minWeightIndex;
                minHeap.push({dist[neighborIndex],neighborIndex});
            }
        }
    }

    predFinal = pred;
    distFinal = dist;
}

void ArtNexus::bellmanFordHelper(int source, int destination) {
    distances[source] = 0;
    predecessors[source] = -1;

    for (int i= 0; i < vertices.size(); i++) {
        if (i != source) {
            distances[i] = float(INT_MAX);
            predecessors[i] = -1;
        }
    }

    float tempDist = 0.0;
    int count = 0;
    unordered_map<int, float> distancesTemp;
    for (int i =0 ; i < 100200; i++) {   //has to iterate over the number of vertices in the graph
        for (auto piece: adjList) {
            for (auto edge: piece.second) {
                tempDist = distances[piece.first] + edge.second;
                if (distances[piece.first] != INT_MAX && tempDist < distances[edge.first]) {
                    distances[edge.first] = tempDist;
                    predecessors[edge.first] = piece.first;
                }
            }
        }
        if (distancesTemp != distances) {
            distancesTemp = distances;
        }
        else {
            break;
        }
    }

    for (auto piece: adjList) {
        for (auto edge: piece.second) {
            tempDist = distances[piece.first] + edge.second;
            if (distances[piece.first] != INT_MAX && tempDist < distances[edge.first]) {
                cout << "Error: Negative Cycle Found";
            }
        }
    }
}

void ArtNexus::findPathDiksHelper(int destination) {
    vector<ArtPiece*> path;
    path.push_back(vertices[destination]);
    int p = predFinal[destination];
    while(p != -1){
        path.push_back(vertices[p]);
        p = predFinal[p];
    }

    if(path.size() == 1){
        cout<<"No connections found" <<endl;
    }

    else {
        cout << "shortest path: " << distFinal[destination] << "\n";
        for (int i = path.size() - 1; i >= 0; i--) {
            path[i]->printArtPiece();
            cout<<endl;
        }

    }


}

void ArtNexus::findPathBellHelper(int destination) {
    vector<ArtPiece *> path;
    path.push_back(vertices[destination]);
    int p = predecessors[destination];
    while (p != -1) {
        path.push_back(vertices[p]);
        p = predecessors[p];
    }
    if (path.size() == 1) {
        cout << "No connections found" << endl;
    } else {
        cout << "shortest path: " << distances[destination] << "\n";
        for (int i = path.size() - 1; i >= 0; i--) {
            path[i]->printArtPiece();
            cout<<endl;
        }
    }
}

//Class functions
void ArtNexus::dijkstra(int source, int destination) {
    dijkstraHelper(source, destination);
}

void ArtNexus::bellmanFord(int source, int destination) {
    bellmanFordHelper(source, destination);
}

void ArtNexus::findPathDiks(int destination) {
    findPathDiksHelper(destination);
}

void ArtNexus::findPathBell(int destination) {
    findPathBellHelper(destination);
}

//accessor function
void ArtNexus::getVertex(int id){
    vertices[id]->printArtPiece();
}
