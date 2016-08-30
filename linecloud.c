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
char tc,buf1[64000], buf2[64000];

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


for (x=1; x<(256); x++) {
hue=(x/(256.0));
sat=0.75;
intensity=1.0;

if (x<((256.0)/4.0)) { intensity=(x*4.0)/(256.0); }
 else intensity=1.0;

HSItoRGB(hue,sat,intensity,&red,&green,&blue);
hsidac[x*3]=red;
hsidac[x*3+1]=green;
hsidac[x*3+2]=blue;

}
hsidac[0]=0;
hsidac[1]=0;
hsidac[2]=0;

WritePal(0,256,hsidac);

cls(ptr0,0);
cls(buf1,0);
cls(buf2,0);

/* Set up for main loop... */
maxx=319;
maxy=199;
minx=0;
miny=0;

i=0;
while (i<=numlins+1) {
xx[i]=(int) rand()%maxx; yy[i]=(int) rand()%maxy;
dx[i]=(int) rand()%10-5; dy[i]=(int) rand()%10-5;
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


color=255;

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

 
i=1;
while (i<numlins) {
line(buf1,xx[i],yy[i],xx[i+1],yy[i+1],255);
i++; 
}
line(buf1,xx[numlins],yy[numlins],xx[1],yy[1],255);

q=(q+1) % traces;

i=1;
while (i<=numlins) {
lx[i][q]=xx[i];
ly[i][q]=yy[i];
i++;
}

if (gravity!=0) {
   for (i=1; i<=numlins; i++) {
   ii=i-1;
   iii=i+1;
   if (i==1) ii=numlins;
   if (i==numlins) iii=1;
   a1=dx[i] + ((xx[ii]+xx[iii] - 2*xx[i])/156);
   a2=dy[i] + ((yy[ii]+yy[iii] - 2*yy[i])/156);
   dx[i]=(int) a1;
   dy[i]=(int) a2;
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
if (abs(dx[i])>5) dx[i]=(int) dx[i]/2;
if (abs(dy[i])>5) dy[i]=(int) dy[i]/2;
i++;
}


memset(buf1,0,320);
for (x=321; x<(198*320); x++) {
 tc=(BYTE) ((buf1[x+1] + buf1[x-1] + buf1[x+320] + buf1[x-320] 
  /*     + buf1[x-321] + buf1[x-319] + buf1[x+319] + buf1[x+321] */ 
    )/4);  
/*    )/8);  */

 if (tc>2)  tc-=1; 
 buf2[x]=tc; 

}

memset(buf2,0,320);
memcpy(buf1,buf2,64000);
memcpy(ptr0,buf2,64000);


VioScrUnLock(HANDLE);
} /* end loop */
}

