/* vecballs.c - Demo of 3D projection with the fixed point integer
 *		3D library int3dlib.  Uses the painter's algorithm
 *		to draw the shaded spheres from back to front, and
 *		provides a nice illusion of solid spheres at a 
 * 		relatively high rate of speed. 
 * John E. Stone - 7/01/93 
 *
 */


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
#include "vgalib.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "int3dlib.h"
#include <time.h>
#include "inline.h"
 
#define maxnumballs 900 
#define FDiv 4096
#define AInc 182
#define AInc2 51



int pts[maxnumballs+1][3],dpts[maxnumballs+1][3];
int order[maxnumballs+1];


int compare(const void * index1, const void * index2)
{
     if (dpts[*(int *) index1][2]>dpts[*(int *) index2][2]) return(1);
else if (dpts[*(int *) index1][2]<dpts[*(int *) index2][2]) return(-1); 
          else return(0);
}


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
FILE * dfile;
int numballs;
int spheresize;
float tx,ty,tz;
BYTE dac[768];
int x,y,z,i,j;
BYTE red,green,blue;
float hue,sat,intensity;
BYTE scrbak[64000],scrbuf[64000];
int kx,ky,kz;
int kx2,ky2,kz2;
int kr,kt,kp;
ROTMATRIX RotA;
int xt,yt,zt;
int framecount;
char str[80];
time_t tstart,tfinish;
double dt;
int waterenable,ainc,ainc2,ainc3,timeron;

kr=0; kt=0; kp=0;

printf("opening model.dat\n");

dfile=fopen("model.dat","r");
printf("Reading model.dat... \n");
fscanf(dfile,"%d",&numballs);
printf("Number of vector balls: %d\n",numballs);
fscanf(dfile,"%d",&spheresize);
printf("Spheres of size: %d\n",spheresize);
fscanf(dfile,"%d",&waterenable);
if (waterenable) printf("Mirror/Water enabled.. \n");
fscanf(dfile,"%d",&ainc);
fscanf(dfile,"%d",&ainc2);
fscanf(dfile,"%d",&ainc3);
fscanf(dfile,"%d",&timeron);


for (i=0; i<numballs; i++) {
fscanf(dfile,"%f%f%f",&tx,&ty,&tz);

 pts[i][0]=tx*FDiv;
 pts[i][1]=ty*FDiv;
 pts[i][2]=tz*FDiv;
} 

fclose(dfile);

initgraph(&ptr0);

for (x=1; x<=64; x++) {
dac[x*3]=x-1;
dac[x*3+1]=x-1;
dac[x*3+2]=x-1;
}
for (x=65; x<=128; x++) {
dac[x*3]=0;
dac[x*3+1]=0;
dac[x*3+2]=x-65;
}

dac[0]=0;
dac[1]=0;
dac[2]=0;

WAITVSYNC
WritePal(0,129,dac);

cls(ptr0,0);
for (x=0; x<200; x++) {
line(scrbak,0,x,319,x,((63.0*(x+1))/200.0)+65);
}

makesphere(array,spheresize);

framecount=0;
time(&tstart);

/* main loop */
while (!kbhit()) {

framecount++;

memcpy(scrbuf,scrbak,64000);

kr+=ainc;
kp+=ainc2;
kt+=ainc3;

IntInitRot(&RotA,kt,kp,kr);

for (i=0; i<numballs; i++) {
ROTATE3D(RotA,pts[i][0],pts[i][1],pts[i][2],dpts[i][0],dpts[i][1],dpts[i][2]);
order[i]=i;
}

qsort(order,numballs,sizeof(int),compare);

for (i=numballs-1; i>=0; i--) {
j=order[i];
zt=dpts[j][2];

if ((zt)>=-100*FDiv) {
 zt=(3*FDiv*FDiv)/(zt+20*FDiv);
  x=160+((5*dpts[j][0]*zt)>>20);
  y=100-((dpts[j][1]*zt)>>18);

MASKBLT2(array, spheresize, spheresize, scrbuf,320,200, x, y);
}
}

if (waterenable) 
for (i=160; i<180; i++) {
memcpy(scrbuf+((359-i)*320),scrbuf+(i*320),320);
}

if (timeron) {
  time(&tfinish);
  dt=framecount/(0.001+difftime(tfinish,tstart));
  sprintf(str,"FPS:%3.1f",dt);
  putstring(scrbuf,2,2,str,255);
}

memcpy(ptr0,scrbuf,64000);
}
}
