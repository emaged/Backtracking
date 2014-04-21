#ifndef STAPEL_H
#define	STAPEL_H
class Puzzel;
class State;
class Stapel{
public:
    Stapel( );
    virtual ~Stapel( );
    bool isLeeg( );//returnt true als top == NULL
    void push(State* laatste);//nieuwe state op stapel
    void pop( );//popt zonder terug te zetten
    void pop(Puzzel& puzzel);//state van stapel, zet terug op puzzel  
private:
    State* top;
};

#endif	/* STAPEL_H */

