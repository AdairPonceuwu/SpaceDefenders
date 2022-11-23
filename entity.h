#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glut.h>
#include "object.h"

class Entity {
public:
    float radio,
          velocidad,
          angulo,
          V[3];
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
};

#endif // ENTITY_H
