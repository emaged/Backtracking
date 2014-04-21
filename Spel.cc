#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
#include "Spel.h"
#include "Stapel.h"

const int rMax = 10, kMax = 10;

Spel::Spel( ):rijen(4), kolommen(4), tabel(NULL){
    bouwSpel( );
    vulRandom( );
}//constructor

Spel::Spel(int hoogte, int breedte):rijen(hoogte), kolommen(breedte), 
        tabel(NULL){
    bouwSpel( );
    vulRandom( );
}//constructor voor gegeven h en b

Spel::~Spel( ){
    vernietig( );
}//destructor

//random vullen?
void Spel::bouwSpel( ){
    if (tabel != NULL)
        vernietig( );
    tabel = new int*[rijen];
    for (int i = 0; i < rijen; i++){
        tabel[i] = new int[kolommen];
    }//for i
    aanZet = 'A';
    aantal = 0;
    maxA = 0, maxB = 0;
    spelerA = 0, spelerB = 0;
    winst = false;
}//bouwt spel

void Spel::drukAf( ){
    for (int i = 0; i < rijen; i++){
        for (int j = 0; j < kolommen; j++){
            if (tabel[i][j] == -1)
                cout << ' ' << '*' << ' ';
            else if (tabel[i][j] == 0)
                cout << ' ' << '-' << ' ';
            else if (tabel[i][j] < 10)//100?
                cout << ' ' << tabel[i][j] << ' ';
            else 
                cout << tabel[i][j] << ' ';
        }//for j
        cout << endl;
    }//for i
    cout << endl;
    cout << "Speler A: " << spelerA << " Speler B: " << spelerB << endl
            << "score A-B: " << spelerA - spelerB << endl;
}//drukaf

bool Spel::einde( ){
    int i, j, teller = 0;
    for (i = 0; i < rijen; i++)
        if (tabel[i][kSter] > 0)
            teller++;
    for (j = 0; j < kolommen; j++)
        if (tabel[rSter][j] > 0)
            teller++;
    if (teller == 0)//geen zet beschikbaar
        return true;
    else 
        return false;
}//einde?

//enige bug die ik nog kan vinden is wanneer invoer file
//verkeerde rijen en kolommen heeft, resulteert soms in seg
//fault. Ik ga echter wel uit van goede file invoer..
void Spel::invoer( ){
    cin.ignore(100, '\n');
    ifstream invoer;
    string invoerNaam;
    int getal, i = 0, j  = 0;
    int teller = 0;
    cout	<< "Leest beschrijving uit een file.\n"
        	<< "Voer de bestandslocatie in.\n";
	cin	>> invoerNaam;
	invoer.open(invoerNaam.c_str( ), ios::in);
	if (! invoer ){ 
		cout << "File niet geopend" << endl;
		return; 
	}//if
    vernietig( );
	invoer >> rijen;
    if (rijen <= 0)
        rijen = 4;
    while (rijen > rMax)
        rijen = rijen/10;
    invoer >> kolommen;
    if (kolommen <= 0)
        kolommen = 5;
    while (kolommen > kMax)
        kolommen = kolommen/10;
    bouwSpel( );
    invoer >> getal;
    while (! invoer.eof( )){//kan beter?
        if (getal > 100 || (getal <= 0 && getal != -1))
                getal = 0;//wordt leeg vakje
        tabel[i][j] = getal;
        if (getal == -1)
            rSter = i, kSter = j;
        teller++;
        j++;
        if (j == kolommen)
            j = 0, i++;
        if ( j == kolommen && i == (rijen - 1))//voor te grote invoer file
            break;                             //(eventueel)
        invoer >> getal;
        if (invoer.eof( ) && (teller != kolommen*rijen) ){//te kleine invoer
            tabel[i][j] = getal, j++;
            for (; i < rijen; i++)
                for (; j < kolommen; j++)
                    tabel[i][j] = 0;
        }//if
    }//while
    cout << endl;
    drukAf( );
}//invoer

