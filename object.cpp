#include <GL/glut.h>

#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>

#include "object.h"

Object::Object(std::string path, GLuint *t) {
    load_obj(path);
    set_texture(t);
}

bool Object::set_texture(GLuint *t) {
    texture = t;
}

void Object::load_obj(std::string path) {
    std::ifstream file;
    std::string line;

    file.open(path);
    std::cout << "Loading " << path << std::endl;

    while (getline(file, line)) {
        if (line[0] == 'v' && line[1] == ' ') {
            float* verts = parse_vert_line(line);
            assert(verts != NULL && "Error reading vertice");

            vertices.push_back(verts[0]);
            vertices.push_back(verts[1]);
            vertices.push_back(verts[2]);
            delete[] verts;
        } else if (line[0] == 'f') {
            int *facs = parse_face_line(line);
            assert(facs != NULL && "Error reading face");

            faces.push_back(facs[0]);
            faces.push_back(facs[1]);
            faces.push_back(facs[2]);
            delete[] facs;
        }
    }

    file.close();
    std::cout << vertices[0] << std::endl;
}

void Object::draw() {
    assert(false && "draw not implemented!");
}

float* Object::parse_vert_line(std::string line) {
    line = line.substr(2);
    int size = line.size();
    char *c_line = new char[size + 1];
    float *out = new float[3];
    int i = 0;

    memcpy(c_line, line.c_str(), size);
    c_line[size] = 0;
    char *tok = strtok(c_line, " ");
    while (tok) {
        out[i++] = atof(tok);
        tok = strtok(NULL, " ");
    }

    delete[] c_line;
    if (i != 3) {
        delete[] out;
        return NULL;
    }

    return out;
}

int* Object::parse_face_line(std::string line) {
    line = line.substr(2);
    int size = line.size();
    char *c_line = new char[size + 1];
    int *out = new int[3];
    int i = 0;

    memcpy(c_line, line.c_str(), size);
    c_line[size] = 0;
    char *tok = strtok(c_line, " ");
    while (tok) {
        out[i++] = atoi(tok);
        tok = strtok(NULL, " ");
    }

    delete[] c_line;
    if (i != 3) {
        delete[] out;
        return NULL;
    }

    return out;
}

