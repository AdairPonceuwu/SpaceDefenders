#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public Entity {
public:
    Enemy(float x, float y, float z, float angulo);
    Enemy();
    virtual ~Enemy();

    void update();
    void draw();
};

#endif // ENEMY_H
