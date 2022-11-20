#include <cassert>

#include "scene.h"
#include "object.h"

void Scene::init() {
    char* filename0 = "texturas/Estrella.bmp";
    char* filename1 = "texturas/Laser3.bmp";
    char* filename2 = "texturas/Enemigo4.bmp";
    char* filename3 = "texturas/Laser4.bmp";
    char* filename4 = "texturas/Enemigos3.bmp";
    char* filename5 = "texturas/Planetas/jupiter.bmp";
    char* filename6 = "texturas/Fondo13.bmp";
    char* filename7 = "texturas/Sol2.bmp";
    char* filename8 = "texturas/Asteroide2.bmp";
    char* filename9 = "texturas/Planeta1.bmp";
    char* filename10 = "texturas/Satelite1.bmp";
    char* filename11 = "texturas/Planetas/mercurio.bmp";
    char* filename12 = "texturas/Planetas/saturno.bmp";
    char* filename13 = "texturas/Planetas/venus.bmp";
    char* filename14 = "texturas/Planetas/marte.bmp";

    load_texture(filename0, 0);
    load_texture(filename1, 1);
    load_texture(filename2, 2);
    load_texture(filename3, 3);
    load_texture(filename4, 4);
    load_texture(filename5, 5);
    load_texture(filename6, 6);
    load_texture(filename7, 7);
    load_texture(filename8, 8);
    load_texture(filename9, 9);
    load_texture(filename10, 10);
    load_texture(filename11, 11);
    load_texture(filename12, 12);
    load_texture(filename13, 13);
    load_texture(filename14, 14);
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

void Scene::add_object(Object o) {
    assert(false && "add_object not implemented!");
}

void Scene::kill_object(Object *o) {
    assert(false && "kill_object not implemented!");
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
