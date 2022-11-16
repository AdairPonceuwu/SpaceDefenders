#ifndef DISPAROS_H
#define DISPAROS_H
#include <stdio.h>

class Disparos
{
    public:
        Disparos();
        Disparos(float x, float y, float z, bool disparo);
        float velocidad = .005f;
        float disparoRadio= .05f;
        float V[3];
        bool disparo;
        float radio;
        virtual ~Disparos();
        void update(float delta);
    protected:

    private:
};

#endif // DISPAROS_H
