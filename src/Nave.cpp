#include "Nave.h"
#include <stdio.h>
Nave::Nave(float x, float y, float z) {
    V[0] = x;
    V[1] = y;
    V[2] = z;
}

Nave::Nave() {}

Nave::~Nave() {}

void Nave::update(float delta){

    if(teclas[0]) { // izq
        V[0] -= velocidad * delta;
    } else if (teclas[1]){ // der
        V[0] += velocidad * delta;
    }

    if(teclas[2]) { // adelante
        V[2] -= velocidad * delta;
    } else if(teclas[3]) { // atras
        V[2] += velocidad * delta;
    }

    //Limites
    if(V[0]<-4.5){
        V[0]=-4.5;
    }
    if(V[0]>4.5){
        V[0]=4.5;
    }

    if(V[2]<-18){
        V[2]=-18;
    }
    if(V[2]>0){
        V[2]=0;
    }
}

void Nave::muerto() {
    vivo = false;
}

