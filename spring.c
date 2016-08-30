/* spring.c - 3d spring demo.... */


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


Springer(mat1, mat2, xres, x1, y1, pts, k) 
int *mat1;
int *mat2;
int xres, x1, y1, pts, k;
{

int x,y,a,b,c,d;

for (x=x1+1; x<(x1+pts-1); x++) {
  for (y=((y1+1)*xres); y<((y1+pts-1)*xres); y+=xres) {
	mat2[x+y]+= 
	       (mat1[x + 1 + y] + mat1[x - 1 + y]   + 
		mat1[x + y - xres] + mat1[x + y + xres]  
		- (mat1[x+y]<<2))/k;   
  }
}

for (x=x1+1; x<(x1+pts-1); x++) {
  for (y=((y1+1)*xres); y<((y1+pts-1)*xres); y+=xres) {
	mat1[x+y]+=mat2[x+y]; 
  }
}

}




main()
{
	char status, color;
	PCH ptr0;
	int x,y,row,col;
	int dlist[201][201], dlist2[201][201];
	char clist[201][201];
	double theta,phi;
	float lx,ly;
	long pts,pts2,height,rho,d,s1,s2,c1,c2;
	char ptr1[65536];
	BYTE savedac[768], newdac[768], hsidac[768];
	BYTE red, green, blue;
	float hue,sat,intensity;
	int k1,k2;
	int xa,ya,go;
	USHORT fWait = 0;
	HMOU hmou;
	MOUEVENTINFO mouev;
	USHORT moustat;
	
printf("Wave  V3.0   By John E. Stone   \n\n");
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

printf("\nEnter Spring type:  \n");
printf("1 - Random height\n2 - Sine Wave\n3 - Period 2 Sines...\n");
printf("4 - Water Droplet\n5 - Mod Function\n");
scanf("%d",&k1);

printf("\nEnter spring coefficient k: \n");
scanf("%d",&k2);

printf("\n\n\nPrecalculating altitude points . . . . .\n");


for (x=0; x<201; x++) {
for (y=0; y<201; y++) {
dlist[x][y]=0;
dlist2[x][y]=0;
}
}

if (k1==1) {
dlist[0][0]=0;
dlist[pts][0]=0;
dlist[pts][pts]=0;
dlist[0][pts]=0;

subdivide((int *) dlist,201,0,0,pts,pts);
}
else if (k1==2) {
for (x=0; x<pts; x++) {
for (y=0; y<pts; y++) {
dlist[x][y]=(int) (FDiv*10*sin(sqrt(((x-pts2)*(x-pts2)/(pts-1.0))
			+((y-pts2)*(y-pts2)/(pts-1.0)))));
}
}
}
else if (k1==3) {
for (x=0; x<pts; x++) {
  for (y=0; y<pts; y++) {
dlist[x][y]=(int) (FDiv*10*sin((6.283*x/(pts-1)))*sin((6.283*y/(pts-1))));
}
}
}
else if (k1==4) {
for (x=0; x<pts; x++) {
  for (y=0; y<pts; y++) {
dlist[x][y]=0;
}
}
dlist[pts2][pts2]=35*FDiv;
dlist[pts2+1][pts2]=35*FDiv;
dlist[pts2][pts2+1]=35*FDiv;
dlist[pts2+1][pts2+1]=35*FDiv;
}
else {
xa=pts>>2;
for (x=0; x<pts; x++) {
  for (y=0; y<pts; y++) {
	dlist[x][y]=FDiv*20.0*((x % xa)+(y % xa))/pts;
}
}

}


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
WritePal(0,256,hsidac);

col=0;
row=0;
go=0;

while (!kbhit()) {

MouReadEventQue(&mouev, &fWait, hmou);

while (mouev.fs!=0) {

if (mouev.fs==1) {
  theta+=((SHORT) mouev.col)/60.0;
    phi-=((SHORT) mouev.row)/60.0;
  }
else {
  if (mouev.fs & 6) { 
     if (go==0) { go=1; }
     else { go=0; }
  }
}

MouReadEventQue(&mouev, &fWait, hmou);

} /* end while */

if (go!=0) Springer(dlist,dlist2,201,0,0,pts,k2);
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
fitdpnt(ptr1,((x-pts2)*FDiv),((y-pts2)*FDiv),dlist[x][y],s1,s2,c1,c2,rho,d,15);
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


