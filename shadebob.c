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
#define ADD 45 
#define BOBS 40

BYTE red, green, blue;
BYTE savedac[768], newdac[768], nnewdac[768], hsidac[768];
PCH ptr0;
char ch;
unsigned int i,x,y,j,xx,yy;
float hue, sat, intensity;
char status;
BYTE fire1[64000],fire2[64000];
int bobs[BOBS][4];

main() {

Initgraph(&ptr0);

srand(getpid());

DosSetPriority(0,1,31,getpid());


/*
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
*/

for (x=0; x<256; x++) {
hue=(x/255.0);
sat=0.75;
intensity=1.0;

HSItoRGB(hue,sat,intensity,&red,&green,&blue);
hsidac[x*3]=red;
hsidac[x*3+1]=green;
hsidac[x*3+2]=blue;

}


memset(fire1,0,64000);
memset(fire2,0,64000);
memset(ptr0,0,64000);


WritePal(0,255,hsidac);

for (x=0; x<BOBS; x++) {
  bobs[x][0]=rand() % 320;
  bobs[x][1]=rand() % 200;
  bobs[x][2]=(rand() % 7) - 3;
  if (bobs[x][2]==0) bobs[x][2]=1;
  if (bobs[x][3]==0) bobs[x][3]=1;
  bobs[x][3]=(rand() % 7) - 3;
}

while (!kbhit()) {

for (x=0; x<BOBS; x++) {
  bobs[x][0]+=bobs[x][2];
  bobs[x][1]+=bobs[x][3];
     if (bobs[x][0]<0)   { bobs[x][0]=0;   bobs[x][2]=-bobs[x][2]; }
else if (bobs[x][0]>316) { bobs[x][0]=316; bobs[x][2]=-bobs[x][2]; }
     if (bobs[x][1]<4)   { bobs[x][1]=4;   bobs[x][3]=-bobs[x][3]; }
else if (bobs[x][1]>196) { bobs[x][1]=196; bobs[x][3]=-bobs[x][3]; }
 
i=bobs[x][0]+bobs[x][1]*320;

 fire1[i]+=ADD; 
 fire1[i+1]+=ADD;
 fire1[i+2]+=ADD;
 fire1[i+3]+=ADD;
 fire1[i+320]+=ADD;
 fire1[i+321]+=ADD;
 fire1[i+322]+=ADD;
 fire1[i+323]+=ADD;
 fire1[i+640]+=ADD;
 fire1[i+641]+=ADD;
 fire1[i+642]+=ADD;
 fire1[i+643]+=ADD;
 fire1[i+1260]+=ADD;
 fire1[i+1261]+=ADD;
 fire1[i+1262]+=ADD;
 fire1[i+1263]+=ADD;
}


memset(fire1,0,320);
for (x=321; x<(198*320); x++) {
 fire2[x]=(BYTE) ((fire1[x+1] + fire1[x-1] + fire1[x+320] + fire1[x-320] + 
      fire1[x-321] + fire1[x-319] + fire1[x+319] + fire1[x+321])/8);
}

memset(fire2,0,320);
memcpy(fire1,fire2,64000);
memcpy(ptr0,fire2,64000);
} 
exit(0);

}


