#ifndef DISPARO_H
#define DISPARO_H

#include <stdio.h>

class Disparo {
    public:
        Disparo();
        Disparo(float x, float y, float z, bool disparo);
        virtual ~Disparo();
        void update(float delta);

        float velocidad = .005f;
        float disparoRadio= .08f;
        float V[3];
        bool disparo;
        float radio;
    protected:

    private:
};

#endif // DISPARO_H
