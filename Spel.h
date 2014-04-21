#ifndef SPEL_H
#define	SPEL_H

class State;
class Stapel;
class Spel {
public:
	Spel( );//creëert random gevuld 4 bij 4 spel
	Spel(int hoogte, int breedte);//creëert random gevult h bij b spel
	~Spel( );//roept vernietig( ) aan. 
        //creëert een dynamische array en vult deze met vulRandom( )
	void bouwSpel( );
	void drukAf( );//drukt spel af
	bool einde( );//returnt true als er geen zetten meer mogelijk zijn
	void invoer( );//leest uit opgegeven file spel in, controleert waardes
        //returnt true als a winnend is, anders false
	bool optie1(Spel& spel, Stapel& stapel);
        //berekent beste zet en de eindstand na optimaal spel van beide spelers
	void optie2(Spel& spel, Stapel& stapel);
	void parameters( );//submenu voor parameters
	void setPuzzel( );//set parameters
        //creërt puzzel met rijen i, kolommen j. handig voor evt test functies
        void setPuzzel(int i, int j);//creëert puzzel
        //hulp functie voor stapel.pop( ). zet waardes op:
        //tabel[i][j] = waarde, tabel[r][k] = ster
	void terug(int i, int j, int waarde, int r, int k);
	void vulRandom( );//random puzzel voor ingevoerde h en b
        //maakt een zet op tabel[i][j], returnt false als ongeldige zet
	bool zet(int i, int j, Stapel& stapel);//returnt true als zet succes
	void zetBeste(Spel& spel, Stapel& stapel);//mbv optie2 zet beste zet
	void zetGretig(Stapel& stapel);//berekent en zet hoogste geldige zet
        //srand(time(0)) in main voor minder voorspelbaarheid.
	void zetRandom(Stapel& stapel);//zet random zet 
	void vernietig( );//bevat instructies voor destructor
	void result2(Spel& spel, Stapel& stapel);//weergeeft resultaat optie2
private:
        int rijen, kolommen;
	int **tabel;//rijen * kolommen
        int aantal;//aantal zetten
        char aanZet;//'A' of 'B'
	int maxA, maxB;//hoogste waarde voor spelerA en spelerB
        int spelerA, spelerB;//score speler A en speler B
        int rSter, kSter;//rij van *
        int rBeste, kBeste;//na aanroepen van optie 2 geeft best mogelijke zet
	bool winst;
	State* state;
};
//geeft error bij invoer > max  en bij invoer < min. leest per kar niet 
//met invoer >> om suboptimale invoer te voorkomen
int leesGetal(int max, int min);
//wisselt a en b, gebruikt voor vulRandom( );
void wissel(int& A, int& B);

#endif	/* SPEL_H */
