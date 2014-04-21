#ifndef STAPEL_H
#define	STAPEL_H

class Spel;
class State {
public:
	State( );
	State(int i, int j, int w, int r, int k);
	int i, j;
        int waarde;
	int rSter, kSter;
	State* next;
	//beurt?
};

class Stapel {
public:
	Stapel( );//zet top = NULL
	~Stapel( );// popt stapel tot top = NULL
	void push(State* laatste);//nieuwe state op stapel
	void pop(Spel& puzzel);//state van stapel, zet terug op puzzel
	void pop( );//popt zonder terug te zetten
	bool isLeeg( );//returnt true als top == NULL
private:
	State* top;
};

#endif	/* STAPEL_H */
