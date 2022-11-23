#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "rgbimage.h"
#include "utils.h"
#include "scene.h"
#include "nave.h"
#include "enemy.h"
#include "disparos.h"

//Sistema Solar
int year=0, day=0;
int year_1=0,day_1=0;
int year_2=0,day_2=0;
int solE=0;
int planet1=0;
int satelite=0;

// Constantes varias
const int WIDTH = 1140,
          HEIGTH = 648;
const float FOV_Y = 60.6,
            Z_NEAR = 0.01,
            Z_FAR = 100.0;
int delta_t = 0, odelta_t = 0;

Scene s = Scene();

GLfloat anguloSol = 0.0f;

float luz_difusa[] = {1, 1, 1, 0};

static void keyboardDown(BYTE key, int x, int y) {
    switch (key) {
        case 'a':
        case 'A':
            s.nave.teclas[0] = true;
            break;
        case 'd':
        case 'D':
            s.nave.teclas[1] = true;
            break;
        case 'w':
        case 'W':
            s.nave.teclas[2] = true;
            break;
        case 's':
        case 'S':
            s.nave.teclas[3] = true;
            break;
        case 'r':
        case 'R':
            if(s.nave.vivo) {
                s.gen_enemy_wave();
            }
            break;
    }
    glutPostRedisplay();
}

void keyboardUp(BYTE key, int x, int y) {
    switch (key) {
        case 'a':
        case 'A':
            s.nave.teclas[0] = false;
            break;
        case 'd':
        case 'D':
            s.nave.teclas[1] = false;
            break;
        case 'w':
        case 'W':
            s.nave.teclas[2] = false;
            break;
        case 's':
        case 'S':
            s.nave.teclas[3] = false;
            break;
        case 'L':
        case 'l':
            s.dispara();
    }
    glutPostRedisplay();
}

