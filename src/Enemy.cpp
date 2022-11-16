#include "Enemy.h"
#include <stdlib.h>
#include <stdio.h>
Enemy::Enemy()
{
}

Enemy::Enemy(float x, float y, float z, float delta)
{
    condicion = true;
    enemy_radio = enemy_radio;
    V[0]=x;
    V[1]=y;
    V[2]=z;
    angulo=delta;
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::updateEnemy(float delta){
    if(condicion){
        V[2] += (delta * (enemigo_velocidad)+.011);
        angulo += (10)*delta;
        if(angulo>=360){
            angulo = 0;
        }
    }else{
        if(!condicion){
            enemy_radio -= 0.0015f*delta;
            if(enemy_radio<=0)
                enemy_radio=0;
        }
    }
}

void Enemy::muerto(){
    condicion=false;
}
