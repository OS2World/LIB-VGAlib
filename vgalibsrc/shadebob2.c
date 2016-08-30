/* plasma.c -  Plasma 1.0 for OS/2 using vgalib */


/*
 *   Copyright (c) 1992, 1993, John E. Stone - johns@cs.umr.edu
 *   All rights reserved.
 *   
 *   For questions comments:  email to johns@cs.umr.edu
 *
 *   U.S. Mail to:  John E. Stone
 *                  1701 N. Pine Apt 8
 *                  Rolla MO, 65401 
 *
 */
#define INCL_BASE
#include <os2.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "vgalib.h"
#include <process.h>
#include <conio.h>

#define HANDLE 0
#define WAIT 1
#define ADD  1 
#define BOBS 4 
#define EDGE 25 

BYTE red, green, blue;
BYTE savedac[768], newdac[768], nnewdac[768], hsidac[768];
PCH ptr0;
char ch;
unsigned int i,x,y,j,xx,yy;
float hue, sat, intensity;
char status;
int bobs[BOBS][4];
int a,b;

main() {

Initgraph(&ptr0);

srand(getpid());

DosSetPriority(0,1,31,getpid());
srand(getpid());

for (x=0; x<256; x++) {
hue=(x/255.0);
sat=0.75;
intensity=1.0;

HSItoRGB(hue,sat,intensity,&red,&green,&blue);
hsidac[x*3]=red;
hsidac[x*3+1]=green;
hsidac[x*3+2]=blue;

}


memset(ptr0,0,64000);


WritePal(0,256,hsidac);

for (x=0; x<BOBS; x++) {
  bobs[x][0]=rand() % 320;
  bobs[x][1]=rand() % 200;
  bobs[x][2]=(rand() % 9) - 4;
  bobs[x][3]=(rand() % 9) - 4;
  if (bobs[x][2]==0) bobs[x][2]=-2;
  if (bobs[x][3]==0) bobs[x][3]=1;
}

while (!kbhit()) {

for (x=0; x<BOBS; x++) {
  bobs[x][0]+=bobs[x][2];
  bobs[x][1]+=bobs[x][3];
     if (bobs[x][0]<(2*EDGE))   { bobs[x][0]=(2*EDGE);   bobs[x][2]=-bobs[x][2]; }
else if (bobs[x][0]>(2*(319-EDGE))) { bobs[x][0]=2*(319-EDGE); bobs[x][2]=-bobs[x][2]; }
     if (bobs[x][1]<(2*EDGE))   { bobs[x][1]=(2*EDGE);   bobs[x][3]=-bobs[x][3]; }
else if (bobs[x][1]>(2*(199-EDGE))) { bobs[x][1]=2*(199-EDGE); bobs[x][3]=-bobs[x][3]; }


for (a=-EDGE; a<=EDGE; a++) {
  for (b=-EDGE; b<=EDGE; b++) {  
    i=(bobs[x][0]/2 + b) + ((bobs[x][1]/2 + a)*320);
       if ((i>=0) && (i<64000)) ptr0[i]+=ADD; 
  }
}

}

} 
exit(0);

}


