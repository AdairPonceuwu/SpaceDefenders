#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include "enemy.h"
#include "utils.h"

Enemy::Enemy(float x, float y, float z, float angulo) {
    V[0] = x;
    V[1] = y;
    V[2] = z;
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
}

void Enemy::draw(GLuint *texture) {
    glPushMatrix();
    glTranslated(V[0], V[1], V[2]);
    glRotated(angulo, 0, 1, 0);
    drawCone(*texture);
    glPopMatrix();
}
