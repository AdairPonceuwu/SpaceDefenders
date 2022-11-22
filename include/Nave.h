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
    // mapa de teclas
    // 0 - izq
    // 1 - der
    // 2 - adelante
    // 3 - atras
    bool teclas[4] = { false };

    void update(float delta);
    void muerto();
};

#endif // NAVE_H
