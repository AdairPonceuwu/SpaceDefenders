#ifndef SD_UTILS
#define SD_UTILS

#include <GL/glut.h>
#include <cmath>

#include "rgbimage.h"

/*
 * Read a texture map from a BMP bitmap file.
 */

//Recordar que (pi/180 = r/g) donde "r" son radianes y "g" grados
//Se aplica la formula r
inline float RadToDeg(float r) {
      return ((180.0*r)/M_PI);
}

inline float DegToRad(float g) {
      return ((g*M_PI)/180.0);
}

inline void drawAxis() {
    // Variables para dibujar los ejes del sistema
    const float X_MIN = -50,
                X_MAX = 50,
                Y_MIN = -50,
                Y_MAX = 50,
                Z_MIN = -50,
                Z_MAX = 50;

    //X axis in red
    glBegin(GL_LINES);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(X_MIN,0.0,0.0);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(X_MAX,0.0,0.0);
    glEnd();

    //Y axis in green
    glBegin(GL_LINES);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(0.0,Y_MIN,0.0);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(0.0,Y_MAX,0.0);
    glEnd();

    //Z axis in blue
    glBegin(GL_LINES);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0.0,0.0,Z_MIN);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0.0,0.0,Z_MAX);
    glEnd();
}

/// desechables!
inline void drawFace(float x1, float y1, float z1,
              float x2, float y2, float z2,
              float x3, float y3, float z3,
              float x4, float y4, float z4) {
   glBegin(GL_QUADS);
       glTexCoord2f(0.0, 0.0);
       glVertex3f(x1, y1, z1);

       glTexCoord2f(0.0, 1.0);
       glVertex3f(x2, y2, z2);

       glTexCoord2f(1.0, 1.0);
       glVertex3f(x3, y3, z3);

       glTexCoord2f(1.0, 0.0);
       glVertex3f(x4, y4, z4);
   glEnd();
}

//Draw a cube with the specific texture
inline void drawCube(GLuint *texture) {
   //Activate textures
   glEnable(GL_TEXTURE_2D);
   //front face
   glBindTexture(GL_TEXTURE_2D, texture[0]);
   drawFace(-1.0, 1.0, 1.0,
            -1.0, -1.0, 1.0,
            1.0, -1.0, 1.0,
            1.0, 1.0, 1.0);
   //right face
   glBindTexture(GL_TEXTURE_2D, texture[1]);
   drawFace(1.0, 1.0, 1.0,
            1.0, -1.0, 1.0,
            1.0, -1.0, -1.0,
            1.0, 1.0, -1.0);
   //back face
   glBindTexture(GL_TEXTURE_2D, texture[2]);
   drawFace(1.0, 1.0, -1.0,
            -1.0, 1.0, -1.0,
            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0);
   //left face
   glBindTexture(GL_TEXTURE_2D, texture[3]);
   drawFace(-1.0, 1.0, -1.0,
            -1.0, -1.0, -1.0,
            -1.0, -1.0, 1.0,
            -1.0, 1.0, 1.0);
   glDisable(GL_TEXTURE_2D);
}

inline void drawCubes(GLuint *texture) {
    glPushMatrix();
    glTranslated(10,0,0);
    glColor3f(1.0,1.0,1.0);
    drawCube(texture);
    //glTranslated(0,0,0);
    glTranslated(-20,0,0);
    glRotated(45.0, 0.0, 1.0, 0.0);
    drawCube(texture);
    glPopMatrix();

    //dibujado de cubos sin textura
    glPushMatrix();
    glTranslated(0,10,0);
    glColor3f(0.0,1.0,0.0);
    glutSolidCube(3);
    glTranslated(0,-20,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,10);
    glColor3f(0.0,0.0,1.0);
    glutSolidCube(1);
    glTranslated(0,0,-20);
    glutSolidCube(1);
    glPopMatrix();
}

inline void drawSphere2(GLfloat *angulo, GLuint texture,float x, float y, float z,float xS, float yS, float zS) {

    //activando texturas
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(xS,yS,zS);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glRotatef(*angulo, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, texture);
    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture( qobj, GL_TRUE );
    gluSphere( qobj, 1.0f, 20, 20 );
    gluDeleteQuadric( qobj );
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    *angulo = (*angulo + 0.1 > 360) ? 0.0 : *angulo + 0.1;

}

