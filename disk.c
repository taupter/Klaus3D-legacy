#include "disk.h"

#include "globals.h"
#include "palette.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

void LoadASC(){
    unsigned char InputString[20];
    int cor;
    unsigned long int loop;

    sprintf(nomearq,"%s%s.txt",caminho,nome);
    printf("%s CARAY\n",nomearq);
    arquivo=fopen(nomearq,"r");
    printf("%d\n",errno);
    perror("Merda: ");
    if(arquivo!=0){
        printf("Here\n");
        fgets(InputString,6,arquivo);
        printf("%s\n",InputString);
        if (strcmp(InputString,"Klaus")==0){
            fgets(InputString,10,arquivo); // Por causa da linha em branco
            fgets(InputString,10,arquivo); // tem-se que dar o desconto de 2 lidas
            fgets(InputString,12,arquivo); // CAPTURA DO NOME VERTICES
            fscanf(arquivo,"%s",InputString);
            vertices=atol(InputString);
            if(vertices>0)
                for(loop=1;loop<=vertices;loop++){
                    fscanf(arquivo,"%s",InputString); // É só pra constar - Tira o index (que só tem função visual)
                    fscanf(arquivo,"%s",InputString); // tem-se que dar o desconto de 2 lidas
                    vert[loop].x=atof(InputString);
                    fscanf(arquivo,"%s",InputString); // tem-se que dar o desconto de 2 lidas
                    vert[loop].y=atof(InputString);
                    fscanf(arquivo,"%s",InputString);
                    vert[loop].z=atof(InputString);
                }

            fgets(InputString,12,arquivo); // CAPTURA DO NOME FACETS
            fgets(InputString,12,arquivo); // CAPTURA DO NOME FACETS

            fscanf(arquivo,"%s",InputString);

            facets=atol(InputString);

            if(facets>0)
                for(loop=1;loop<=facets;loop++){
                    fscanf(arquivo,"%s",InputString); // É só pra constar - Tira o index (que só tem função visual)
                    fscanf(arquivo,"%s",InputString); // Captura INDEX 1
                    fac[loop].v1=atol(InputString);
                    fscanf(arquivo,"%s",InputString); // Captura INDEX 2
                    fac[loop].v2=atol(InputString);
                    fscanf(arquivo,"%s",InputString); // Captura INDEX 3
                    fac[loop].v3=atol(InputString);
                    fscanf(arquivo,"%s",InputString); // Captura INDEX 4
                    fac[loop].v4=atol(InputString);
                    fscanf(arquivo,"%s",InputString); // Captura Cor
                    cor=atoi(InputString);
                    if (cor>=0){
                        fac[loop].R=palette[cor].R;
                        fac[loop].G=palette[cor].G;
                        fac[loop].B=palette[cor].B;
                    }
                    else{
                        fac[loop].R=palette[cor+32].R;
                        fac[loop].G=palette[cor+32].G;
                        fac[loop].B=palette[cor+32].B;
                    }
                }
        }

        fclose(arquivo);
    }
}

void SaveCPP(){
    unsigned long int loop;
    sprintf(nomearq,"%s%s.cpp",caminho,nome);
    if((arquivo=fopen(nomearq,"w"))!=NULL){
        if(vertices>0)
            for(loop=1;loop<=vertices;loop++){
                fprintf(arquivo,"addVertex(");
                fprintf(arquivo,"%17.0f,",vert[loop].x);
                fprintf(arquivo,"%17.6f,",vert[loop].y);
                fprintf(arquivo,"%17.6f);\n",vert[loop].z);
            }
        if(facets>0)
            for(loop=1;loop<=facets;loop++){
                fprintf(arquivo,"addFacet4v3c(");
                fprintf(arquivo,"%ld,",(fac[loop].v1)-1);
                fprintf(arquivo,"%ld,",(fac[loop].v2)-1);
                fprintf(arquivo,"%ld,",(fac[loop].v3)-1);
                fprintf(arquivo,"%ld  ",(fac[loop].v4)-1);
                fprintf(arquivo,"%8.4f,",fac[loop].R);
                fprintf(arquivo,"%8.4f,",fac[loop].G);
                fprintf(arquivo,"%8.4f);\n",fac[loop].B);
            }
    }
    fclose(arquivo);
}
