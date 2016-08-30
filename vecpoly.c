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
#include "triangle.h"
 
#define maxnumballs 4000 
#define FDiv 4096
#define AInc 182
#define AInc2 51

struct tri {
	int v1,v2,v3;
	int cz;
	char color;
};


struct tri tlist[4000];

int pts[maxnumballs+1][3],dpts[maxnumballs+1][3];
int order[maxnumballs+1];


int compare(const void * index1, const void * index2)
{
     if (tlist[*(int *) index1].cz>tlist[*(int *) index2].cz) return(1);
else if (tlist[*(int *) index1].cz<tlist[*(int *) index2].cz) return(-1); 
          else return(0);
}




void main() {
PCH ptr0;
char array[100000];
FILE * dfile;
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
int zt1,zt2,zt3;
int framecount;
char str[80];
time_t tstart,tfinish;
double dt;
int waterenable,ainc,ainc2,ainc3,timeron;
int numverts,numtris;
int x1,y1,x2,y2,x3,y3;

kr=0; kt=0; kp=0;

printf("opening mesh.dat\n");

dfile=fopen("mesh.dat","r");
printf("Reading mesh.dat... \n");
fscanf(dfile,"%d",&numverts);
printf("Number of vertexes: %d\n",numverts);
fscanf(dfile,"%d",&numtris);
printf("Number of triangles:  %d\n",numtris);
fscanf(dfile,"%d",&waterenable);
if (waterenable) printf("Mirror/Water enabled.. \n");
fscanf(dfile,"%d",&ainc);
fscanf(dfile,"%d",&ainc2);
fscanf(dfile,"%d",&ainc3);
fscanf(dfile,"%d",&timeron);

/* read in vertices */
for (i=0; i<numverts; i++) {
fscanf(dfile,"%f%f%f",&tx,&ty,&tz);
 pts[i][0]=tx*FDiv;
 pts[i][1]=ty*FDiv;
 pts[i][2]=tz*FDiv;
} 

/* read in triangles. . . */
for (i=0; i<numtris; i++) {
 fscanf(dfile,"%d%d%d%d",&tlist[i].v1,&tlist[i].v2,&tlist[i].v3,&tlist[i].color);
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

/* Rotate all vertices for viewing. . . */
for (i=0; i<numverts; i++) {
ROTATE3D(RotA,pts[i][0],pts[i][1],pts[i][2],dpts[i][0],dpts[i][1],dpts[i][2]);
}

/* calculate center depths for triangles. . . */
for (i=0; i<numtris; i++) {
tlist[i].cz=(dpts[tlist[i].v1][2]+dpts[tlist[i].v2][2]+dpts[tlist[i].v3][2])/3;
order[i]=i;
}

/* depthsort the list of triangles . . .*/
qsort(order,numtris,sizeof(int),compare);

for (i=numtris-1; i>=0; i--) {

zt=0;

j=tlist[order[i]].v1;
zt1=dpts[j][2];
if ((zt1)>=-100*FDiv) {
 zt1=(3*FDiv*FDiv)/(zt1+20*FDiv);
  x1=160+((5*dpts[j][0]*zt1)>>20);
  y1=100-((dpts[j][1]*zt1)>>18);
  zt=1;
}

j=tlist[order[i]].v2;
zt2=dpts[j][2];
if ((zt2)>=-100*FDiv) {
 zt2=(3*FDiv*FDiv)/(zt2+20*FDiv);
  x2=160+((5*dpts[j][0]*zt2)>>20);
  y2=100-((dpts[j][1]*zt2)>>18);
} else { zt=0; }

j=tlist[order[i]].v3;
zt3=dpts[j][2];
if ((zt3)>=-100*FDiv) {
 zt3=(3*FDiv*FDiv)/(zt3+20*FDiv);
  x3=160+((5*dpts[j][0]*zt3)>>20);
  y3=100-((dpts[j][1]*zt3)>>18);
} else { zt=0; }

if (zt==1) {
triangle(scrbuf,x1,y1,x2,y2,x3,y3,tlist[order[i]].color);
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
