#ifndef DISPARO_H
#define DISPARO_H

#include <GL/glut.h>
#include <stdio.h>

#include "entity.h"

class Disparo : public Entity {
public:
    Disparo();
    Disparo(float x, float y, float z);
    virtual ~Disparo();

    void update(float delta);
    void draw(GLuint texture);
};

#endif // DISPARO_H
