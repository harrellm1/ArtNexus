#include "Data.h"

string Data::checkString(string temp, string defaultStr){
    if (temp.empty()) {
        return defaultStr;
    }
    return temp;
}

Data::Data() {
    ifstream file;
    file.open("C:\\Users\\ccstu\\CLionProjects\\ArtNexus_FinalProject\\METData.csv");
    if (file.is_open()) {
        cout<<"open";
        string line;
        string first;
        getline(file, line);
        getline(file, line);

        for (int i=0; i < 100200; i++) {
            ArtPiece addedPiece;

            getline(file, first);
            string temp;
            stringstream ss(first);

            //For Title
            for (int j = 0; j < 2; j++) {
                getline(ss, temp, ',');
            }
            addedPiece.pieceName = checkString(temp, addedPiece.pieceName);

            //For culture
            getline(ss, temp, ',');
            addedPiece.pieceCulture = checkString(temp, addedPiece.pieceCulture);

            //For artist's name
            getline(ss, temp, ',');
            addedPiece.artistName = checkString(temp, addedPiece.artistName);

            //For Date
            getline(ss, temp, ',');
            addedPiece.dateCompleted = checkString(temp, addedPiece.dateCompleted);

            //For medium
            getline(ss, temp, ',');
            addedPiece.pieceMedium = checkString(temp, addedPiece.pieceMedium);

            //For country
            getline(ss, temp, ',');
            addedPiece.pieceCountry = checkString(temp, addedPiece.pieceCountry);

            //For image link
            getline(ss, temp, ',');
            addedPiece.pieceImageLink = checkString(temp, addedPiece.pieceImageLink);

            allPieces.push_back(addedPiece);
            adjList[i] = {};
        }
    }
    file.close();

}


float Data::calcWeight(ArtPiece piece1, ArtPiece piece2) {
    /*WEIGHT CALCULATION
     * Since Dijkstra's and Bellman Ford find the path with the shortest weight,
     * the more similarities between two pieces, the SMALLER the value of the
     * edge between them.
     *
     * Weight Attributes
     * same artist = -0.25
     * ONLY ONE DEDUCTION FOR DATE SIMILARITY; MAXIMUM WEIGHT DEDUCTION IS CHOSEN
     *      same date (year) = -0.25
     *      dates less than or equal to one year apart = -0.2
     *      dates less than or equal to five years apart = -0.1
     *      dates less than or equal to ten years apart = -0.05
     * same culture = -0.25
     * same country = -0.25
     *
     * The minimum weight between two pieces is 0
     * no self loops are allowed
     */

    float weight = 1.0;

    if(piece1.artistName != "Anonymous" && piece2.artistName != "Anonymous"){
        if(piece1.artistName == piece2.artistName){
            weight -= 0.25;
        }
    }

    if(piece1.dateCompleted != "Unknown" && piece2.dateCompleted != "Unknown") {
        if(abs(stoi(piece1.dateCompleted) - stoi (piece2.dateCompleted)) == 0){
            weight -= 0.25;
        }

        else if(abs(stoi(piece1.dateCompleted) - stoi (piece2.dateCompleted)) <= 1){
            weight -= 0.2;
        }

        else if(abs(stoi(piece1.dateCompleted) - stoi (piece2.dateCompleted)) <= 5){
            weight -= 0.1;
        }

        else if(abs(stoi(piece1.dateCompleted) - stoi (piece2.dateCompleted)) <= 10){
            weight -= 0.05;
        }
    }

    if(piece1.pieceCountry != "Unknown" && piece2.pieceCountry != "Unknown"){
        if(piece1.pieceCountry == piece2.pieceCountry){
            weight -= 0.25;
        }
    }

    if(piece1.pieceCulture != "Unknown"  && piece2.pieceCulture != "Unknown"){
        if(piece1.pieceCulture == piece2.pieceCulture){
            weight -= 0.25;
        }
    }

    return weight;
}

void Data::filterData() {
    for(int i = 0 ; i < allPieces.size(); i++){
        for(int j = 0; j < allPieces.size(); j++){
            if(i != j){ //not the same piece (no self loops)
                float num = calcWeight(allPieces[i], allPieces[j]);
                if (num != 1.0) { //there is some degree of similarity
                    if(adjList[i].size() == 4){ //keep the four edges with the lowest value (i.e. most similarity) to i (K nearest neighbors)
                        int minSimilarityIndex = 0;
                        for(int k = 0; k < adjList[i].size(); k++){
                            if (adjList[i][k] > adjList[i][minSimilarityIndex]){
                                minSimilarityIndex = k;
                            }
                        }

                        if (num < adjList[i][minSimilarityIndex].second){ //if piece j is more related to the piece than the piece at minSimilarIndex, replace the edge
                            adjList[i][minSimilarityIndex].first = j;
                            adjList[i][minSimilarityIndex].second = num;
                        }
                    }

                    else{ //there are fewer than four pieces currently connected to piece i
                        adjList[i].emplace_back(make_pair(j, num));
                    }
                }
            }
        }
    }
}

void Data::writeToFile() {
    //Because the calculations take extremely long to perform, the results are written out to a file once.
    //The ArtNexus is run from that file
    //write out graph to file including all the pieces and the adjacency list

    ofstream file(".../allPiecesData.txt");

    int numNodes = allPieces.size();
    file << numNodes<< endl;

    //write all art pieces to file
    for(auto i: allPieces){
        i.serialize(file);
    }


    //write adjacency list to file
    for(int i = 0; i < allPieces.size(); i++){
        int vertexAdjListSize = adjList[i].size();
        if(vertexAdjListSize == 0){
            file<<vertexAdjListSize<<endl;
            file <<i<<endl;
            continue;
        }

        file<<vertexAdjListSize<<endl;

        for(int j = 0; j < adjList[i].size(); j++){

            file << i;
            file << '|';

            int neighborIndex = adjList[i][j].first;
            file<<neighborIndex;
            file<<'|';

            file<<adjList[i][j].second;
            file<<endl;
        }

    }
}