bool Spel::optie1(Spel& spel, Stapel& stapel){
    if (einde( )){
        if (spelerA > spelerB)
            return true;
        else 
            return false;
    }//if
    bool winA;
    bool geldig;
    for (int i = 0; i < rijen; i ++){
        geldig = zet(i,kSter,stapel);
        if (geldig){
            aantal++;
            winA = optie1(spel,stapel);
            stapel.pop(spel);
            aantal--;
            if (aanZet == 'A'){
                if (winA && aantal == 0)//aantal == 0  is oorspronkelijke state
                    winst = true;
                else if (aantal == 0)
                    winst = false;
                if (winst == true && aantal == 0)
                    goto here;//vakje dat wint gevonden
                if (winA)
                    return true;
            }//if
            if (aanZet == 'B'){
                if (!winA)
                    return false;
            }//if
        }//if
    }//for i
    for (int j = 0; j < kolommen; j++){
        geldig = zet(rSter,j,stapel);
        if (geldig){
            aantal++;
            winA = optie1(spel,stapel);
            stapel.pop(spel);
            aantal--;
            if (winA && aantal == 0)
                winst = true;
            else if (aantal == 0)
                winst = false;
            if (winst == true && aantal == 0){
                goto here;
            }//if
            if (aanZet == 'A'){
                if (winA)
                    return true;
            }//if
            if (aanZet == 'B'){
                if (!winA)
                    return false;
            }//if
        }//if
    }//for j
    if (aanZet == 'A')
        return false;//alles doorlopen maar nog geen true
    else            //dus moet false zijn
        return true;//--< zelfde andersom voor b
    here:
    winst = false;//reset winst
    return true;
}//optie 1

//het idee is dus dat, beginnent vanuit een zet voor eindpositie
//alle mogelijke eindposities worden berekend en de beste wordt 
//gekozen, en van daaruit steeds een stap terug, met wisselende
//personen aan zet. Ik wist niet hoe ik het korter dan zou kunnen maken..
void Spel::optie2(Spel& spel, Stapel& stapel){
    if (einde( )){
        maxA = spelerA, maxB = spelerB;
        return;
    }//if
    int teller = 0;
    int tempA = 0, tempB = 0;
    bool geldig;
    for (int i = 0; i < rijen; i ++){
        geldig = zet(i,kSter,stapel);
        if (geldig){
            aantal++;
            optie2(spel,stapel);
            stapel.pop(spel);
            aantal--;
            if (aanZet == 'A'){
                if (teller == 0){
                    tempA = maxA, tempB = maxB, teller++;
                    if (aantal == 0)//aantal == 0  is oorspronkelijke state
                        rBeste = i, kBeste = kSter;
                }//if
                else if (maxA - maxB > tempA - tempB){
                    tempA = maxA, tempB = maxB;
                    if (aantal == 0)
                        rBeste = i, kBeste = kSter;
                }//else if
            }//if
            if (aanZet == 'B'){
                if (teller == 0){
                    tempA = maxA, tempB = maxB, teller++;
                    if (aantal == 0)
                        rBeste = i, kBeste = kSter;
                }//if
                else if (maxB - maxA > tempB - tempA){
                    tempA = maxA, tempB = maxB;
                    if (aantal == 0)
                        rBeste = i, kBeste = kSter;
                }//else if
            }//if
        }//if
    }//for i
    for (int j = 0; j < kolommen; j++){
        geldig = zet(rSter,j,stapel);
        if(geldig){
            aantal++;
            optie2(spel,stapel);
            stapel.pop(spel);
            aantal--;
            if (aanZet == 'A'){
                if (teller == 0){
                    tempA = maxA, tempB = maxB, teller++;
                    if (aantal == 0)
                        rBeste = rSter, kBeste = j;
                }//if
                else if (maxA - maxB > tempA - tempB){
                    tempA = maxA, tempB = maxB;
                    if (aantal == 0)
                        rBeste = rSter, kBeste = j;
                }//else if
            }//if
            if (aanZet == 'B'){
                if (teller == 0){
                    tempA = maxA, tempB = maxB, teller++;
                    if (aantal == 0)
                        rBeste = rSter, kBeste = j;
                }//if
                else if (maxB - maxA > tempB - tempA){
                    tempA = maxA, tempB = maxB;
                    if (aantal == 0)
                        rBeste = rSter, kBeste = j;
                }//else if
            }//if
        }//if
    }//for j
    maxA = tempA, maxB = tempB;
    return;
}//optie 2

