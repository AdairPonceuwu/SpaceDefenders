#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "rgbimage.h"
#include "utils.h"
#include "player.h"
#include "scene.h"
#include "Nave.h"
#include "Enemy.h"
#include "Disparos.h"
//Sistema Solar
int year=0, day=0;
int year_m=0,day_m=0;
int sol=0;
int planet1=0;
int satelite=0;
//Variables dimensiones de la pantalla
const int WIDTH = 1140;
const int HEIGTH = 648;
//VARIABLES MOVIMIENTO NAVE
bool izqDown = false;
bool derDown = false;
bool adelanteDown = false;
bool atrasDown = false;
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
//Iluminasion
float luz_ambiente[]={0.5,0.7,0,0};
float luz_difusa[]={1,1,1,0};


//Dibujar enemigos
void cargarEnemigos(){
    int i=0;
    while(i<40){
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
                case 'w':
                case 'W':
                    adelanteDown=true;
                    break;
                case 's':
                case 'S':
                    atrasDown=true;
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
                case 'w':
                case 'W':
                    adelanteDown=false;
                    break;
                case 's':
                case 'S':
                    atrasDown=false;
                    break;
                case 'L':
                case 'l':
                    arrDisparos[shoots]=(Disparos(alcon.V[0],alcon.V[1],alcon.V[2]-.85f,true));
                    shoots++;
            }
            glutPostRedisplay();
}


