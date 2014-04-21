#include <iostream>
#include <cstdlib>
using namespace std;
#include "Puzzel.h"
#include "Stapel.h"

const int rMax = 12, kMax = 12;

State::State( ):next(NULL){
    //leeg
}//constructor

State::State(int r, int k, int s, char z):rij(r),kolom(k),
        lengte(s),richting(z),next(NULL){
    //leeg
}//constructor met parameters

Puzzel::Puzzel( ):rijen(6),kolommen(8),zetten(0),s(3),
        hZetten(0),hZettenAantal(0),tabel(NULL){
    bouwSpel( );
}//constructor met standaard waarden voor rijen en kolommen

Puzzel::Puzzel(int h, int b, int s):rijen(h),kolommen(b),
        zetten(0),s(s),hZetten(0),hZettenAantal(0),tabel(NULL){
    bouwSpel( );
}//bouwt puzzel met hoogte h en breedte b

Puzzel::~Puzzel( ){
    vernietig( );
}//destructor

void Puzzel::bouwSpel( ){
    if (tabel != NULL)
        vernietig( );
    tabel = new int*[rijen];
    for (int i = 0; i < rijen; i++){
        tabel[i] = new int[kolommen];
    }//for i
    for (int i = 0; i < rijen; i++)
        for (int j = 0; j < kolommen; j++)
            tabel[i][j] = 0;
}//bouwt tabel

void Puzzel::drukAf( ){
    for (int i = 0; i < rijen; i++){
        for (int j =  0; j < kolommen; j++){
            if(tabel[i][j] < 10)
                cout << tabel[i][j] << "  ";
            else 
                cout << tabel[i][j] << ' ';
        }//for j
        cout << endl;
    }//for i
    cout << endl;
}//drukt stand af

int Puzzel::gewoon(Puzzel& puzzel, Stapel& stapel){
    if (isVol( )){        
        return 1;
    }//if
    int teller = 0;
    int i, j;
    int optie = 0;
    for (i = 0; i < rijen; i++){//kan beter?!!!!!
        for (j = 0; j < kolommen; j++){
            optie = ruimte(i,j);
            if (optie > 0){
                goto here;
            }//if zet mogelijk
        }//for j
    }//for i
    return 0;
    here:
    if (optie == 3){
        zetRechts(puzzel,stapel,i,j);
        teller += gewoon(puzzel,stapel);
        stapel.pop(puzzel);
        zetOmlaag(puzzel,stapel,i,j);
        teller += gewoon(puzzel,stapel);
        stapel.pop(puzzel);
    }//if optie 3
    else if (optie == 2){
        zetOmlaag(puzzel,stapel,i,j);
        teller += gewoon(puzzel,stapel);
        stapel.pop(puzzel);
    }//if optie 2
    else if (optie == 1){
        zetRechts(puzzel,stapel,i,j);
        teller += gewoon(puzzel,stapel);
        stapel.pop(puzzel);
    }//if optie 1
    return teller;
}//berekent aantal mogelijkheden

int Puzzel::horizontaal(Puzzel& puzzel, Stapel& stapel, int n){
    if (isVol( )){
        if (hZetten == n){
            hZettenAantal++;
        }//if   
        return 1;
    }//if
    int teller = 0;
    int i, j;
    int optie = 0;
    for (i = 0; i < rijen; i++){
        for (j = 0; j < kolommen; j++){
            optie = ruimte(i,j);
            if (optie > 0){
                goto here;
            }//if zet mogelijk
        }//for j
    }//for i
    return 0;
    here:
    if (optie == 3){
        zetRechts(puzzel,stapel,i,j);
        hZetten++;
        teller += horizontaal(puzzel,stapel,n);
        stapel.pop(puzzel);
        hZetten--;
        zetOmlaag(puzzel,stapel,i,j);
        teller += horizontaal(puzzel,stapel,n);
        stapel.pop(puzzel);
    }//if optie 3
    else if (optie == 2){
        zetOmlaag(puzzel,stapel,i,j);
        teller += horizontaal(puzzel,stapel,n);
        stapel.pop(puzzel);
    }//if optie 2
    else if (optie == 1){
        zetRechts(puzzel,stapel,i,j);
        hZetten++;
        teller += horizontaal(puzzel,stapel,n);
        stapel.pop(puzzel);
        hZetten--;
    }//if optie 1   
    if (stapel.isLeeg( ))
        return hZettenAantal;
    return teller;
}//berekent aantal mogelijkheden met a horizontale "stenen"


bool Puzzel::isVol( ){
    if (rijen * kolommen == zetten  * s)
        return true;
    else 
        return false;
}//true als vol

