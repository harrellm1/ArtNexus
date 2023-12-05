#include "ArtNexus.h"

void printMenu(){
    cout<<"Select from the following menu" <<endl;
    cout<<"1. View Piece Infomration" << endl;
    cout<<"2. Compare Two Pieces" << endl;
    cout<<"3. Exit" <<endl;
}

int main() {
    ArtNexus graph;
    printMenu();
    int input;

    cin>>input;

    while(input != 3){
        if(input == 1){
            int idNum;
            cout<<"Enter Piece ID Number" <<endl;
            cin>>idNum;
            cout<<"\n";
            graph.getVertex(idNum);
            cout<<"\n";
        }

        else if (input == 2){
            int pieceID1;
            int pieceID2;
            cout<<"Enter Piece 1 ID Number" <<endl;
            cin>>pieceID1;
            cout<<"\n";

            cout<<"Enter Piece 2 ID Number" <<endl;
            cin>>pieceID2;
            cout<<"\n";

            cout<<"Connections according to Dijkstra: " << endl;
            graph.dijkstra(pieceID1,pieceID2);
            graph.findPathDiks(pieceID2);
            cout<<"\n";

            cout<<"Connections according to Bellman Ford: " <<endl;
            graph.bellmanFord(pieceID1, pieceID2);
            graph.findPathBell(pieceID2);
            cout<<"\n";
        }

        else if (input == 3){
           break;

        }

        else{
            cout<<"Error: Invalid Input" << endl;
        }

        printMenu();
        cin>>input;
    }

    return 0;
}
