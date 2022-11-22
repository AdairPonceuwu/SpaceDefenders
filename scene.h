#ifndef SD_SCENE
#define SD_SCENE

#include <GL/glut.h>
#include <vector>

#include "object.h"
#include "nave.h"
#include "disparo.h"

//se define la cantidad de texturas que se manejaran
#define NTextures 20
#define NDisparos 30

class Scene {
public:
    std::vector<Object> objects;
    std::vector<Disparo> disparos;
    GLuint texture_map[NTextures];
    Nave nave;

    Scene();

    void init();
    void load_texture(char *filename, int index);
    void dispara();
    void add_object(Object o);
    void kill_object(Object *o);
    void draw_objects();
    void draw_player();
    void reset();
    void update();
    void draw();
};

#endif // SD_SCENE
