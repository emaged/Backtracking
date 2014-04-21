#include <iostream>
#include <cstdlib>
using namespace std;
#include "Puzzel.h"
#include "Stapel.h"

Stapel::Stapel( ):top(NULL){
    
}//Stapel

Stapel::~Stapel( ){
    while (!isLeeg( )){
        pop( );
    }//while
}//destructor

bool Stapel::isLeeg( ){
    return (top == NULL);
}//leeg als top nergens naar wijst..

void Stapel::pop( ){
    State* discard = top;
    top = top->next;
    delete discard;
}//pop

void Stapel::pop(Puzzel& puzzel){
    if (top == NULL){
        return;
    }//if
    int i = top->rij;
    int j = top->kolom;
    int lengte = top->lengte;
    char richting = top->richting;
    puzzel.terug(i,j,lengte,richting);
    State* discard = top;
    top = top->next;
    delete discard;
}//pop

void Stapel::push(State* laatste){
    laatste->next = top;
    top = laatste;
}//push
