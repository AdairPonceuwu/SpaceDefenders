#ifndef SD_OBJECT
#define SD_OBJECT

#include <GL/glut.h>
#include <string>
#include <vector>

#include "utils.h"

class Object {
public:
    Object() {}
    Object(std::string path, GLuint *t);
    bool set_texture(GLuint *t);
    void load_obj(std::string path);

    void draw();
    void update(float v[3]);

private:
    bool loaded_texture = false;
    GLuint *texture;
    std::vector<float> vertices;
    std::vector<int> faces;

    float* parse_vert_line(std::string line);
    int* parse_face_line(std::string line);
};

#endif // SD_OBJECT
