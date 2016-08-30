/*
*   Liny.c - A neat little graphics demo
*
*      All versions (DOS - OS2 - UNIX) 
*      By,  John E. Stone
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
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include "vgalib.h"
#define HANDLE 0
#define WAIT 1

char status;
BYTE red,green,blue;

char color;
int lx[40][256],ly[40][255];
int dx[40],dy[40];
int xx[40],yy[40];
int z,numlins,traces;
int maxx,maxy,minx,miny;
int i,ii,iii,gravity,randon,q;
int looper;
float PI,a1,a2;
PCH ptr0;
BYTE nnewdac[768],savedac[768],newdac[768],hsidac[768];
float hue,sat,intensity;
int x,y,q,r;


main(argc,argv)
int argc; char *argv[];

{

PI=3.1415926;

numlins=atoi(argv[1]);
traces=atoi(argv[2]);
gravity=atoi(argv[3]);
randon=atoi(argv[4]);

if (traces>255) traces=255;
if (numlins>40) numlins=39;
i=0;


Initgraph(&ptr0);

ReadPal(0, 256, savedac);
ReadPal(0, 256, hsidac);


for (x=1; x<(traces+1); x++) {
hue=(x/(traces*1.0));
sat=0.75;
intensity=1.0;

HSItoRGB(hue,sat,intensity,&red,&green,&blue);
hsidac[x*3]=red;
hsidac[x*3+1]=green;
hsidac[x*3+2]=blue;

}
hsidac[0]=0;
hsidac[1]=0;
hsidac[2]=0;

WAITVSYNC
WritePal(0,256,hsidac);

cls(ptr0,0);


/* Set up for main loop... */
maxx=319;
maxy=199;
minx=0;
miny=0;

i=0;
while (i<=numlins+1) {
xx[i]=(int) rand()%maxx; yy[i]=(int) rand()%maxy;
dx[i]=(int) rand()%20-10; dy[i]=(int) rand()%20-10;
i++;
}

i=0;
while (i<=numlins) {
  z=0;
  while (z<=traces) {
  lx[i][z]=xx[i];
  ly[i][z]=yy[i];
  z++;
 }
 dx[i]=(int) rand()%10 - 2;
 dy[i]=(int) rand()%10 - 2;
i++;
} 
q=1;


/* Main Loop of program.. */
while (!kbhit()) {
VioScrLock(WAIT,&status,HANDLE);
i=1; 
while (i<=numlins) {
xx[i]=xx[i]+dx[i];
yy[i]=yy[i]+dy[i];
if (xx[i]>maxx) dx[i]= -(abs(dx[i]));
if (xx[i]<minx) dx[i]=   abs(dx[i]);
if (yy[i]>maxy) dy[i]= -(abs(dy[i]));
if (yy[i]<miny) dy[i]=   abs(dy[i]);
i++;
}

color=(char) (q % traces)+1;


 WAITVSYNC  

 
i=1;
while (i<numlins) {
line(ptr0,xx[i],yy[i],xx[i+1],yy[i+1],color);
i++; 
}
line(ptr0,xx[numlins],yy[numlins],xx[1],yy[1],color);

q=(q+1) % traces;

color=0;

i=1;
while (i<numlins) {
line(ptr0,lx[i][q],ly[i][q],lx[i+1][q],ly[i+1][q],color);
i++;
}
line(ptr0,lx[numlins][q],ly[numlins][q],lx[1][q],ly[1][q],color);

i=1;
while (i<=numlins) {
lx[i][q]=xx[i];
ly[i][q]=yy[i];
i++;
}

if (gravity!=0) {
   i=1;
   while (i<=numlins) {
   ii=i-1;
   iii=i+1;
   if (i==1) ii=numlins;
   if (i==numlins) iii=1;
   a1=dx[i] + ((xx[ii]+xx[iii] - 2*xx[i])/100);
   a2=dy[i] + ((yy[ii]+yy[iii] - 2*yy[i])/100);
   dx[i]=(int) a1;
   dy[i]=(int) a2;
   i++;
   }
}

if (randon!=0) {
   if ((rand()%100)>97) {
       i=rand()%numlins + 1;
       dx[i]=dx[i] + rand()%3 - 1;
       dy[i]=dy[i] + rand()%3 - 1;
       }
   }

i=1;
while (i<=numlins) { 
if (abs(dx[i])>13) dx[i]=(int) dx[i]/2;
if (abs(dy[i])>10) dy[i]=(int) dy[i]/2;
i++;
}

VioScrUnLock(HANDLE);
} /* end loop */
}

