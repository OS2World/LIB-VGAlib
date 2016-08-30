/* spheres.c - draw bouncing spheres */

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
#include <os2.h>
#include "vgalib.h"
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#define spheresize 30 
#define numballs 100 

void makesphere(PCH ptr0, int d)
{
int x,y,i,j,r;
float rx,ry,rz;
float c,q;

r=d/2;

for (x=-r; x<=r; x++) {
  rx=(x*1.0)/(1.0*r);
  for (y=-r; y<=r; y++) {
    ry=(y*1.0)/(1.0*r);

    rz=sqrt(1.0-rx*rx-ry*ry);


    c=(2.0*rz)/sqrt(1.0 + 1.0 + 4.0);
    if (c>0.04) c=(rx-ry+2.0*rz)/sqrt(1.0 + 1.0 + 4.0);
    if (c<0.01) c=0.01; 
    if (c>1.0) c=1.0;	
    ptr0[(x+r) + (d*(y+r))]=(char) 64*(1.0*c);

  }
}
}


void main() {
PCH ptr0;
char array[100000];
BYTE dac[768];
int x,y,z,i,j;
BYTE red,green,blue;
float hue,sat,intensity;
int pts[numballs][4];
BYTE scrbuf[64000];

initgraph(&ptr0);

for (x=1; x<=65; x++) {
hue=0.5;
sat=0.09;
intensity=x/64.0;
HSItoRGB(hue,sat,intensity,&red,&green,&blue);
dac[x*3]=x-1;
dac[x*3+1]=x-1;
dac[x*3+2]=x-1;

}
dac[0]=0;
dac[1]=0;
dac[2]=0;

WAITVSYNC
WritePal(0,65,dac);

cls(ptr0,0);

makesphere(array,spheresize);

for (x=0; x<numballs; x++) {
 pts[x][0]=rand() % 320;
 pts[x][1]=rand() % 200;
 pts[x][2]=(rand() % 10)-5;
 pts[x][3]=(rand() % 8)-4;
 if (pts[x][2]==0) pts[x][2]=1;
 if (pts[x][3]==0) pts[x][3]=1;
}


while (!kbhit()) {
cls(scrbuf,0);
for (x=0; x<numballs; x++) {
  pts[x][0]+=pts[x][2];
  pts[x][1]+=pts[x][3];
  if (pts[x][0]<0) { pts[x][0]=0; pts[x][2]=-pts[x][2]; }
  if (pts[x][0]>(319-spheresize)) { pts[x][0]=(319-spheresize); pts[x][2]=-pts[x][2]; }
  if (pts[x][1]<0) { pts[x][1]=0; pts[x][3]=-pts[x][3]; }
  if (pts[x][1]>(199-spheresize)) { pts[x][1]=(199-spheresize); pts[x][3]=-pts[x][3]; }
  
maskblt(array,array,spheresize,spheresize,scrbuf,320,200,pts[x][0],pts[x][1]);
}
WAITVSYNC
memcpy(ptr0,scrbuf,64000);
}


}
