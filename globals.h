#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#define PROGRAM_TITLE "Klaus3D"

#define MAXVERTICES 10000
#define MAXFACETS   10000

GLdouble spin;

struct vertex
{
    GLdouble x;
    GLdouble y;
    GLdouble z;
};

struct position
{
    GLdouble theta;
    GLdouble phi;
    GLdouble beta;
    GLdouble x;
    GLdouble y;
    GLdouble z;
};

struct facet
{
    unsigned long int v1;
    unsigned long int v2;
    unsigned long int v3;
    unsigned long int v4;
    GLfloat R;
    GLfloat G;
    GLfloat B;
};
struct colorRGB
{
    GLfloat R;
    GLfloat G;
    GLfloat B;
};


//typedef GLdoublefacet

struct vertex vert[MAXVERTICES];
struct facet  fac[MAXFACETS];
struct colorRGB palette[256];

unsigned long int vertices;
unsigned long int facets;

GLdouble bbox;

FILE *arquivo;
char nomearq[255];
char caminho[255];
char nome[9];

#endif // GLOBALS_H
