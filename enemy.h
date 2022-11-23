#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public Entity {
public:
    Enemy(float x, float y, float z, float angulo, float rad);
    Enemy();
    virtual ~Enemy();

    void update(float delta);
    void draw();
};

#endif // ENEMY_H
