#ifndef NAVE_H
#define NAVE_H

class Nave {
public:
    Nave(float x, float y, float z);
    Nave();
    virtual ~Nave();

    float velocidad = .0055f;
    float radio = .25f;
    float V[3];
    bool condicion = true;//true vivo, false muerto

    void update(float delta, bool izq, bool der,bool adelante, bool atras);
    void muerto();
};

#endif // NAVE_H