inline void drawSphere(GLdouble radius,GLint slices, GLint stacks,GLuint texture) {

    //activando texturas
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, texture);
    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture( qobj, GL_TRUE );
    gluSphere( qobj, radius, slices, stacks );
    gluDeleteQuadric( qobj );
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
inline void drawCone(GLuint texture){
 unsigned int indices_enemigo[] = {
		// front
		0, 1, 2,
		// Front
		3, 4, 5,
		// back
		6, 7, 8,
		// back
		9, 10, 11,
		// front
		12, 13, 14,
		// Front
		15, 16, 17,
		// back
		18, 19, 20,
		// back
		21, 22, 23,
	};
GLfloat vertices_enemigo[] = {
	//x		y		z
	0.0f, 0.5f,  0.5f,
	0.0f, 0.0f,  0.5f,
	0.5f, 0.0f, 0.0f,
	//x		y		z
	0.0f, 0.5f,  0.5f,
	0.0f, 0.0f,  0.5f,
	-0.5f, 0.0f, 0.0f,
	//x		y		z
	0.0f, -0.5f,  -0.5f,
	0.0f, 0.0f,  -0.5f,
	0.5f, 0.0f,  0.0f,
	//x		y		z
	0.0f, -0.5f,  0.0f,
	0.0f, 0.0f,  0.5f,
	-0.5f, 0.0f,  0.0f,
	//x		y		z
	0.0f, 0.5f,  -0.5f,
	0.0f, 0.0f,  -0.5f,
	0.5f, 0.0f,  0.0f,
	//x		y		z
	0.0f, 0.5f,  0.0f,
	0.0f, 0.0f,  0.5f,
	-0.5f, 0.0f,  0.0f,
	//x      y      z
	0.0f, -0.5f,  0.5f,
	0.0f, 0.0f,  0.5f,
	0.5f, 0.0f, 0.0f,
	//x		y		z
	0.0f, -0.5f,  0.5f,
	0.0f, 0.0f,  0.5f,
	-0.5f, 0.0f, 0.0f,
};
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glRotated(270, 0.0f,0.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < (sizeof(indices_enemigo) / sizeof(int)); i += 3) {
            int v1 = indices_enemigo[i]*3,
                v2 = indices_enemigo[i + 1] * 3,
                v3 = indices_enemigo[i + 2] * 3;
            glTexCoord2f(0.0,0.0);
            glVertex3f(
                vertices_enemigo[v1],
                vertices_enemigo[v1 + 1],
                vertices_enemigo[v1 + 2]
            );
            glTexCoord2f(0.0, 1.0);
            glVertex3f(
                vertices_enemigo[v2],
                vertices_enemigo[v2 + 1],
                vertices_enemigo[v2 + 2]
            );
            glTexCoord2f(1.0, 1.0);
            glVertex3f(
                vertices_enemigo[v3],
                vertices_enemigo[v3 + 1],
                vertices_enemigo[v3 + 2]
            );
        }
    glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}