void Spel::parameters( ){
    char subKeuze = -1;//keuze in submenu
    cin.ignore(100, '\n');
    do {
        cout << "(F)ile invoer of (R)andom puzzel? (T)erug\n";
        subKeuze = cin.get( );
        switch (subKeuze){
            case 'f' : case 'F':
                invoer( );
                subKeuze = 't';
                cin.ignore(1, '\n');
                break;
            case 'r': case 'R':
                setPuzzel( );
                subKeuze = 't';
                break;
            case 't' : case 'T':
                cin.ignore(1, '\n');
                break;
            default:
                cout << "verkeerde input, probeer opnieuw.\n" << endl;
                cin.ignore(1, '\n');
                break;
        }//switch
    } while (subKeuze != 't' && subKeuze != 'T');
}//parameters

void Spel::result2(Spel& spel, Stapel& stapel){
    optie2(spel,stapel);
    int verschil = maxA - maxB;
    cout << "Uitslag: " << maxA << " - " << maxB << '.' << endl;
    if (verschil <= 0){
        cout << "Verschil: " << -verschil << '.' << endl;
        cout << "Het spel is winnend voor B.\n";
    }//if
    else {
        cout << "Verschil: " << verschil << '.' << endl;
        cout << "Het spel is winnend voor A.\n";
    }//else
    cout << "Beginzet: " << rBeste << ',' << kBeste << endl;
    maxA = 0, maxB = 0;
}//resultaat optie 2

void Spel::setPuzzel( ){
    cin.ignore(100, '\n');
    vernietig( );
    cout	<< "Voer aantal rijen in, maximaal " << rMax << ".\n";
	rijen = leesGetal(rMax,1);
	cout	<< "Voer aantal kolommen in, maximaal " << kMax << ".\n";
	kolommen = leesGetal(kMax,1);
    bouwSpel( );
    srand(time(0));
    vulRandom( );
	cout	<< "Aantal rijen: " << rijen << endl
		<< "Aantal kolommen: " << kolommen << endl << endl;
    drukAf( );
}//menu voor parameters

void Spel::setPuzzel(int i, int j){
    vernietig( );
    rijen = i, kolommen = j;
    bouwSpel( );
    vulRandom( );
}//set puzzel met rijen i en kolommen k

void Spel::terug(int i, int j, int waarde, int r, int k){
    tabel[i][j] = waarde;
    tabel[r][k] = -1;
    rSter = r, kSter = k;
    if (aanZet == 'A')
        spelerB -= waarde, aanZet = 'B';
    else 
        spelerA -= waarde, aanZet = 'A';
}//terug, hulp voor stapel.pop( )

void Spel::vernietig( ){
    for (int i = 0; i < rijen; i++)
        delete[] tabel[i];
    delete[] tabel;
    tabel = NULL;
}//vernietig

void Spel::vulRandom( ){
    int A[100];
    int i, j, r;
    for (i = 0; i < 100; i++)
        A[i] = i + 1;
    for (i = 99; i >= 0; i--){//kan eventueel vaker schudden indien nodig..
        r = rand( ) % (i + 1);
        wissel(A[i], A[r]);
    }//for i
    r = 0;
    for (i = 0; i < rijen; i++){
        for (int j = 0; j < kolommen; j++){
            tabel[i][j] = A[r];
            r++;
        }//for j
    }//for i
    i =  rand( ) % rijen;
    j = rand( ) % kolommen;
    tabel[i][j] = -1;
    rSter = i, kSter = j;
}//vult random

