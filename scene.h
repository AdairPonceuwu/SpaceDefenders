#ifndef SD_SCENE
#define SD_SCENE

#include <vector>

#include "object.h"
#include "player.h"

//se define la cantidad de texturas que se manejaran
#define NTextures 20

class Scene {
public:
    std::vector<Object> objects;
    Player player;
    GLuint texture_map[NTextures];

    Scene() {}

    void init();
    void load_texture(char *filename, int index);
    void add_object(Object o);
    void kill_object(Object *o);
    void draw_objects();
    void draw_player();
    void reset();
};

#endif // SD_SCENE