inline void drawRock(GLfloat *angulo, GLuint *texture, float x, float y, float z,float xS, float yS, float zS) {
    float vertices[] = {
        0.610554, 0.390263, -0.577546,
        1.000000, -0.452002, -0.489054,
        1.000000, 0.391220, 0.255188,
        1.000000, -0.366603, 0.290283,
        -2.512954, 0.636146, 0.198266,
        -2.808197, -0.710687, -0.417162,
        -2.808197, 0.385705, 1.000000,
        -2.808197, -0.688166, 0.421588,
        -0.904099, -1.000000, -1.000000,
        -0.904099, 1.151799, 0.452907,
        -0.904099, -1.000000, 1.000000,
        -0.663425, 1.000000, -0.498829,
        -1.856148, -1.000000, -1.000000,
        -1.856148, 1.170638, 1.000000,
        -1.856148, -1.000000, 1.000000,
        -1.856148, 1.000000, -0.511415,
        0.047951, -1.000000, 1.000000,
        -0.192723, 1.000000, -0.498829,
        0.047951, -0.767962, -0.750716,
        0.043057, 0.877238, 0.388713,
        0.847340, 0.000000, -0.852088,
        -2.808197, 0.000000, 1.000000,
        1.000000, 0.000000, 1.000000,
        -2.388790, 0.000000, -0.462172,
        -0.904099, 0.000000, -1.341803,
        -0.904099, 0.000000, 1.623521,
        -1.856148, 0.000000, -1.000000,
        -1.856148, 0.000000, 1.623521,
        0.047951, 0.000000, 1.623521,
        0.047951, 0.000000, -1.341803,
    };
    int caras[] = {
        4, 13, 15,
        27, 6, 21,
        21, 4, 23,
        18, 3, 16,
        20, 2, 22,
        29, 0, 20,
        15, 24, 26,
        8, 14, 12,
        19, 25, 28,
        11, 19, 17,
        5, 14, 7,
        23, 15, 26,
        25, 13, 27,
        15, 9, 11,
        0, 19, 2,
        22, 19, 28,
        11, 29, 24,
        18, 10, 8,
        24, 18, 8,
        22, 16, 3,
        25, 14, 10,
        23, 12, 5,
        28, 10, 16,
        26, 8, 12,
        18, 20, 1,
        20, 3, 1,
        7, 23, 5,
        14, 21, 7,
        4, 6, 13,
        27, 13, 6,
        21, 6, 4,
        18, 1, 3,
        20, 0, 2,
        29, 17, 0,
        15, 11, 24,
        8, 10, 14,
        19, 9, 25,
        11, 9, 19,
        5, 12, 14,
        23, 4, 15,
        25, 9, 13,
        15, 13, 9,
        0, 17, 19,
        22, 2, 19,
        11, 17, 29,
        18, 16, 10,
        24, 29, 18,
        22, 28, 16,
        25, 27, 14,
        23, 26, 12,
        28, 25, 10,
        26, 24, 8,
        18, 29, 20,
        20, 22, 3,
        7, 21, 23,
        14, 27, 21,
    };


    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(xS,yS,zS);
    glRotatef(*angulo, 0.0f, 0.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glBegin(GL_TRIANGLES);
        for (int i = 0; i < (sizeof(caras) / sizeof(int)); i += 3) {
            int v1 = caras[i] * 3,
                v2 = caras[i + 1] * 3,
                v3 = caras[i + 2] * 3;
            glTexCoord2f(0.0,0.0);
            glVertex3f(
                vertices[v1],
                vertices[v1 + 1],
                vertices[v1 + 2]
            );
            glTexCoord2f(0.0, 1.0);
            glVertex3f(
                vertices[v2],
                vertices[v2 + 1],
                vertices[v2 + 2]
            );
            glTexCoord2f(1.0, 1.0);
            glVertex3f(
                vertices[v3],
                vertices[v3 + 1],
                vertices[v3 + 2]
            );
        }
    glEnd();
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    *angulo = (*angulo + 0.1 > 360) ? 0.0 : *angulo + 0.4;
}

inline void drawStar(GLfloat *angulo,GLuint texture){
    unsigned int octaedro_indices[] = {
		//top
		// front
		0, 1, 2,
		// Fron
		3, 4, 5,
		// back
		6, 7, 8,
		// back
		9, 10, 11,

		// bottom
		// front
		12, 13, 14,
		// Fron
		15, 16, 17,
		// back
		18, 19, 20,
		// back
		21, 22, 23,

	};
GLfloat octaedro_vertices[] = {
	// front
	//x		y		z
	0.0f, 0.5f,  0.0f,
	0.0f, 0.0f,  0.5f,
	0.5f,  0.0f,  0.0f,
	// front
	//x		y		z
	0.0f, 0.5f,  0.0f,
	0.0f, 0.0f,  0.5f,
	-0.5f, 0.0f,  0.0f,
	// back
	//x		y		z
	0.0f, 0.5f,  0.0f,
	0.5f,  0.0f,  0.0f,
	0.0f, 0.0f,  -0.5f,
	// back
	//x		y		z
	0.0f, 0.5f,  0.0f,
	-0.5f, 0.0f,  0.0f,
	0.0f, 0.0f,  -0.5f,
	// bottom
	//front
	//x		y		z
	0.0f, -0.5f,  0.0f,
	0.0f, 0.0f,  0.5f,
	0.5f,  0.0f,  0.0f,
	// front
	//x		y		z
	0.0f, -0.5f,  0.0f,
	0.0f, 0.0f,  0.5f,
	-0.5f, 0.0f,  0.0f,
	// back
	//x		y		z
	0.0f, -0.5f,  0.0f,
	0.5f,  0.0f,  0.0f,
	0.0f, 0.0f,  -0.5f,
	// back
	//x		y		z
	0.0f, -0.5f,  0.0f,
	-0.5f, 0.0f,  0.0f,
	0.0f, 0.0f,  -0.5f,
};
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glRotatef(*angulo, 0.0f, 0.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < (sizeof(octaedro_indices) / sizeof(int)); i += 3) {
            int v1 = octaedro_indices[i] * 3,
                v2 = octaedro_indices[i + 1] * 3,
                v3 = octaedro_indices[i + 2] * 3;
            glTexCoord2f(0.0,0.0);
            glVertex3f(
                octaedro_vertices[v1],
                octaedro_vertices[v1 + 1],
                octaedro_vertices[v1 + 2]
            );
            glTexCoord2f(0.0, 1.0);
            glVertex3f(
                octaedro_vertices[v2],
                octaedro_vertices[v2 + 1],
                octaedro_vertices[v2 + 2]
            );
            glTexCoord2f(1.0, 1.0);
            glVertex3f(
                octaedro_vertices[v3],
                octaedro_vertices[v3 + 1],
                octaedro_vertices[v3 + 2]
            );
        }
    glEnd();
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    *angulo = (*angulo + 0.1 > 360) ? 0.0 : *angulo + 0.4;
}

#endif // SD_UTILS
