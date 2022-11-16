#include <GL/glut.h>
#include <cassert>
#include <string>


#include "object.h"

Object::Object(float x, float y, float z) {
    assert(false && "Object constructor not implemented!");
}

Object::Object(std::string texture_path) {
    assert(false && "Object constructor not implemented!");
}

Object::Object(std::string texture_path, float x, float y, float z) {
    assert(false && "Object constructor not implemented!");
}

void Object::set_collision(bool val, float rad) {
    collision = val;
    if (val) {
        collision_rad = rad;
    }
}

bool Object::set_texture(GLuint *t) {
    texture = t;
}

bool Object::load_obj(std::string path) {
    assert(false && "load_obj not implemented!");
}

void Object::draw() {
    assert(false && "draw not implemented!");
}
