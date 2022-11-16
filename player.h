#ifndef SD_PLAYER
#define SD_PLAYER

#include <GL/glut.h>
#include <stdio.h>

class Player {
public:
    Player() {
        fov_y = 60.0;
        z_near = 0.01;
        z_far = 100.0;
    }

    Player(float fov, float zn, float zf) {
        fov_y = fov;
        z_near = zn;
        z_far = zf;
    }

    //Variables para matrices de rotacion y traslación
    //La inicializacion del angulo depende de la posicion inicial del observador y su
    //direccion
    float dir[3] = {0.0,-1.0,0.0};
    float theta = 0;

    //Variables para establecer los valores de gluPerspective
    float fov_y;
    float z_near;
    float z_far;

    //Variables para definir la posicion del observador
    //Por default se inicializa en (0,0,0) y mirando hacia x positivo
    //gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z)
    float EYE_X = 0.0;
    float EYE_Y = 8.0;
    float EYE_Z = 0.0;
    float CENTER_X = 0;
    float CENTER_Y = 0;
    float CENTER_Z = 0;
    float UP_X = 1;
    float UP_Y = 1;
    float UP_Z = 0;

    // mapa de teclas
    // 0 - izq
    // 1 - arriba
    // 2 - derecha
    // 3 - abajo
    bool arrowkeys[4] = { false };

    void glLookAt() {
        gluLookAt(
            EYE_X, EYE_Y, EYE_Z,
            CENTER_X, CENTER_Y, CENTER_Z,
            UP_X, UP_Y, UP_Z
        );
    }

    /// sin uso
    void look_at_lr() {
        // si estuviera sobre el plano xz, mirando hacia x o z
        // se podria usar esta funcion para girar la vista
        float x, z, r = DegToRad(theta);

        x = dir[0]*cos(r) + dir[2]*sin(r);
        z = -dir[0]*sin(r) + dir[2]*cos(r);
        dir[0] = x;
        dir[2] = z;
        CENTER_X = EYE_X + dir[0];
        CENTER_Z = EYE_Z + dir[2];
    }

    void keypress(int key) {
        arrowkeys[key] = true;
        printf("pressed %d\n", key);
    }

    void keyrelease(int key) {
        arrowkeys[key] = false;
        printf("released %d\n", key);
    }

    void update_pos() {
        dir[0] = 0;
        dir[2] = 0;
        if (arrowkeys[0]) { dir[2] = -0.05; }
        if (arrowkeys[1]) { dir[0] = 0.05; }
        if (arrowkeys[2]) { dir[2] = 0.05; }
        if (arrowkeys[3]) { dir[0] = -0.05; }

        EYE_X += dir[0];
        EYE_Z += dir[2];
        CENTER_X += dir[0];
        CENTER_Z += dir[2];
    }
};

#endif // SD_PLAYER
