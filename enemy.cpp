#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include "enemy.h"

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
    if(vivo) {
        V[2] += velocidad + 0.011;
        angulo += 1;
        if (angulo >= 360) {
            angulo = 0;
        }
    } else if(!vivo){
        radio -= 0.0015f;
        if (radio <= 0)
            radio = 0;
    }
}

void Enemy::draw(GLuint texture) {}
