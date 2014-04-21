#include <iostream>
#include <cstdlib>
using namespace std;
#include "Puzzel.h"
#include "Stapel.h"
void hoofdMenu( );

int main( ){
    hoofdMenu( );
    return 0;
}//main

void hoofdMenu( ){
    char keuze;
    Stapel stapel;
    Puzzel puzzel;
    int n;
    cout << endl;
    do {
        cout    << "Kies uit (G)ewoon, (H)orizontaal-variant en\n"
                << "(R)otatie-variant. P voor Parameters, S voor stoppen.\n" 
                << endl;
        keuze = cin.get( );
        switch (keuze){
            case 'G': case 'g':
                cin.ignore(100, '\n');
                cout    << "Het aantal mogelijkheden is: "  
                        << puzzel.gewoon(puzzel,stapel) << endl;
                break;
            case 'H': case 'h':
                puzzel.selectN(puzzel,stapel);
                break;
            case 'R': case 'r':
                cin.ignore(100, '\n');
                puzzel.rotatieTest(puzzel,stapel);
                break;
            case 'P': case 'p':
                puzzel.parameters( );
                break;
            case 's': case 'S':
                break;
            default:
                cout << "Verkeerde input, probeer opnieuw.\n";
                cin.ignore(1, '\n');
                break;
        }//switch
        cout << endl;
    } while (!(keuze == 's') && !(keuze == 'S'));
     cout << "Einde Programma!.\n";
}//hoofdmenu
