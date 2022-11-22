#include <GL/glut.h>

#include "disparo.h"
#include "utils.h"

Disparo::Disparo() {}
Disparo::Disparo(float x, float y, float z, bool disparos) {
    disparo = disparos;
    V[0] = x;
    V[1] = y;
    V[2] = z;
    radio = disparoRadio;
}

Disparo::~Disparo() {}

void Disparo::update(float delta) {
    V[2] -= velocidad * delta;

    if (V[2] < -18) {
        fuera_de_rango = true;
    }
}

void Disparo::draw(GLuint texture) {
    glPushMatrix();
    glTranslated(V[0], V[1], V[2]);
    drawSphere(radio, 100, 100, texture);
    glPopMatrix();
}
