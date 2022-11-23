#ifndef SD_SCENE
#define SD_SCENE

#include <GL/glut.h>
#include <vector>

#include "object.h"
#include "nave.h"
#include "disparo.h"
#include "enemy.h"

#define NTextures 20
#define NDisparos 30
#define NEnemies 30

class Scene {
public:
    std::vector<Enemy> enemies;
    std::vector<Disparo> disparos;
    GLuint texture_map[NTextures];
    Nave nave;

    Scene();

    void init();
    void load_texture(char *filename, int index);
    void dispara();
    void draw_objects();
    void draw_player();
    void reset();
    void update();
    void draw();
};

#endif // SD_SCENE
