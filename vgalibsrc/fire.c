/* plasma.c -  Plasma 1.0 for OS/2 using vgalib */


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
#include <process.h>
#include <conio.h>

#define HANDLE 0
#define WAIT 1
#define F 2

BYTE red, green, blue;
BYTE savedac[768], newdac[768], nnewdac[768], hsidac[768];
PCH ptr0;
char ch;
unsigned int i,x,y,j,xx,yy;
float hue, sat, intensity;
char status;
BYTE fire1[64000],fire2[64000];
int flames[50];

main() {

Initgraph(&ptr0);

srand(getpid());

for (x=0; x<64; x++) {
hsidac[x*3]=x;
hsidac[x*3+1]=0;
hsidac[x*3+2]=0;
}

for (x=64; x<192; x++) {
hsidac[x*3]=63;
hsidac[x*3+1]=(x-64)/2;
hsidac[x*3+2]=0;
}

for (x=192; x<256; x++) {
hsidac[x*3]=63;
hsidac[x*3+1]=63;
hsidac[x*3+2]=(x-192);
}

memset(fire1,0,64000);
memset(fire2,0,64000);
memset(ptr0,0,64000);


WritePal(0,255,hsidac);

for (x=0; x<50; x++) {
flames[x]=rand() % 316;
}

while (!kbhit()) {

for (i=0; i<48; i++) {
flames[i]+=(rand() % 7) - 3;
if (flames[i]>317) flames[i]=1;
   else if (flames[i]<1) flames[i]=318;  

fire1[320*198+flames[i]]=255; 
fire1[320*198+flames[i]+1]=255;
fire1[320*198+flames[i]+2]=255;
fire1[320*197+flames[i]+1]=255;
}

for (x=(320*100); x<(199*320); x++) {
 xx=((fire1[x+1] + fire1[x-1] + fire1[x+320] + fire1[x-320]  
 + fire1[x-321] + fire1[x-319] + fire1[x+319] + fire1[x+321])/8); 
 if (xx>1)  fire2[x-320]=(BYTE) xx-1;
	else  fire2[x-320]=0; 
}

memcpy(fire1,fire2,64000);
memcpy(ptr0,fire2,64000);
} 
exit(0);

}


