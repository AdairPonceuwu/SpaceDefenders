#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glut.h>
#include "object.h"

class Entity {
public:
    float radio,
          velocidad,
          angulo,
          V[3] = { 0 },
          S[3] = { 1 },
          R[3] = { 0 };
    bool vivo = true;
    Object *obj;

    virtual void update() {}
    virtual void draw(GLuint *texture) {}
    virtual void draw() {}
    virtual void set_obj(Object *o) {
        obj = o;
    }
    virtual void mata() {
        vivo = false;
    }
    virtual void move(float x, float y, float z) {
        V[0] = x;
        V[1] = y;
        V[2] = z;
    }
    virtual void rotate(float angle, float x, float y, float z) {
        angulo = angle;
        R[0] = x;
        R[1] = y;
        R[2] = z;
    }
    virtual void scale(float f) {
        S[0] = f;
        S[1] = f;
        S[2] = f;
    }
};

#endif // ENTITY_H