bool Spel::zet(int i, int j, Stapel& stapel){
    if (tabel[i][j] < 1)
        return false;//geen geldige zet
    int value = tabel[i][j];
    if (aanZet == 'A')
        spelerA += value, aanZet = 'B';
    else
        spelerB += value, aanZet = 'A';
    state = new State(i,j,value,rSter,kSter);
    stapel.push(state);
    tabel[rSter][kSter] = 0;
    rSter = i, kSter = j;
    tabel[i][j] = -1;
    return true;
}//zet

void Spel::zetBeste(Spel& spel, Stapel& stapel){
    if (einde( )){
        cout << "Er is een winnaar!\n" << endl;
        drukAf( );
        return;
    }//if
    optie2(spel,stapel);
    int i = rBeste, j = kBeste;
    zet(i,j,stapel);//placeholder?
    drukAf( );
    return;
}//zet beste zet mbv optie 2

void Spel::zetGretig(Stapel& stapel){
    cin.ignore(100, '\n');
    if (einde( )){
        cout << "Er is een winnaar!\n" << endl; 
        drukAf( );
        return;
    }//if
    int i, j, iMax, jMax, max = 0;
    for (i = 0; i < rijen; i++)
        if (tabel[i][kSter] > max){
            max = tabel[i][kSter];
            iMax = i, jMax = kSter;
        }//if
    for (j = 0; j < kolommen; j++)
        if (tabel[rSter][j] > max){
            max = tabel[rSter][j];
            iMax = rSter, jMax = j;
        }//if
    if (aanZet == 'A')
        spelerA += tabel[iMax][jMax], aanZet = 'B';
    else
        spelerB += tabel[iMax][jMax], aanZet = 'A';
    state = new State(iMax,jMax,max,rSter,kSter);
    stapel.push(state);
    tabel[rSter][kSter] = 0;
    rSter = iMax, kSter = jMax;
    tabel[iMax][jMax] = -1;
    cout << endl;
    drukAf( );
}//zet hoogste getal mogelijk

void Spel::zetRandom(Stapel& stapel){
    cin.ignore(100, '\n');
    if (einde( )){
        cout << "Er is al een winnaar!\n" << endl; 
        drukAf( );
        return;
    }//if
    int zetten[rMax + kMax];
    int i, j, teller = 0;
    for (i = 0; i < rijen; i++){
        while (tabel[i][kSter] == 0 || tabel[i][kSter] == -1){
            i++;
            if (i >= rijen)
                goto stop;
        }//while
        zetten[teller] = i, teller++;
    }//for i
    stop:
    for (j = 0; j < kolommen; j++){
        while (tabel[rSter][j] == 0 || tabel[rSter][j] == -1){
            j++;
            if (j >= kolommen)
                goto stop2;
        }//while
        zetten[teller] = j + 10, teller++;
    }//for j
    stop2:
    int r = rand( ) % teller;
    if (zetten[r] >= 10)
        j = zetten[r] - 10, i = rSter;
    else
        i = zetten[r], j = kSter;
    if (aanZet == 'A')
        spelerA += tabel[i][j], aanZet = 'B';
    else
        spelerB += tabel[i][j], aanZet = 'A';
    teller = tabel[i][j];
    state = new State(i,j,teller,rSter,kSter);
    stapel.push(state);
    tabel[rSter][kSter] = 0;
    rSter = i, kSter = j;
    tabel[i][j] = -1;
    cout << endl;
    drukAf( );
}//zet at random

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

void wissel(int& A, int& B){
    int temp;
    temp = A;
    A = B;
    B = temp;
}//wissel
