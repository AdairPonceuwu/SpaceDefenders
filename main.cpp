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

Scene s = Scene();

//float Radio=1.0;
GLfloat anguloSol = 0.0f;
//Enemies respawn
Enemy arrEnemies[30];
Enemy arrEnemiesRocks[30];
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
    float x=0;
    float z=0;
    while(i<30){
    for (int r = 0; r < 10; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            arrEnemies[i]=(Enemy((-8/ 2) + r +0.5f+x, 0, -20 + c+z,rand() % 360));
            //arrEnemiesRocks[i]=(Enemy((-8/ 2) + r +0.5f+x, 0, -20 + c+z,rand() % 360));
            i++;
            z+=0.5;
        }
        x+=0.6;
        z=0;
    }
}
}

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
            if(s.nave.vivo){
                cargarEnemigos();
                printf("Juego iniciado\n");
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
            arrDisparos[shoots]=(Disparos(s.nave.V[0],s.nave.V[1],s.nave.V[2]-.85f,true));
            shoots++;
    }
    glutPostRedisplay();
}


//Dibujar nave
void dibujarNave(){
    if(!s.nave.vivo){printf("GAME OVER\n");exit(1);}
    glPushMatrix();
    glTranslated(s.nave.V[0], s.nave.V[1],s.nave.V[2]);
    glRotated(180,1,0,0);
    glutSolidCone(s.nave.radio,.8,100,100);
    glPopMatrix();
}
//Dibujar enemigos
void dibujarEnemies(){
    Enemy enemigo=Enemy();
    for(int i = 0;i<30;i++){
        enemigo=arrEnemies[i];
        if(arrEnemies[i].condicion&&arrEnemies[i].V[2]!=0){
        glPushMatrix();
        //glScaled(1,1,1);
        glTranslated(enemigo.V[0],enemigo.V[1],enemigo.V[2]);
        glRotated(enemigo.angulo,0,1,0);
        if(i%2==0){
            drawCone(s.texture_map[2]);
        }else{
            drawCone(s.texture_map[4]);
        }
        glPopMatrix();
        }
    }
}
//Disparos
void dibujarDisparos(){
    Disparos shoot = Disparos();
    for(int i = 0;i<200;i++){
        shoot=arrDisparos[i];
        if(arrDisparos[i].disparo && s.nave.vivo){
            glPushMatrix();
            glTranslated(shoot.V[0],shoot.V[1],shoot.V[2]);
            drawSphere(shoot.radio,100,100,s.texture_map[3]);
            glPopMatrix();
        }
    }

}
//Fondo
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
    glScaled(.9,.9,.9);
    glTranslated(-7,-5,-10);
    glRotated(solE,0.0,1.0,0.0);
    drawStar(&anguloSol,s.texture_map[1]);
    glPushMatrix();
    glRotated(satelite,1.0,0.0,0.0);
    glScaled(0.5,0.5,0.5);
    glTranslated(0,1.5,0);
    drawStar(&anguloSol,s.texture_map[0]);
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
    glScaled(.2,.2,.2);
    glRotatef(year_1,0,1,0);
    glTranslatef(-6.5,0.0,0.0);
    glPushMatrix();
    glRotatef(day_1,0,1,0);
    drawRock(s.texture_map[9]);
    glPopMatrix();
    glPopMatrix();

    //Rocka 2
     glPushMatrix();
     glScaled(.25,.25,.25);
     glRotated(year_2,0.0,1.0,0.0);
     glTranslatef(9.5,0.0,0.0);
     glPushMatrix();
     glRotatef(day_2,0,1,0);
     drawRock(s.texture_map[16]);
     glPopMatrix();
     glPopMatrix();

     //Rocka 3
     glPushMatrix();
     glScaled(.5,.5,.5);
     glRotated(year,0.0,1.0,0.0);
     glTranslatef(10,0.0,0.0);
     glPushMatrix();
     glRotatef(day,0,1,0);
     drawRock(s.texture_map[15]);
     glPopMatrix();
     glPopMatrix();

     //Rocka 3.1
     glPushMatrix();
     glScaled(.5,.5,.5);
     glRotated(year,0.0,1.0,0.0);
     glTranslatef(-10,0.0,0.0);
     glPushMatrix();
     glRotatef(day,0,1,0);
     drawRock(s.texture_map[8]);
     glPopMatrix();
     glPopMatrix();

    glPopMatrix();

}
//Modificar posciones
void update(){
    Enemy enemigo = Enemy();
    Disparos shoot = Disparos();
    //Nave
    s.nave.update(10);
    //Enemigos
    for(int i=0;i<30;i++){
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
    for(int i=0; i<30; i++)
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
                double sumaRadios = s.nave.radio + arrEnemies[i].enemy_radio;
                double distanciaX = s.nave.V[0] - arrEnemies[i].V[0];
                double distanciaZ = s.nave.V[2] - arrEnemies[i].V[2];
                if(arrEnemies[i].condicion&&(sumaRadios*sumaRadios)>((distanciaZ*distanciaZ)+(distanciaX*distanciaX)))
                {
                   s.nave.muerto();
                }
            }
        }
    }
    //Sistema Solar
    DWORD TiempoActual = 0;
    DWORD LastUpdate = 0;
    DWORD Lapso =0;
    TiempoActual = GetTickCount();
    Lapso = (TiempoActual - LastUpdate);

    if(Lapso>=30){
            year=((year+1)%360);
            solE=(solE-2)%360;
            day=(day+2)%360;
            year_1=((year_1+4)%360);
            year_2=((year_2+3)%360);
            LastUpdate=TiempoActual;
            satelite = (satelite-4)%360;
            day_2=(day_2-4)%360;
            day_1=(day_1-3)%360;
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
    // drawSistemaEstrellas();
    drawSistemaRocka();
    //drawRock(&anguloSol, s.texture_map,-10,-15,-15,.8,.8,.8);
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
    gluLookAt(s.nave.V[0],5,2,s.nave.V[0],0,-4,0,1,0);
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

