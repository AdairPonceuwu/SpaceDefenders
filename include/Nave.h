#ifndef NAVE_H
#define NAVE_H

class Nave {
public:
    Nave(float x, float y, float z);
    Nave();
    virtual ~Nave();
    void update(float delta);
    void muerto();

    float V[3];
    bool vivo = true; //true vivo, false muerto
    float velocidad = .0055f;
    float radio = .25f;
    // mapa de teclas
    // 0 - izq
    // 1 - der
    // 2 - adelante
    // 3 - atras
    bool teclas[4] = { false };
};

#endif // NAVE_H
