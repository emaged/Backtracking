#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "Spel.h"
#include "Stapel.h"

void hoofdMenu( );

int main( ) {
    hoofdMenu( );
    return 0;
}//main

void hoofdMenu( ){
    char keuze;
    srand(time(0));
    Stapel s;
    Spel puzzel;
    puzzel.drukAf( );
    cout << endl;
    do {
        cout    << "(P)arameters, Optie(1), Optie(2), (S)toppen.\n"
                << "(B)este, (G)retig, of (R)andom zet.\n"
                << "(T)erug voor vorige zet.\n" << endl;
        keuze = cin.get( );
        switch (keuze){
            case 'p': case 'P':
                    puzzel.parameters( );
                    break;
            case '1':
                if (puzzel.optie1(puzzel,s))
                    cout << "Het spel is winnend voor A.\n" << endl;
                else
                    cout << "Het spel is winnend voor B.\n" << endl;
                cin.ignore(100, '\n');
                break;
            case '2':
                puzzel.result2(puzzel,s);
                cin.ignore(100, '\n');
                break;
            case 'b': case 'B':
                puzzel.zetBeste(puzzel,s);
                cin.ignore(100, '\n');
                break;
            case 'g': case 'G':
                puzzel.zetGretig(s);
                break;
            case 'r': case 'R':
                puzzel.zetRandom(s);
                break;
            case 't': case 'T':
                s.pop(puzzel);
                cin.ignore(100, '\n');
                puzzel.drukAf( );
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
