/* Wave.c - 3d graphics demo, uses some float, some fix... first attempt. */


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
#include "3dlib.h"

#define HANDLE 0
#define WAIT 1
#define FDiv 4096
 

main()
{
	char status;
	char color;
	PCH ptr0;
	int x,y,row,col;
	long dlist[401][401];
	char clist[401][401];
	double theta,phi;
	float lx,ly;
	long pts,pts2,height,rho,d,s1,s2,c1,c2;
	char ptr1[65536];


printf("Wave  V1.0   By John E. Stone   \n\n");
printf("Written for OS/2 2.0 320x200 direct graphics.\n");
printf("send email to: johns@cs.umr.edu for info  \n");
printf("\n\nGood defaults: rho=100  d=17  height=5  points=32 ");
printf("\nmaximums: points=100  (rho d height are all interrelated)\n");

printf("\n\n\nEnter rho:  \n");
scanf("%d",&rho);
rho=rho*FDiv;
printf("\n\nEnter d:   \n");
scanf("%d",&d);
d=d*FDiv;
printf("\n\nEnter height:   \n");
scanf("%d",&height);
printf("\n\nEnter number of points per side (16-100):  \n");
scanf("%d",&pts);
pts2=pts>>1;

printf("\n\n\nPrecalculating 160,000 altitude points /w colors. . . . .\n");
printf("(this is why it needs ~1Mb of free ram to run.)\n");

for (x=0; x<400; x++) {
 for (y=0; y<400; y++) {
   lx=(x/5.0)-40.0;
   ly=(y/5.0)-40.0;
   dlist[x][y]=FDiv*height*sin(sqrt(lx*lx + ly*ly));  
   clist[x][y]=(char) 26+(4*sin(sqrt(lx*lx + ly*ly)));
 }
}


Initgraph(&ptr0);

color=15; 
phi=1.0;


col=0;
for (row=0; row<(400-pts); row++) {
theta+=0.01;
col=row;

s1=(long) (FDiv*sin(theta));
s2=(long) (FDiv*sin(phi));
c1=(long) (FDiv*cos(theta));
c2=(long) (FDiv*cos(phi));

DosSleep(1);

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