//Fondo
void dibujarFondo(){
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glTranslated(0, 0, -25);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, s.texture_map[6]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-60.0f, -60.0f, 4.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(60.0f, -60.0f, 4.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(60.0f, 60.0f, 4.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-60.0f, 60.0f, 4.0f);
    glEnd();
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glLoadIdentity();
}

//Dibujado del Sistema solar
void drawSistemaSolar(){
    glPushMatrix();
    glTranslated(6,-5,-10);
    glRotated(solE,0.0,1.0,0.0);
    drawSphere(1,15,15,s.texture_map[7]);
    glPushMatrix();
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glutSolidTorus(0.01f, 1.5f, 50, 50);
    glutSolidTorus(0.01f, 2.5f,50, 50 );
    glutSolidTorus(0.01f, 5.0f,50, 50 );
    glPopMatrix();
    glPushMatrix();
    glRotated(year,0.0,1.0,0.0);
    glTranslated(2.7,0,0);
    glPushMatrix();
    glScaled(.5,.5,.5);
    glRotated(day,0.0,1.0,0.0);
    drawSphere(.8,12,12,s.texture_map[9]);
    glPopMatrix();
    glRotated(satelite,1.0,0.0,0.0);
    glTranslated(0,1.5,0);
    drawSphere(.3,12,12,s.texture_map[10]);
    glPopMatrix();

    //DIBUJA MARTE
     glPushMatrix();
     glRotatef(year,0,1,0);
     glTranslatef(-2.7,0.0,0.0);
     glPushMatrix();
     glRotatef(day,0,1,0);
     drawSphere(0.3,10,10,s.texture_map[14]);
     glPopMatrix();
     glPopMatrix();

    //DIBUJA MERCURIO
     glPushMatrix();
     glRotated(year_1,0.0,1.0,0.0);
     glTranslatef(1.5,0.0,0.0);
     glPushMatrix();
     glRotatef(day_1,0,1,0);
     drawSphere(0.15,10,10,s.texture_map[11]);
     glPopMatrix();
     glPopMatrix();

    //DIBUJA VENUS
     glPushMatrix();
     glRotated(year_1,0.0,1.0,0.0);
     glTranslatef(-1.5,0.0,0.0);
     glPushMatrix();
     glRotatef(day_1,0,1,0);
     drawSphere(0.15,10,10,s.texture_map[13]);
     glPopMatrix();
     glPopMatrix();

    //DIBUJA SATURNO
     glPushMatrix();
     glRotated(year_2,0.0,1.0,0.0);
     glTranslatef(5.0,0.0,0.0);
     glPushMatrix();
     glRotatef(day_2, 0, 1, 0);
     glRotatef(90, 1.0f, 1.0f, 0.0f);
     drawSphere(0.6,15,15,s.texture_map[12]);
     glColor3f(0.5f, 0.5f, 0.5f);//Violet
     glutSolidTorus(0.1f, 0.9f,20, 20 );
     glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
     glutSolidTorus(0.08f, 1.0f,20, 20 );
     glColor3f(0.5f, 0.5f, 0.5f);//Violet
     glutSolidTorus(0.08f, 1.02f,20, 20 );
     glColor3f(0.5f, 0.5f, 0.5f);//Violet
     glutSolidTorus(0.1f, 1.05f,50, 50 );
     glPopMatrix();
     glPopMatrix();

    //DIBUJA JUPITER
    glPushMatrix();
    glRotatef(year_2, 0, 1, 0);
    glTranslatef(-5.0,0.0,0.0);
    glPushMatrix();
    glRotatef(day_2, 0, 1, 0);
    drawSphere(0.6,15,15,s.texture_map[5]);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}
//Dibujando estrellas
/*void drawSistemaEstrellas(){
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
}*/
void drawSistemaRocka(){

    glPushMatrix();
    glScaled(0.9, 0.9, 0.9);
    glTranslated(-7, -5, -10);
    glRotated(solE, 0.0, 1.0, 0.0);
    drawStar(&anguloSol, s.texture_map[1]);
    glPushMatrix();
    glRotated(satelite, 1.0, 0.0, 0.0);
    glScaled(0.5, 0.5, 0.5);
    glTranslated(0, 1.5 ,0);
    drawStar(&anguloSol, s.texture_map[0]);
    glPopMatrix();
    //Dibuja Orbitas
    glPushMatrix(); //Sistema de base de referencia
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glutSolidTorus(0.01f, 1.5f, 50, 50);
    glutSolidTorus(0.01f, 2.5f,50, 50 );
    glutSolidTorus(0.01f, 5.0f,50, 50 );
    glPopMatrix();


    //Rocka 1
    glPushMatrix();
    glScaled(0.2, 0.2, 0.2);
    glRotatef(year_1, 0, 1, 0);
    glTranslatef(-6.5, 0.0, 0.0);
    glPushMatrix();
    glRotatef(day_1, 0, 1, 0);
    drawRock(s.texture_map[9]);
    glPopMatrix();
    glPopMatrix();

    //Rocka 2
     glPushMatrix();
     glScaled(0.25, 0.25, 0.25);
     glRotated(year_2, 0.0, 1.0, 0.0);
     glTranslatef(9.5, 0.0, 0.0);
     glPushMatrix();
     glRotatef(day_2, 0, 1, 0);
     drawRock(s.texture_map[16]);
     glPopMatrix();
     glPopMatrix();

     //Rocka 3
     glPushMatrix();
     glScaled(0.5, 0.5, 0.5);
     glRotated(year, 0.0, 1.0, 0.0);
     glTranslatef(10, 0.0, 0.0);
     glPushMatrix();
     glRotatef(day, 0, 1, 0);
     drawRock(s.texture_map[15]);
     glPopMatrix();
     glPopMatrix();

     //Rocka 3.1
     glPushMatrix();
     glScaled(0.5, 0.5, 0.5);
     glRotated(year, 0.0, 1.0, 0.0);
     glTranslatef(-10, 0.0, 0.0);
     glPushMatrix();
     glRotatef(day, 0, 1, 0);
     drawRock(s.texture_map[8]);
     glPopMatrix();
     glPopMatrix();

    glPopMatrix();

}
//Modificar posciones
void update(){
    //Sistema Solar
    DWORD TiempoActual = 0;
    DWORD LastUpdate = 0;
    DWORD Lapso = 0;
    TiempoActual = GetTickCount();
    Lapso = TiempoActual - LastUpdate;

    if (Lapso >= 30){
        year = (year + 1) % 360;
        solE = (solE - 2) % 360;
        day = (day + 2) % 360;
        year_1 = (year_1 + 4) % 360;
        year_2 = (year_2+3) % 360;
        LastUpdate = TiempoActual;
        satelite = (satelite - 4) % 360;
        day_2 = (day_2 - 4) % 360;
        day_1 = (day_1 - 3) % 360;
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

    delta_t = glutGet(GLUT_ELAPSED_TIME);
    s.update(delta_t - odelta_t);
    odelta_t = delta_t;
    drawAxis();
    s.draw();
    // drawSistemaEstrellas();
    drawSistemaRocka();
    drawSistemaSolar();
    dibujarFondo();
    glutSwapBuffers();
    glLoadIdentity();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    luz();
    gluPerspective(FOV_Y, (GLfloat)WIDTH/HEIGTH, Z_NEAR, Z_FAR);
    gluLookAt(s.nave.V[0], 5, 2, s.nave.V[0], 0, -4, 0, 1, 0);
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
    glutInitWindowPosition(300,150);
    glutInitWindowSize(WIDTH, HEIGTH);
    glutCreateWindow("SpaceDefender");
    init();
    dibujarFondo();
    //cargarEnemigos();
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    printf("Comenzar juego:R\n");
    printf("Adelante:W\n");
    printf("Atras:S\n");
    printf("Derecha:D\n");
    printf("Izquierda:A\n");
    printf("Disparar:L\n");
    //glutSpecialFunc(keypress);
    //glutSpecialUpFunc(keyrelease);
    glutMainLoop();
    return 0;
}
