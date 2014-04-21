#ifndef SPEL_H
#define	SPEL_H
class Stapel;
class State;
class Puzzel {
public:
    Puzzel( );
    Puzzel(int h, int b, int s);
    virtual ~Puzzel( );
    void bouwSpel( );
    void drukAf( );
    int gewoon(Puzzel& puzzel, Stapel& stapel);
    int horizontaal(Puzzel& puzzel, Stapel& stapel, int n);
    bool isVol( );
    bool isVol(int n);
    void parameters( );
    int rotatie(Puzzel& puzzel, Stapel& stapel);
    void rotatieTest(Puzzel& puzzel, Stapel& stapel);
    bool rotatieZet(Puzzel& puzzel, Stapel& stapel, int i, int j, char k);
    int ruimte(int i, int j);//ruimte voor zet?
    bool ruimte(int i, int j, char k);
    void selectN(Puzzel& puzzel, Stapel& stapel);
    void terug(int i, int j, int lengte, char z);
    void vernietig( );
    void zetRechts(Puzzel& puzzel, Stapel& stapel, int i, int j);
    void zetOmlaag(Puzzel& puzzel, Stapel& stapel, int i, int j);
    void zetLinks(Puzzel& puzzel, Stapel& stapel, int i, int j);
    void zetOmhoog(Puzzel& puzzel, Stapel& stapel, int i, int j);
private:
    int rijen, kolommen, zetten,s;//s is lengte stenen
    int hZetten, hZettenAantal;
    int **tabel;
    State* state;
};

class State{
public:
    State( );
    State(int r, int k, int s, char z);
    int rij, kolom, lengte;// s is opgegeven lengte "stenen"
    char richting;//verticaal/horizontaal
    State* next;
};

int leesGetal(int max, int min);
#endif	/* SPEL_H */

