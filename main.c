#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "globals.h"
#include "palette.h"
#include "disk.h"

struct position pos;
GLdouble step;
GLdouble lensangle;

void initialobject()
{ vertices=8;
    vert[1].x= -25.0 ; vert[1].y= -25.0 ; vert[1].z= -25.0;
    vert[2].x= -25.0 ; vert[2].y=  25.0 ; vert[2].z= -25.0;
    vert[3].x=  25.0 ; vert[3].y=  25.0 ; vert[3].z= -25.0;
    vert[4].x=  25.0 ; vert[4].y= -25.0 ; vert[4].z= -25.0;
    vert[5].x= -25.0 ; vert[5].y= -25.0 ; vert[5].z=  25.0;
    vert[6].x= -25.0 ; vert[6].y=  25.0 ; vert[6].z=  25.0;
    vert[7].x=  25.0 ; vert[7].y=  25.0 ; vert[7].z=  25.0;
    vert[8].x=  25.0 ; vert[8].y= -25.0 ; vert[8].z=  25.0;

    facets=6;
    fac[1].v1= 1 ; fac[1].v2= 2; fac[1].v3= 3; fac[1].v4= 4; fac[1].R= 1.0; fac[1].G= 0.0; fac[1].B= 0.0;
    fac[2].v1= 8 ; fac[2].v2= 7; fac[2].v3= 6; fac[2].v4= 5; fac[2].R= 0.5; fac[2].G= 0.0; fac[2].B= 0.0;
    fac[3].v1= 2 ; fac[3].v2= 6; fac[3].v3= 7; fac[3].v4= 3; fac[3].R= 0.0; fac[3].G= 1.0; fac[3].B= 0.0;
    fac[4].v1= 4 ; fac[4].v2= 8; fac[4].v3= 5; fac[4].v4= 1; fac[4].R= 0.0; fac[4].G= 0.5; fac[4].B= 0.0;
    fac[5].v1= 4 ; fac[5].v2= 3; fac[5].v3= 7; fac[5].v4= 8; fac[5].R= 0.0; fac[5].G= 0.0; fac[5].B= 1.0;
    fac[6].v1= 5 ; fac[6].v2= 6; fac[6].v3= 2; fac[6].v4= 1; fac[6].R= 0.0; fac[6].G= 0.0; fac[6].B= 0.5;
}

void calcbox()
{
    unsigned long int loop;

    for(loop=1;loop<=vertices;loop++)
    {
        if (fabs(vert[loop].x)>bbox) bbox=fabs(vert[loop].x);
        if (fabs(vert[loop].y)>bbox) bbox=fabs(vert[loop].y);
        if (fabs(vert[loop].z)>bbox) bbox=fabs(vert[loop].z);
    }
    bbox=bbox*1.1;
    printf("%f\n",bbox);
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    //   glShadeModel(GL_GOURAUD);
}

void drawobject()
{
    unsigned long int loop;

    //	printf("%08d %08d\n", vertices, facets);

    if(facets>0)
        for(loop=1;loop<=facets;loop++)
        {
            glEnable(GL_DEPTH_TEST);
            glBegin(GL_POLYGON);
            glEnable(GL_DEPTH_TEST);

            glColor3f(fac[loop].R, fac[loop].G, fac[loop].B);
            glVertex3d(vert[fac[loop].v1].x, vert[fac[loop].v1].y, vert[fac[loop].v1].z);
            glVertex3d(vert[fac[loop].v2].x, vert[fac[loop].v2].y, vert[fac[loop].v2].z);
            glVertex3d(vert[fac[loop].v3].x, vert[fac[loop].v3].y, vert[fac[loop].v3].z);
            glVertex3d(vert[fac[loop].v4].x, vert[fac[loop].v4].y, vert[fac[loop].v4].z);
            glEnd();
            //			printf("%08d %08f %08f %08f\n", loop, fac[loop].R, fac[loop].G, fac[loop].B);
        }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslated(pos.x,pos.y,pos.z);

    glRotated(pos.theta,0,1.0,0);
    glRotated(pos.phi  ,1.0,0,0);
    glRotated(pos.beta ,0,0,1.0);
    //  glRotated(1.0,pos.phi,pos.theta,pos.beta);
    drawobject();
    glPopMatrix();
    glutSwapBuffers();
}

void spinDisplay(void)
{
    pos.theta+=(step/4) ; if(pos.theta>=360) pos.theta-=360;
    pos.phi  +=(step/2);  if(pos.phi  >=360) pos.phi  -=360;
    pos.beta +=step;      if(pos.beta >=360) pos.beta -=360;
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //   glOrtho(-bbox, bbox, -bbox, bbox, -bbox, bbox);
    gluPerspective(lensangle,((GLdouble)w/(GLdouble)h),100,10000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) pos.z-=1;       break;
    case  GLUT_MIDDLE_BUTTON:
        if (state ==GLUT_DOWN)  pos.z+=1;       break;
    default:
        break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case '1' : pos.theta-=step; if(pos.theta< 0  ) pos.theta+=360;  break;
    case '2' : pos.theta+=step; if(pos.theta>=360) pos.theta-=360;  break;
    case '3' : pos.phi-=step;   if(pos.phi  < 0  ) pos.phi  +=360;  break;
    case '4' : pos.phi+=step;   if(pos.phi  >=360) pos.phi  -=360;  break;
    case '5' : pos.beta-=step;  if(pos.beta < 0  ) pos.beta +=360;  break;
    case '6' : pos.beta+=step;  if(pos.beta >=360) pos.beta -=360;  break;
    case '7' : lensangle+=1; if(lensangle>180) lensangle=180;       break;
    case '8' : lensangle-=1; if(lensangle<0)   lensangle=  0;       break;

    case 'q' : pos.x-=1; break;
    case 'w' : pos.x+=1; break;
    case 'e' : pos.y-=1; break;
    case 'r' : pos.y+=1; break;
    case 't' : pos.z-=1; break;
    case 'y' : pos.z+=1; break;

    case 'a' : glutIdleFunc(spinDisplay);      break;
    case 's' : glutIdleFunc(NULL);             break;
    case 'z' : pos.theta=0; pos.phi=0; pos.beta=0;                  break;
    case 'x' : pos.x=0; pos.y=0; pos.z=0;                           break;
    default:
        break;
    }
    glutPostRedisplay();
    printf("Theta : %lf\nPhi   : %lf\nBeta  : %lf\nLens  : %lf\n",pos.theta, pos.phi, pos.beta, lensangle);
}

/*
 * Request double buffer display mode.
 * Register mouse input callback funcions
 */
int main(int argc, char** argv)
{
    DefPalette();
    initialobject();

    sprintf(caminho,"/home/taupter/Projects/Klaus3D/vectors/");
    sprintf(nome,"bico2");

    printf("%s\n",caminho);

    LoadASC();
    SaveCPP();
    calcbox();
    pos.x=0;
    pos.y=0;
    pos.z=-300;
    pos.theta=0;
    pos.phi=0;
    pos.beta=0;

    step=2;
    lensangle=45;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(PROGRAM_TITLE);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