//Dibujar nave
void dibujarNave(){
    if(!alcon.condicion)exit(1);
    glPushMatrix();
    glTranslated(alcon.V[0],alcon.V[1],alcon.V[2]);
    glRotated(180,1,0,0);
    glutSolidCone(alcon.radio,.8,100,100);
    glPopMatrix();
}
//Dibujar enemigos
void dibujarEnemies(){
    Enemy enemigo=Enemy();
    for(int i = 0;i<40;i++){
        enemigo=arrEnemies[i];
        if(arrEnemies[i].condicion&&arrEnemies[i].V[2]!=0){
        glPushMatrix();
        glTranslated(enemigo.V[0],enemigo.V[1],enemigo.V[2]);
        glRotated(enemigo.angulo,0,1,0);
        glRotated(270,1,0,0);
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
        if(arrDisparos[i].disparo && alcon.condicion){
        glPushMatrix();
        glTranslated(shoot.V[0],shoot.V[1],shoot.V[2]);
        glutSolidSphere(shoot.radio,100,100);
        glPopMatrix();
        }
    }

}
void dibujarFondo(){
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glTranslated(0,0,-25);
    glColor3f(1.0f,1.0f,1.0f);
    glBindTexture(GL_TEXTURE_2D,s.texture_map[6]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f); glVertex3f(-60.0f,-60.0f,4.0f);
    glTexCoord2f(1.0f,0.0f); glVertex3f(60.0f,-60.0f,4.0f);
    glTexCoord2f(1.0f,1.0f); glVertex3f(60.0f,60.0f,4.0f);
    glTexCoord2f(0.0f,1.0f); glVertex3f(-60.0f,60.0f,4.0f);
    glEnd();
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glLoadIdentity();
}
void setMaterial(GLfloat ambientR,GLfloat ambientG,GLfloat ambientB,
                 GLfloat diffuseR,GLfloat diffuseG, GLfloat diffuseB,
                 GLfloat specularR, GLfloat specularG, GLfloat specularB){
                 GLfloat ambient[]={ambientR,ambientG,ambientB};
                 GLfloat diffuse[]={diffuseR,diffuseG,diffuseB};
                 GLfloat specular[]={specularR,specularG,specularB};
                 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
                 glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
                 glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
}
//Dibujado tipo planetas y sol
void drawSistemaSolar(){
    glPushMatrix();
    glTranslated(6,-5,-10);
    glRotated(sol,0.0,1.0,0.0);
    drawSphere(1,15,15,s.texture_map[7]);
    glRotated(year,0.0,1.0,0.0);
    glTranslated(2,0,0);
    glPushMatrix();
    glScaled(.5,.5,.5);
    glRotated(day,0.0,1.0,0.0);
    drawSphere(.8,12,12,s.texture_map[9]);
    glPopMatrix();
    glRotated(satelite,1.0,0.0,0.0);
    glTranslated(0,1.5,0);
    drawSphere(.3,12,12,s.texture_map[10]);
    glPopMatrix();
}
//Dibujando estrellas
void drawSistemaEstrellas(){
    glPushMatrix();
    glScaled(2,2,2);
    glTranslated(-6,-5,-10);
    glRotated(day,0.0,1.0,0.0);
    drawStar(&anguloSol,s.texture_map[1]);
    glPushMatrix();
    glRotated(satelite,1.0,0.0,0.0);
    glScaled(0.5,0.5,0.5);
    glTranslated(0,1.5,0);
    drawStar(&anguloSol,s.texture_map[0]);
    glPopMatrix();
    glPopMatrix();
}

//Modificar posciones
void update(){
    Enemy enemigo = Enemy();
    Disparos shoot = Disparos();
    //Nave
    alcon.update(10,izqDown,derDown,adelanteDown,atrasDown);
    //
    //Enemigos
    for(int i=0;i<40;i++){
        arrEnemies[i];
        delta=delta+0.000005;
        arrEnemies[i].updateEnemy(delta);
    }
    //
    //Disparos
    for(int i=0;i<200;i++){
            arrDisparos[i];
            deltaS=deltaS+.0008;
            arrDisparos[i].update(deltaS);
            if(arrDisparos[i].V[2]<-25||arrDisparos[i].V[2]>5){
                    arrDisparos[i].disparo=false;
            }

    }
    //
    //Colisiones
    for(int i=0; i<40; i++)
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
                    arrEnemies[i].enemy_radio=0;
                    arrEnemies[i].muerto();
                    arrDisparos[j].disparo=false;
               }
            }
            else
            {
                double sumaRadios = alcon.radio + arrEnemies[i].enemy_radio;
                double distanciaX = alcon.V[0] - arrEnemies[i].V[0];
                double distanciaZ = alcon.V[2] - arrEnemies[i].V[2];
                if(arrEnemies[i].condicion&&(sumaRadios*sumaRadios)>((distanciaZ*distanciaZ)+(distanciaX*distanciaX)))
                {
                   alcon.muerto();
                }
            }
        }
    }
    //
    //Sistema Solar
    DWORD TiempoActual = 0;
    DWORD LastUpdate = 0;
    DWORD Lapso =0;
    TiempoActual = GetTickCount();
    Lapso = (TiempoActual - LastUpdate);

    if(Lapso>=30){
            year=((year+1)%360);
            sol=(sol-2)%360;
            day=(day+2)%360;
            LastUpdate-TiempoActual;
            satelite = (satelite-4)%360;

    }
}
//--------------------------------------------------------------------------
void luz(){
    glLightfv(GL_LIGHT0,GL_DIFFUSE,luz_difusa);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    update();
    drawAxis();
    dibujarNave();
    dibujarEnemies();
    dibujarDisparos();
    drawSistemaEstrellas();
    drawRock(&anguloSol, s.texture_map,-10,-15,-15,.8,.8,.8);
    drawSistemaSolar();
    drawCone(&anguloSol,s.texture_map[2]);
    dibujarFondo();
    glutSwapBuffers();
    glLoadIdentity();
}


void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    luz();
    gluPerspective(s.player.fov_y, (GLfloat)WIDTH/HEIGTH, s.player.z_near, s.player.z_far);
    gluLookAt(alcon.V[0],5,2,alcon.V[0],0,-4,0,1,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0,0,0,0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    s.init();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200,150);
    glutInitWindowSize(WIDTH, HEIGTH);
    glutCreateWindow("SpaceDefender");
    init();
    dibujarFondo();
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

