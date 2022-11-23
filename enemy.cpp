#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include "enemy.h"
#include "utils.h"

Enemy::Enemy(float x, float y, float z, float angulo) {
    move(x, y, z);
    scale(0.5);
    R[1] = 1.0;
    radio = 0.45f;
    velocidad = 0.00015f;
    this->angulo = angulo;
    printf("crea enemigo!\n");
}

Enemy::Enemy() {
    radio = 0.45f;
    velocidad = 0.00015f;
    printf("crea enemigo sin parametros!");
}

Enemy::~Enemy() {}

void Enemy::update() {
    V[2] += velocidad + 0.011;
    angulo = (float)(((int)angulo + 1) % 360);

    if (V[2] > 0.5) {
        mata();
    }
}

void Enemy::draw() {
    glPushMatrix();
    glTranslated(V[0], V[1], V[2]);
    glRotated(angulo, R[0], R[1], R[2]);
    glScaled(S[0], S[1], S[2]);
    //drawCone(*texture);
    //drawSphere(radio, 10, 10, 0);
    obj->draw();
    glPopMatrix();
}
