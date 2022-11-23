#include <GL/glut.h>

#include "disparo.h"
#include "utils.h"

Disparo::Disparo() {}
Disparo::Disparo(float x, float y, float z) {
    V[0] = x;
    V[1] = y;
    V[2] = z;
    radio = 0.08;
    velocidad = 0.005;
}

Disparo::~Disparo() {}

void Disparo::update(float delta) {
    V[2] -= velocidad * delta;

    if (V[2] < -18) {
        mata();
    }
}

void Disparo::draw(GLuint texture) {
    glPushMatrix();
    glTranslated(V[0], V[1], V[2]);
    drawSphere(radio, 100, 100, texture);
    glPopMatrix();
}
