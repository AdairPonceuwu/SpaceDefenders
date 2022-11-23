#include <cassert>
#include <iostream>

#include "scene.h"
#include "object.h"
#include "enemy.h"

Scene::Scene() {
    disparos.reserve(NDisparos);
    enemies.reserve(NEnemies);
}

void Scene::init() {
    const int T = 17;
    char *archivos[T] = {
        "texturas/Estrella.bmp",
        "texturas/Laser3.bmp",
        "texturas/Enemigo4.bmp",
        "texturas/Laser4.bmp",
        "texturas/Enemigos3.bmp",
        "texturas/Planetas/jupiter.bmp",
        "texturas/Fondo13.bmp",
        "texturas/Sol2.bmp",
        "texturas/Asteroide2.bmp",
        "texturas/Planeta1.bmp",
        "texturas/Satelite1.bmp",
        "texturas/Planetas/mercurio.bmp",
        "texturas/Planetas/saturno.bmp",
        "texturas/Planetas/venus.bmp",
        "texturas/Planetas/marte.bmp",
        "texturas/Asteroide.bmp",
        "texturas/Planetas/Asteroide3.bmp",
    };

    for (int i = 0; i < T; ++i) {
        load_texture(archivos[i], i);
    }
}

void Scene::load_texture(char *filename, int index) {
	glClearColor (0.0, 0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap( filename );

    //generate an OpenGL texture ID for this texture
    glGenTextures(1, &texture_map[index]);
    //bind to the new texture ID
    glBindTexture(GL_TEXTURE_2D, texture_map[index]);


    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0,
                     GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
    theTexMap.Reset();
}

void Scene::dispara() {
    if (disparos.size() < NDisparos) {
        float x = nave.V[0],
              y = nave.V[1],
              z = nave.V[2] - 0.85;

        disparos.push_back(Disparo(x, y, z));
        std::cout << "Disparando!" << std::endl;
    }
}

void Scene::draw_objects() {
    assert(false && "draw_objects not implemented!");
}

void Scene::draw_player() {
    assert(false && "draw_player not implemented!");
}

void Scene::reset() {
    assert(false && "reset not implemented!");
}

void Scene::update() {
    nave.update(10);

    // avanza disparos
    bool d_elim[NDisparos] = { false };
    for (int i = 0; i < disparos.size(); ++i) {
        disparos[i].update(10);
        if (!disparos[i].vivo) {
            d_elim[i] = true;
        }
    }

    // elimina aquellos que se salieron de rango
    for (int i = 0; i < disparos.size(); ++i) {
        if (d_elim[i]) {
            disparos.erase(disparos.begin() + i);
        }
    }
}

void Scene::draw() {
    nave.draw(0);
    for (int i = 0; i < disparos.size(); ++i) {
        disparos[i].draw(texture_map[3]);
    }
}
