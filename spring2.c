/* spring2.c - test of spring using new 3d libraries... */


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
#include "int3dlib.h"

#define HANDLE 0
#define WAIT 1
#define BUFSIZE 12
#define FDiv 4096 
#define AINC 122
#define AINC2 41



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
	char status,color;
	unsigned rc;
	PCH ptr0;
	int x,y,row,col;
	int dlist[201][201], dlist2[201][201];
	char clist[201][201];
	long pts,pts2,height,rho,d,s1,s2,c1,c2;
	char ptr1[65536];
	BYTE savedac[768], newdac[768], hsidac[768];
	BYTE red, green, blue;
	float hue,sat,intensity;
	USHORT fWait=0;
	HMOU hmou;
	MOUEVENTINFO mouev;
	USHORT moustat;
	int k1,k2;
	int xa,ya,go;
	ROTMATRIX RotA;    
	int kx,ky,kz;
	int kx2,ky2,kz2;
	int kr,kt,kp;



printf("Wave  V3.0   By John E. Stone   \n\n");
printf("Written for OS/2 2.0 320x200 direct graphics.\n");
printf("send email to: johns@cs.umr.edu for info  \n");

MouOpen(NULL, &hmou);
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
kr=0;
kt=0;
kp=0;

InitRot(&RotA,kt,kp,kr);


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
go=1;


while (!kbhit()) {

MouReadEventQue(&mouev, &fWait, hmou);

while (mouev.fs!=0) {

if (mouev.fs==1) {
  kt+=(AINC*(mouev.col>>2));
  kp+=(AINC*(mouev.row>>2));
  }
else {
  if (mouev.fs & 6) {
	if (go==0) { go=1; }
	else { go=0; }
  }
}

MouReadEventQue(&mouev, &fWait, hmou);
} /* end of while */

/*

else {
  if (joy1.x>jhmax) { kr+=AINC; }
  if (joy1.x<jhmin) { kr-=AINC; }
 }
*/

if (go!=0) Springer(dlist,dlist2,201,0,0,pts,k2);
if (rho<50*FDiv) rho=50*FDiv;
if (rho>300*FDiv) rho=300*FDiv;
if (d>20*FDiv) d=20*FDiv;
if (d<5*FDiv) d=5*FDiv;

s1=0;
s2=0;
c1=FDiv;
c2=FDiv;

IntInitRot(&RotA,kt,kp,kr);

for (x=0; x<pts; x++) {
 for (y=0; y<pts; y++) {
kx=((x-pts2)*FDiv);
ky=((y-pts2)*FDiv);
kz=dlist[x][y];

Rotate3d(&RotA,kx,ky,kz,&kx2,&ky2,&kz2);

fitdpnt(ptr1,kx2,ky2,kz2,s1,s2,c1,c2,rho,d,15);
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


