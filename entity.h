#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glut.h>

class Entity {
public:
    float radio,
          velocidad,
          angulo,
          V[3];
    bool vivo = true;

    virtual void update() {};
    virtual void draw(GLuint *texture) {};
    virtual void mata() {
        vivo = false;
    };
};

#endif // ENTITY_H