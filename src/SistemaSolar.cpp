#include "SistemaSolar.h"
#include "rgbimage.h"
#include "utils.h"
#include "player.h"
#include "scene.h"

SistemaSolar::SistemaSolar()
{
    //ctor
}

SistemaSolar::~SistemaSolar()
{
    //dtor
}

void SistemaSolar::drawSystem(){
    Scene s = Scene();
    glPushMatrix();
    drawSphere(&sol,s.texture_map[8],0.0,0.0,-5,2,2,2);
    glPopMatrix();
    glPushMatrix();
    glRotated(year,0.0,1.0,0.0);
    glTranslated(3,0,-5);
    glPushMatrix();
    drawSphere(&day,s.texture_map[1],0,0,0,.5,.5,.5);
    glPopMatrix();
    glRotated(satelite,1.0,0.0,0.0);
    drawSphere(&satelite,s.texture_map[2],0.0,1.5,-5,.2,.2,.2);
    glPopMatrix();
}
