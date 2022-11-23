#include <stdio.h>
#include <cstdlib>
#include <GL/glut.h>

#include "nave.h"
#include "object.h"
#include "utils.h"

Nave::Nave(float x, float y, float z) {
    move(x, y, z);
    scale(0.3);
    velocidad = 0.0055f;
    radio = 0.25f;
}

Nave::Nave() {
    velocidad = 0.0055f;
    radio = 0.25f;
    scale(0.3);
}

Nave::~Nave() {}

void Nave::update(float delta) {
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
    if(V[0] < -4.5){
        V[0] = -4.5;
    }
    if(V[0] > 4.5){
        V[0] = 4.5;
    }

    if(V[2] < -18){
        V[2] = -18;
    }
    if(V[2] > 0){
        V[2] = 0;
    }

    if (!vivo){
        printf("GAME OVER\n");
        exit(1);
    }
}

void Nave::draw() {
    glPushMatrix();
    glTranslated(V[0], V[1], V[2]);
    //glRotated(180, 1, 0, 0);
    glScaled(S[0], S[1], S[2]);
    //glutSolidCone(radio, 0.8, 100, 100);
    //drawSphere(radio, 10, 10, 0);
    obj->draw();
    glPopMatrix();
}
