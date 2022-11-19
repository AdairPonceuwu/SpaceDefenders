#ifndef SISTEMASOLAR_H
#define SISTEMASOLAR_H
#include <GL/glut.h>

class SistemaSolar
{
    public:
        SistemaSolar();
        virtual ~SistemaSolar();
        GLfloat year=0, day=0;
        GLfloat year_m=0,day_m=0;
        GLfloat sol=0;
        GLfloat planet1=0;
        GLfloat satelite=0;
        void drawSystem();
        void giros();
    protected:

    private:
};

#endif // SISTEMASOLAR_H
