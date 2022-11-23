#include <cassert>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

#include "scene.h"
#include "object.h"
#include "enemy.h"
#include "utils.h"

Scene::Scene() {
    disparos.reserve(NDisparos);
    enemies.reserve(NEnemies);
}

Enemy Scene::alien1(float x, float y, float z, float angulo) {
    Enemy e = Enemy(x, y, z, angulo);
    e.set_obj(&objects[0]);

    return e;
}

Enemy Scene::alien2(float x, float y, float z, float angulo) {
    Enemy e = Enemy(x, y, z, angulo);
    e.set_obj(&objects[1]);

    return e;
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

    objects[0] = Object("modelos/alien.obj", &texture_map[2]);
    objects[1] = Object("modelos/alien.obj", &texture_map[4]);
    objects[2] = Object("modelos/nave.obj", &texture_map[5]);
    nave.set_obj(&objects[2]);

    load_waves("oleadas/oleadas.ol");
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

void Scene::load_waves(char *filename) {
    std::ifstream file;
    std::string line = "";

    file.open(filename);
    std::cout << "Cargando oleadas" << std::endl;
    std::vector<char> wave;

    while (getline(file, line)) {
        trim(line);
        std::cout << line << std::endl;
        assert(
           line.length() <= 6 &&
           "No se permiten oleadas de más de 5 enemigos por fila."
       );

        if (line[0] == 'w') {
            if (wave.size() != 0) {
                waves.push_back(wave);
            }

            wave.clear();
            continue;
        }

        for (int i = 0; i < line.length(); ++i) {
            wave.push_back(line[i]);
        }
        // completa línea
        for (int i = 0; i < 6 - line.length(); ++i) {
            wave.push_back(' ');
        }
    }

    if (wave.size() != 0) {
        waves.push_back(wave);
    }
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

void Scene::update() {
    nave.update(10);

    // avanza disparos
    for (int i = 0; i < disparos.size(); ++i) {
        disparos[i].update(10);
    }

    // avanza enemigos
    for (int i = 0; i < enemies.size(); ++i) {
        enemies[i].update();

        // checa colisiones con nave
        if (c.checa(&nave, &enemies[i])) {
            nave.mata();
        }
    }

    // checa colisiones enemigo con disparo
    for (int i = 0; i < disparos.size(); ++i) {
        for (int j = 0; j < enemies.size(); ++j) {
            if (c.checa(&disparos[i], &enemies[j])) {
                disparos[i].mata();
                enemies[j].mata();
            }
        }
    }

    // elimina aquellos que se salieron de rango
    for (auto i = disparos.begin(); i < disparos.end(); ++i) {
        if (!i->vivo) {
            disparos.erase(i);
        }
    }

    for (auto i = enemies.begin(); i < enemies.end(); ++i) {
        if (!i->vivo) {
            enemies.erase(i);
        }
    }
    active_wave = enemies.size() != 0;
}

void Scene::draw() {
    // dibuja nave
    nave.draw();

    // dibuja disparos
    for (int i = 0; i < disparos.size(); ++i) {
        disparos[i].draw(&texture_map[3]);
    }

    // dibuja enemigos
    for (int i = 0; i < enemies.size(); ++i) {
        enemies[i].draw();
    }
}

void Scene::gen_enemy_wave() {
    if (active_wave) {
        return;
    }

    if (wave_index == waves.size()) {
        std::cout << "No hay más oleadas" << std::endl;
        return;
    }

    const float X_SPACE = 0.8,
                X_BOTTOM = -4.5,
                Z_SPACE = -0.8,
                Z_BOTTOM = -20;

    active_wave = true;
    Enemy e;

    float x, z;
    int c = 0, j = 0;

    for (int i = 0; i < waves[wave_index].size(); ++i) {
        std::cout << waves[wave_index][i] << std::endl;
    }

    while (c < waves[wave_index].size()) {
        for (int i = 0; i < 6; ++i) {
            x = X_BOTTOM + i + (i * X_SPACE);
            z = Z_BOTTOM - j + (j * Z_SPACE);

            switch(waves[wave_index][c]) {
            case 'a':
                e = alien1(x, 0, z, rand() % 360);
                enemies.push_back(e);
                break;
            case 'A':
                e = alien2(x, 0, z, rand() % 360);
                enemies.push_back(e);
                break;
            }

            c++;
        }
        ++j;
    }
    wave_index++;
}
