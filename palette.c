#include "palette.h"
#include "globals.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void Pal256(unsigned long int x,int r,int g,int b)

{ if (r>255) r=255;
    if (g>255) g=255;
    if (b>255) b=255;
    if (r<0) r=0;
    if (g<0) g=0;
    if (b<0) b=0;
    palette[x].R=(1.0/255)*r;
    palette[x].G=(1.0/255)*g;
    palette[x].B=(1.0/255)*b;
}

void DefPalette()

{ int loop,jump;
    for (loop=0;loop<=15;loop++)
    { if(loop<8) jump=18; else jump=17;
        Pal256(    loop,loop*17,loop*17,loop*17);             /* Bright  */
        Pal256( 16+loop,loop*36,loop*36-288,loop*36-288);  /* Hue 0   */
        Pal256( 32+loop,loop*36,loop*jump,loop*36-288);    /* Hue 30  */
        Pal256( 48+loop,loop*36,loop*36,loop*36-288);      /* Hue 60  */
        Pal256( 64+loop,loop*jump,loop*36,loop*36-288);    /* Hue 90  */
        Pal256( 80+loop,loop*36-288,loop*36,loop*36-288);  /* Hue 120 */
        Pal256( 96+loop,loop*36-288,loop*36,loop*jump);    /* Hue 150 */
        Pal256(112+loop,loop*36-288,loop*36,loop*36);     /* Hue 180 */
        Pal256(128+loop,loop*36-288,loop*jump,loop*36);   /* Hue 210 */
        Pal256(144+loop,loop*36-288,loop*36-288,loop*36); /* Hue 240 */
        Pal256(160+loop,loop*jump,loop*36-288,loop*36);   /* Hue 270 */
        Pal256(176+loop,loop*36,loop*36-288,loop*36);     /* Hue 300 */
        Pal256(192+loop,loop*36,loop*36-288,loop*jump);   /* Hue 330 */
    }
}
