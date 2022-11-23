#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
    float radio,
          velocidad,
          angulo,
          V[3];
    bool vivo = true;

    virtual void update() {};
    virtual void draw() {};
    virtual void muerto() {};
};

#endif // ENTITY_H
