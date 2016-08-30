/* Lscapes.c - Fractal landscapes demo */

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
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include "vgalib.h"
#include "3dlib.h"


#define HANDLE 0
#define WAIT 1
#define FDiv 4096 
#define FShift 12
#define PMul 11


_Inline void fitdpnt4(PCH ptr0,long x,long y,long z,long s1,long s2,
             long c1,long c2,long rho,long d,char color)
{
long s3,c3,xe,ye,ze;
unsigned int x2,y2;

s3=(-x*c1)>>FShift;
c3=(y*s1)>>FShift;
xe=((y*c1) - (x*s1))>>FShift;
ye=((s3*c2) - (c3*c2) + (z*s2))>>FShift;
ze=(d<<PMul)/(((((s3*s2) - (c3*s2) - (z*c2))>>FShift) + rho));
x2=160+((5*(xe*ze))>>(FShift+PMul-3));
y2=100-((ye*ze)>>(FShift+PMul-5));
if ((x2<320) && (y2<200)) {
   ptr0[x2+(320*y2)]=(char) color;
   }
}


main()
{
	char status, color;
	PCH ptr0;
	int x,y,row,col;
	int dlist[721][361];
	char clist[721][361];
	double theta,phi;
	long pts,pts2,height,rho,d,s1,s2,c1,c2;
	char ptr1[65536];
	BYTE savedac[768], newdac[768], hsidac[768];
	BYTE red, green, blue;
	float hue,sat,intensity;
	USHORT fWait=0;
	HMOU hmou;
	MOUEVENTINFO mouev;
	USHORT moustat;
	FILE * file1;
	int t1,t2,t3;
	float f1;

printf("Wave  V2.0   By John E. Stone   \n\n");
printf("Written for OS/2 2.0 320x200 direct graphics.\n");
printf("send email to: johns@cs.umr.edu for info  \n");


MouOpen(NULL,&hmou);
moustat=MOUSE_DISABLED | MOUSE_MICKEYS;
MouSetDevStatus(&moustat, hmou);


srand(getpid());

rho=100*FDiv;
d=10*FDiv;

printf("\n\nEnter number of points per side (16-100):  \n");
scanf("%d",&pts);
pts2=pts>>1;

printf("\n\n\nPrecalculating 160,000 altitude points /w colors. . . . .\n");
printf("(this is why it needs ~1Mb of free ram to run.)\n");


file1=fopen("e:\\exports\\earthdata\\earth_topo_720x360.dat","r");

for (x=0; x<720; x++) {
  for (y=0; y<360; y++) {
      fscanf(file1,"%d%d%f",&t1,&t2,&f1);
      dlist[x][y]=f1/300.0*FDiv-10*FDiv;
      clist[x][y]=(char) (dlist[x][y]>>10); 
  }
}
fclose(file1);


Initgraph(&ptr0);

color=15; 
phi=1.0;
theta=0.1;

ReadPal(0,256,savedac);
ReadPal(0,256,newdac);

for (x=1; x<256; x++) {                          
hue=(x/255.0);                                   
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
WritePal(0,255,hsidac);

col=0;
row=0;

for (;1;) {

MouReadEventQue(&mouev, &fWait, hmou);

while(mouev.fs!=0) {

if (mouev.fs==1) {
  theta+=((SHORT) mouev.col)/60.0;
    phi-=((SHORT) mouev.row)/60.0;
  }
else {
  if (mouev.fs & 2) {
	row+=(mouev.col >> 1);
	col+=(mouev.row >> 1);
	}
}

MouReadEventQue(&mouev, &fWait, hmou);

} /* end while */


if ((720-col)<pts) { col=720-pts; }
if ((360-row)<pts) { row=360-pts; }
if (row<0) { row=0; }
if (col<0) { col=0; } 
if (rho<50*FDiv) rho=50*FDiv;
if (rho>300*FDiv) rho=300*FDiv;
if (d>20*FDiv) d=20*FDiv;
if (d<5*FDiv) d=5*FDiv;

s1=(long) (FDiv*sin(theta));
s2=(long) (FDiv*sin(phi));
c1=(long) (FDiv*cos(theta));
c2=(long) (FDiv*cos(phi));


for (x=0; x<pts; x++) {
 for (y=0; y<pts; y++) {
fitdpnt4(ptr1,((x-pts2)*FDiv),((y-pts2)*FDiv),dlist[x+row][y+col],s1,s2,c1,c2,rho,d,clist[x+row][y+col]);
 }
} 

VioScrLock(WAIT,&status,HANDLE); 
memcpy(ptr0,ptr1,64000);
memset(ptr1,0,64000);
VioScrUnLock(HANDLE); 
}

VioScrLock(WAIT,&status,HANDLE);
cls(ptr0,0);
VioScrUnLock(HANDLE);
}


