#ifndef NAVE_H
#define NAVE_H

#include "entity.h"

class Nave : public Entity {
public:
    Nave(float x, float y, float z);
    Nave();
    virtual ~Nave();
    void update(float delta);
    void draw();
    void muerto();

    // mapa de teclas
    // 0 - izq
    // 1 - der
    // 2 - adelante
    // 3 - atras
    bool teclas[4] = { false };
};

#endif // NAVE_H
