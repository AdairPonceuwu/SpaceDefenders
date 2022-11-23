#include <stdio.h>
#include <cstdlib>
#include <GL/glut.h>

#include "nave.h"

Nave::Nave(float x, float y, float z) {
    V[0] = x;
    V[1] = y;
    V[2] = z;
    velocidad = 0.0055f;
    radio = 0.25f;
}

Nave::Nave() {
    velocidad = 0.0055f;
    radio = 0.25f;
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
}

void Nave::draw(GLuint *texture) {
    if (!vivo){
        printf("GAME OVER\n");
        exit(1);
    }
    glPushMatrix();
    glTranslated(V[0], V[1], V[2]);
    glRotated(180, 1, 0, 0);
    glutSolidCone(radio, 0.8, 100, 100);
    glPopMatrix();
}
