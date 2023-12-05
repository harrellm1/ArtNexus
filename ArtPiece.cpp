#include <windows.h>
#include "ArtPiece.h"

//Constructor and destructor
ArtPiece::ArtPiece(){
    pieceName = "Untitled";
    artistName = "Anonymous";
    dateCompleted = "Unknown";
    pieceCountry = "Unknown";
    pieceCulture = "Unknown";
    pieceMedium = "Unknown";
    pieceImageLink = "Not available";
}

ArtPiece::~ArtPiece(){
    pieceName ="";
    artistName = "";
    dateCompleted = "";
    pieceCountry = "";
    pieceCulture = "";
    pieceMedium = "";
    pieceImageLink = "";
    delete this;
}

//Print ArtPiece information
void ArtPiece::printArtPiece() const {
    cout << "Title: " << pieceName << "\n";
    cout << "Artist: " << artistName << "\n";
    cout << "Date:" << dateCompleted << "\n";
    cout <<"Country: " << pieceCountry << "\n";
    cout << "Culture: " << pieceCulture << "\n";
    cout << "Medium: " << pieceMedium << "\n";

    if(pieceImageLink != "Not available"){ //open web page to information and image for the art piece
        const int length = pieceImageLink.length();
        char* char_array = new char[length + 1];
        strcpy(char_array, pieceImageLink.c_str());
        ShellExecute(nullptr, nullptr, char_array, nullptr, nullptr , SW_SHOW );
    }

    else{ //no web link was provided in API
        cout<<"Image not available" <<endl;
    }
}

//File IO
void ArtPiece::serialize(ofstream &outputFile) const{
    outputFile<<pieceName;
    outputFile<<'|';

    outputFile<<artistName;
    outputFile<<'|';

    outputFile<<dateCompleted;
    outputFile<<'|';

    outputFile<<pieceCountry;
    outputFile<<'|';

    outputFile<<pieceCulture;
    outputFile<<'|';

    outputFile<<pieceMedium;
    outputFile<<'|';

    outputFile<<pieceImageLink;

    outputFile<<endl;
}

void ArtPiece::deserialize(ifstream& inFile) {
    string lineFromFile;
    getline(inFile,lineFromFile,'|');
    this->pieceName = lineFromFile;

    getline(inFile,lineFromFile,'|');
    this->artistName = lineFromFile;

    getline(inFile,lineFromFile,'|');
    this->dateCompleted = lineFromFile;

    getline(inFile,lineFromFile,'|');
    this->pieceCountry = lineFromFile;

    getline(inFile,lineFromFile,'|');
    this->pieceCulture = lineFromFile;

    getline(inFile,lineFromFile,'|');
    this->pieceMedium = lineFromFile;

    getline(inFile,lineFromFile,'\n');
    this->pieceImageLink = lineFromFile;

}
