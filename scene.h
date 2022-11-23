#ifndef SD_SCENE
#define SD_SCENE

#include <GL/glut.h>
#include <vector>

#include "object.h"
#include "nave.h"
#include "disparo.h"
#include "enemy.h"
#include "colisionador.h"

#define NTextures 20
#define NObjects 3
#define NDisparos 30
#define NEnemies 30

class Scene {
public:
    GLuint texture_map[NTextures];
    Object objects[NObjects];
    Colisionador c = Colisionador();
    std::vector<Enemy> enemies;
    std::vector<Disparo> disparos;
    Nave nave;

    Scene();

    void init();
    void load_texture(char *filename, int index);
    void dispara();
    void update();
    void draw();
};

#endif // SD_SCENE
