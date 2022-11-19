#ifndef SD_OBJECT
#define SD_OBJECT

#include <GL/glut.h>
#include <string>

#include "utils.h"

class Object {
public:
    bool collision = false;
    float collision_rad;
    float pos[3] = { 0 };

    Object() {}
    Object(float x, float y, float z);
    Object(std::string texture_path);
    Object(std::string texture_path, float x, float y, float z);

    void set_collision(bool val, float rad);
    bool set_texture(GLuint *t);
    bool load_obj(std::string path);

    void draw();

protected:
    bool loaded_texture = false;
    GLuint *texture;
    float *vertices;
    int *faces;
};

#endif // SD_OBJECT
