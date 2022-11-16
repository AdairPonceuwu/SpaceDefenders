#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
using namespace std;
#include "rgbimage.h"
#include "utils.h"
#include "player.h"
#include "scene.h"
#include "Nave.h"
#include "Enemy.h"
#include "Disparos.h"
//Borrar
#include <iostream>
#include <iterator>
#include <vector>

using std::cout; using std::endl;
using std::vector; using std::remove;


//Variables dimensiones de la pantalla
const int WIDTH = 1140;
const int HEIGTH = 648;
//VARIABLES MOVIMIENTO NAVE
bool izqDown = false;
bool derDown = false;
Scene s = Scene();
Nave alcon = Nave(0,0,.7f);
//float Radio=1.0;
GLfloat anguloSol = 0.0f;
//Enemies respawn
Enemy arrEnemies[50];
Disparos arrDisparos[200];
float delta=0.0000005;
float deltaS=0.005;
int shoots=0;
//vector<Enemy> arrEnemies;

//Dibujar enemigos
void cargarEnemigos(){
    int i=0;
    while(i<50){
    for (int r = 0; r < 10; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            arrEnemies[i]=(Enemy((-10/ 2) + r + .5f, 0, -15 + c,rand() % 360));
            i++;
        }
    }
}
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(s.player.fov_y, (GLfloat)WIDTH/HEIGTH, s.player.z_near, s.player.z_far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    s.player = Player();
    //s.player.glLookAt();
    glClearColor(0,0,0,0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    s.init();
}

void keypress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            s.player.keypress(key - 100);
            break;
    }

    glutPostRedisplay();
}

void keyrelease(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            s.player.keyrelease(key - 100);
            break;
    }
    glutPostRedisplay();
}
static void keyboardDown(BYTE key, int x, int y)
        {
            char k = (char)key;
            switch (k)
            {
                case 'a':
                case 'A':
                    izqDown = true;
                    break;
                case 'd':
                case 'D':
                    derDown = true;
                    break;
            }
            glutPostRedisplay();
}

 void keyboardUp(BYTE key, int x, int y)
{
            char k = (char)key;
            switch (k)
            {
                case 'a':
                case 'A':
                    izqDown = false;
                    break;
                case 'd':
                case 'D':
                    derDown = false;
                    break;
                case 's':
                case 'S':
                    arrDisparos[shoots]=(Disparos(alcon.V[0],alcon.V[1],alcon.V[2]-.85f,true));
                    shoots++;
            }
            glutPostRedisplay();
}

//Modificar posciones
void update(){
    Enemy enemigo = Enemy();
    Disparos shoot = Disparos();
    //Nave
    alcon.update(10,izqDown,derDown);
    //Enemigos
    for(int i=0;i<50;i++){
        arrEnemies[i];
        delta=delta+0.000005;
        arrEnemies[i].updateEnemy(delta);
    }
    //Disparos
    for(int i=0;i<200;i++){
            arrDisparos[i];
            deltaS=deltaS+.0008;
            arrDisparos[i].update(deltaS);
            if(arrDisparos[i].V[2]<-25||arrDisparos[i].V[2]>5){
                    arrDisparos[i].disparo=false;
            }

    }

    //Colisiones
    for(int i=0; i<50; i++)
    {
        for (int j=0; j<100; j++)
        {
            shoot = arrDisparos[j];
            if(arrDisparos[j].disparo)
            {
                double sumaRadios = arrEnemies[i].enemy_radio + arrDisparos[j].radio;
                double distanciaZ = arrEnemies[i].V[2]-arrDisparos[j].V[2];
                double distanciaX = arrEnemies[i].V[0]-arrDisparos[j].V[0];
                if(arrEnemies[i].condicion&&(sumaRadios*sumaRadios)>((distanciaZ*distanciaZ)+(distanciaX*distanciaX)))
                {
                    arrEnemies[i].muerto();
                    arrDisparos[j].disparo=false;
               }
            }
            else
            {
                double sumaRadios = alcon.radio + arrEnemies[i].enemy_radio;
                double distanciaZ = alcon.V[2] - arrEnemies[i].V[2];
                double distanciaX = alcon.V[0] - arrEnemies[i].V[0];
                if((sumaRadios*sumaRadios)>((distanciaZ*distanciaZ)+(distanciaX*distanciaX)))
                {
                    alcon.muerto();
                }
            }
        }
    }
}

//Dibujar nave
void dibujarNave(){
    if(!alcon.condicion)return;
    glPushMatrix();
    glTranslated(alcon.V[0],alcon.V[1],alcon.V[2]);
    glRotated(180,1,0,0);
    glutSolidCone(alcon.radio,.8,100,100);
    glPopMatrix();
}
//Dibujar enemigos
void dibujarEnemies(){
    Enemy enemigo=Enemy();
    for(int i = 0;i<50;i++){
        enemigo=arrEnemies[i];
        if(arrEnemies[i].condicion){
        glPushMatrix();
        glTranslated(enemigo.V[0],enemigo.V[1],enemigo.V[2]);
        glRotated(enemigo.angulo,0,1,0);
        glRotated(270,1,0,0);
       // enemigo.updateEnemy(delta);
        glutSolidCone(enemigo.enemy_radio,0.3f,100,100);
        glTranslated(0,0.2f,.1);
        glutSolidCube(.2f);
        glPopMatrix();
        }
    }
}

void dibujarDisparos(){
    Disparos shoot = Disparos();
    for(int i = 0;i<100;i++){
        shoot=arrDisparos[i];
        if(arrDisparos[i].disparo){
        glPushMatrix();
        glTranslated(shoot.V[0],shoot.V[1],shoot.V[2]);
        glutSolidSphere(shoot.radio,100,100);
        glPopMatrix();
        }
    }

}
//--------------------------------------------------------------------------
void display() {
    gluLookAt(alcon.V[0],6,2,alcon.V[0],0,-4,0,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    update();
    drawAxis();
    //drawSphere();
    //drawRock(&anguloSol, s.texture_map);
    dibujarNave();
    dibujarEnemies();
    dibujarDisparos();
    glutSwapBuffers();
    glLoadIdentity();
    //s.player.update_pos();
    //s.player.glLookAt();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WIDTH, HEIGTH);
    glutCreateWindow("SpaceDefender");
    init();
    cargarEnemigos();
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    //glutSpecialFunc(keypress);
    //glutSpecialUpFunc(keyrelease);
    glutMainLoop();
    return 0;
}

