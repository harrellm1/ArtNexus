#ifndef ARTNEXUS_FINALPROJECT_ARTPIECE_H
#define ARTNEXUS_FINALPROJECT_ARTPIECE_H

#include <string>
#include<fstream>
#include<iostream>
#include<sstream>
using namespace std;

struct ArtPiece {
    string pieceName; //identifying phrase or name given to a work of art
    string artistName; //Artist name in the correct order for display
    string dateCompleted; //machine-readable date indicating the year the artwork was completed
    string pieceCountry; //country where the artwork was found or created
    string pieceCulture; //information about the culture or people from which an object was created
    string pieceMedium; //refers to the materials that were used to create the artwork
    string pieceImageLink; //URL to the primary image of an object i JPEG format

    //Constructor and Destructor
    ArtPiece();
    ~ArtPiece();

    void printArtPiece() const;

    //File IO
    void serialize(ofstream& outputFile) const;
    void deserialize(ifstream & inFile);
};


#endif //ARTNEXUS_FINALPROJECT_ARTPIECE_H
