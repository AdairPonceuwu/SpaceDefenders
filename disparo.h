#ifndef DISPARO_H
#define DISPARO_H

#include <GL/glut.h>
#include <stdio.h>

class Disparo {
public:
    Disparo();
    Disparo(float x, float y, float z);
    virtual ~Disparo();
    void update(float delta);
    void draw(GLuint texture);

    float velocidad = 0.005f;
    float disparoRadio = 0.08f;
    float V[3];
    float radio;
    bool fuera_de_rango = false;
};

#endif // DISPARO_H