void Puzzel::parameters( ){
    cin.ignore(100, '\n');
    vernietig( );
    cout	<< "Voer aantal rijen in, maximaal " << rMax << ".\n";
    rijen = leesGetal(rMax,1);  
    cout	<< "Voer aantal kolommen in, maximaal " << kMax << ".\n";
    kolommen = leesGetal(kMax,1);
    cout << "Voer de lengte van de \"stenen\" in.\n";
    if (rijen >= kolommen)
        s = leesGetal(rijen,1);
    else
        s = leesGetal(kolommen,1);
    while( (rijen * kolommen) % s != 0){
        s++;
    }//while
    cout    << "Gecreëerd is een " << rijen << " bij " << kolommen
            << " matrix, de steenlengte is " << s << ".\n" << endl;
    bouwSpel( );
}//invoer voor h en b

int Puzzel::rotatie(Puzzel& puzzel, Stapel& stapel){
    if (isVol( )){
        return 1;
    }//if
    int teller = 0;
    int i, j, k;
    int optie = 0;
    for (i = 0; i < rijen; i++){//kan beter?!!!!!
        for (j = 0; j < kolommen; j++){
            optie = ruimte(i,j);
            if (optie > 0){
                goto here;
            }//if zet mogelijk
        }//for j
    }//for i
    return 0;
    here:
    if (optie == 3){
        zetRechts(puzzel,stapel,i,j);
        if(rotatieZet(puzzel,stapel,i,j,'h')){
            teller += rotatie(puzzel,stapel);
            for (k = 0; k  < 4; k++)
                stapel.pop(puzzel);
        }//if
        else
            stapel.pop(puzzel);
        zetOmlaag(puzzel,stapel,i,j);
        if (rotatieZet(puzzel,stapel,i,j,'v')){
            teller += rotatie(puzzel,stapel);
            for (k = 0; k  < 4; k++)
                stapel.pop(puzzel);
        }//if
        else
            stapel.pop(puzzel);
    }//if optie 3
    else if (optie == 2){
        zetOmlaag(puzzel,stapel,i,j);
        if (rotatieZet(puzzel,stapel,i,j,'v')){
            teller += rotatie(puzzel,stapel);
            for (k = 0; k  < 4; k++)
                stapel.pop(puzzel);
        }//if
        else
            stapel.pop(puzzel);
    }//if optie 2
    else if (optie == 1){
        zetRechts(puzzel,stapel,i,j);
       if(rotatieZet(puzzel,stapel,i,j,'h')){
            teller += rotatie(puzzel,stapel);
            for (k = 0; k  < 4; k++)
                stapel.pop(puzzel);
        }//if
        else
            stapel.pop(puzzel);
    }//if optie 1
    return teller;
}//mogelijkheden met rotatie?

void Puzzel::rotatieTest(Puzzel& puzzel, Stapel& stapel){
    if (rijen != kolommen){
        cout    << "Het aantal rijen en het aantal kolommen zijn niet\n"
                << "gelijk; Rotatie onmogelijk.\n" << endl;
        return;
    }//if h!=b
    cout    << "Het aantal Rotatie-invarientheden is: \n"
            << puzzel.rotatie(puzzel,stapel) << endl;
}//test of rotatie mogelijk is

bool Puzzel::rotatieZet(Puzzel& puzzel, Stapel& stapel,
        int i, int j, char k){
    if (k == 'h'){
        if(ruimte(j,rijen-1-i,'v') && ruimte(rijen-1-i,kolommen-1-j,'l')
                && ruimte(rijen-1-j,i,'o')){
        zetOmlaag(puzzel,stapel,j,rijen-1-i);
        zetLinks(puzzel,stapel,rijen-1-i,kolommen-1-j);
        zetOmhoog(puzzel,stapel,rijen-1-j,i);
        }//if
        else
            return false;
    }//if
    else {
        if (ruimte(j,rijen-1-i,'l') && ruimte(rijen-1-i,kolommen-1-j,'o')
                && ruimte(rijen-1-j,i,'h')){
        zetLinks(puzzel,stapel,j,rijen-1-i);
        zetOmhoog(puzzel,stapel,rijen-1-i,kolommen-1-j);
        zetRechts(puzzel,stapel,rijen-1-j,i);
        }//if
        else
            return false;
    }//else
    return true;
}//parameters voor puzzel

