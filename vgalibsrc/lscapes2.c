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


struct tri {
	int v1,v2,v3;
	int cx,cy,cz;
	};



void Landscaper(base1,base2,xres,x1,y1,x2,y2) 
int * base1;
int * base2; 
int xres,x1,y1,x2,y2;

{
int x,y;

for (x=x1; x<=x2; x++) {
   for (y=y1; y<=y2; y++) {
	base1[x + xres*y]=0;
	base2[x + xres*y]=0;
   }
}
        
base1[x1 + xres*y1]=1+(rand()%(192*FDiv));            
base1[x2 + xres*y1]=1+(rand()%(192*FDiv));
base1[x2 + xres*y2]=1+(rand()%(192*FDiv));        
base1[x1 + xres*y2]=1+(rand()%(192*FDiv));          
                                              
subdivide(base1,xres,x1,y1,x2,y2);     
                                              
for (x=x1; x<=x2; x++) {                       
  for (y=y1; y<=y2; y++) {                     
      base2[x + xres*y]=(char) ((base1[x + xres*y])>>12);    
      base1[x + xres*y]-=15*FDiv;
  }
}

}



main()
{
	char status, color;
	PCH ptr0;
	int x,y,row,col;
	int dlist[401][401];
	char clist[401][401];
	struct tri tlist[401][401][2];
	int plist[401*401];
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

dlist[0][0]=1+(rand()%(192*FDiv));
dlist[399][0]=1+(rand()%(192*FDiv));
dlist[399][399]=1+(rand()%(192*FDiv));
dlist[0][399]=1+(rand()%(192*FDiv));

subdivide((int *) dlist,401,0,0,399,399);

for (x=0; x<400; x++) {
  for (y=0; y<400; y++) {
      clist[x][y]=(char) (dlist[x][y]>>10);     
      dlist[x][y]-=10*FDiv;
  }
}


printf("\n\nCreating triangle mesh . . . .\n");

for (x=0; x<400; x++) {
  for (y=0; y<400; y++) {
	
	


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

/*

if (but.b2==1) {
  if (but.b1==1) { exit(0); }
  if (joy1.x>jhmax) { d-=FDiv; }
  if (joy1.x<jhmin) { d+=FDiv; }
  if (joy1.y>jvmax) { rho+=FDiv; }
  if (joy1.y<jvmin) { rho-=FDiv; } 
}
*/

if ((400-col)<pts) { col=400-pts; }
if ((400-row)<pts) { row=400-pts; }
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
fitdpnt(ptr1,((x-pts2)*FDiv),((y-pts2)*FDiv),dlist[x+row][y+col],s1,s2,c1,c2,rho,d,clist[x+row][y+col]);
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


