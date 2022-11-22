#include "disparo.h"

Disparo::Disparo() {}
Disparo::Disparo(float x, float y, float z, bool disparos) {
    disparo = disparos;
    V[0] = x;
    V[1] = y;
    V[2] = z;
    radio = disparoRadio;
}

Disparo::~Disparo() {}

void Disparo::update(float delta) {
    if (disparo) {
        V[2] -= velocidad * delta;
    } else {
        V[2] += velocidad * delta;
    }
}