int Puzzel::ruimte(int i, int j){
    int tempI = i, tempJ = j;
    int lengte = s;
    int optie = 0;
    do{
        if (tabel[i][j] == 0)
            j++, lengte--;
        else 
            break;
        if (lengte == 0){
            optie = 1;
            break;
        }//if
    }while (j < kolommen);
    i = tempI, j = tempJ;
    lengte = s;
    do{
        if (tabel[i][j] == 0)
            i++, lengte--;
        else
            return 0;
        if (lengte == 0){
            optie += 2;
            break;
        }//if
    }while (i < rijen);
    return optie;
}//ruimte?

bool Puzzel::ruimte(int i, int j, char k){
    int lengte = s;
    switch(k){
        case 'h':
            do{
                if (tabel[i][j] == 0)
                    j++, lengte--;
                else
                    return false;
                if (lengte == 0){
                    return true;
                }//if
            }while (j < kolommen );
            break;
        case 'v':
            do{
                if (tabel[i][j] == 0)
                    i++, lengte--;
                else
                    return false;
                if (lengte == 0){
                    return true;
                }//if
            }while (i < rijen);
            break;
        case 'l':
            do{
                if (tabel[i][j] == 0)
                    j--, lengte--;
                else
                    return false;
                if (lengte == 0){
                    return true;
                }//if
            }while (j < kolommen && j >= 0);
            break;
        case 'o':
            do{
                if (tabel[i][j] == 0)
                    i--, lengte--;
                else
                    return false;
                if (lengte == 0){
                    return true;
                }//if
            }while (i < rijen && i >= 0);
            break;
    }//switch
    return false;
}//ruimte 2

void Puzzel::selectN(Puzzel& puzzel, Stapel& stapel){
    int n;
    int maxN = (rijen * kolommen) / s;
    cout << "Voer aantal horizontale stenen in.\n" << endl;
    n = leesGetal(maxN,1);
    int aantal = horizontaal(puzzel,stapel,n);
    cout    << "Aantal spellen met " << n << " horizontale stenen: "
            << aantal   << '.' << endl;
}//selectN

void Puzzel::terug(int i, int j, int lengte, char z){
    switch(z){
        case 'h':
            while (lengte > 0){
                tabel[i][j] = 0, j++, lengte--;
            }//while
            break;
        case 'v':
            while (lengte > 0){
            tabel[i][j] = 0, i++, lengte--;
            }//while
            break;
        case 'o':
            while (lengte > 0){
            tabel[i][j] = 0, i--, lengte--;
            }//while
        case 'l':
            while (lengte > 0){
            tabel[i][j] = 0, j--, lengte--;
            }//while
    }//switch
    zetten--;
}//terug

void Puzzel::vernietig( ){
    for (int i = 0; i < rijen; i++)
        delete[] tabel[i];
    delete[] tabel;
    tabel = NULL;
}//vernietig

//kan beter?
void Puzzel::zetRechts(Puzzel& puzzel, Stapel& stapel, int i, int j){
    state = new State(i,j,s,'h');
    stapel.push(state);
    zetten++;
    for(int lengte = s; lengte > 0; lengte--)
        tabel[i][j] = zetten, j++;
}//zet horizontaal

void Puzzel::zetOmlaag(Puzzel& puzzel, Stapel& stapel, int i, int j){
    state = new State(i,j,s,'v');
    stapel.push(state);
    zetten++;
    for(int lengte = s; lengte > 0; lengte--)
        tabel[i][j] = zetten, i++;
}//zet verticaal

void Puzzel::zetLinks(Puzzel& puzzel, Stapel& stapel, int i, int j){
    state = new State(i,j,s,'l');
    stapel.push(state);
    zetten++;
    for(int lengte = s; lengte > 0; lengte--)
        tabel[i][j] = zetten, j--;
    
}//zet naar links

void Puzzel::zetOmhoog(Puzzel& puzzel, Stapel& stapel, int i, int j){
    state = new State(i,j,s,'o');
    stapel.push(state);
    zetten++;
    for(int lengte = s; lengte > 0; lengte--)
        tabel[i][j] = zetten, i--;
}//zet omhoog

int leesGetal(int max, int min){
    char kar;
    int getal = 0;
    kar = cin.get( );
    while (kar == '\n')
        kar = cin.get( );
        while (kar != '\n'){
            if (kar >= '0' && kar <= '9')
		getal = 10*getal + (kar - '0');
		kar = cin.get( );
	}//while
	if (getal > max){
		cout << "Input is hoger dan toegestaan. Probeer opnieuw.\n"
             << "Voer het benodigde getal in.\n";
        return leesGetal(max, min);
    }//if
    if (getal < min){
        cout << "Input is lager dan toegestaan. Probeer opnieuw.\n"
             << "Voer het benodigde getal in.\n";
        return leesGetal(max, min);
    }//if
    else
        return getal;
}//leesGetal