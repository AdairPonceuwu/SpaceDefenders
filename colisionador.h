#ifndef COLISIONADOR_H
#define COLISIONADOR_H

#include <cmath>

#include "enemy.h"
#include "disparo.h"
#include "nave.h"

class Colisionador {
public:
    Colisionador() {}

    bool checa(Nave *n, Enemy *e) {
        float di = dist(n->V, e->V),
              suma_r = n->radio + e->radio;

        return di <= suma_r;
    }

    bool checa(Disparo *d, Enemy *e) {
        float di = dist(d->V, e->V),
              suma_r = d->radio + e->radio;

        return di <= suma_r;
    }

private:
    float dist(float a[3], float b[3]) {
        float x = a[0] - b[0],
              y = a[1] - b[1],
              z = a[2] - b[2];
        return sqrt(
            (x * x) +
            (y * y) +
            (z * z)
        );
    }
};

#endif // COLISIONADOR_H
