/* paldemo.c - palette manipulation demo */


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

#define HANDLE 0
#define WAIT 1
#define BUFSIZE 12

main()
{
	struct _VIOPHYSBUF phys;
	struct _VIOMODEINFO orig,moda;
	char status;
	unsigned int index;
	unsigned rc;
	unsigned short color;
	PCH ptr0;
	unsigned int x,y,j,xx,yy;
	char * pal[1000];
	char testcolor;
	BYTE savedac[768], newdac[768], nnewdac[768], hsidac[768];
	float hue,sat,intensity;
	BYTE red,green,blue;
	iPoint triangle[8];

phys.pBuf=(unsigned char *) 0xA0000;
phys.cb=65536;

moda.cb=BUFSIZE;
moda.fbType=3;
moda.color=8;
moda.col=40;
moda.row=25;
moda.hres=320;
moda.vres=200;

VioGetMode(&orig, HANDLE);

if (rc=VioSetMode(&moda, HANDLE) )
   { printf("VioSetMode error=%u",rc);  exit(1); }

if (rc=VioGetPhysBuf(&phys, 0) )
   { printf("VioGetPhysBuf error=%u",rc); exit(1); }

ptr0=MAKEP(phys.asel[0],0);

VioScrLock(WAIT, &status, HANDLE);
cls(ptr0,0);

ReadPal(0, 256, savedac);
ReadPal(0, 256, nnewdac);

for (x=0; x<768; x++) {
	newdac[x]=0;
	}

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

cls(ptr0,0);

for (x=0; x<320; x++) {
  for (y=0; y<200; y++) {
    putpixel(ptr0,x,y,y);
  }
}


DosSleep(4000L);

CrossFade(hsidac,savedac);

for (x=0; x<384; x++) {
RotatePal(savedac,1,255,0);
}



for (x=0; x<100; x++) {
WAITVSYNC
Writepal(0,256,nnewdac);
WAITVSYNC
Writepal(0,256,savedac); 
}


for (x=0; x<3; x++) {
CrossFade(savedac,nnewdac);
CrossFade(nnewdac,hsidac);
CrossFade(hsidac,savedac);
}

CrossFade(savedac,hsidac);

for (x=0; x<300000; x++) {
putpixel(ptr0,(rand() % 320),(rand() % 200),(rand() % 256));
}

for (x=0; x<1000; x++) {
RotatePal(hsidac,1,255,0);
}

cls(ptr0,0);
for (x=0; x<256; x++) {
line(ptr0,x,0,x,199,x);
}

for (x=0; x<1000; x++) {
RotatePal(hsidac,1,255,0);
}

FadeOut(hsidac);

cls(ptr0,0);


FadeIn(hsidac);

for (j=0; j<60000; j++) {
xx=rand() % 200;
yy=rand() % 100;

triangle[0].X=0;
triangle[0].Y=40+yy;
triangle[1].X=xx+30;
triangle[1].Y=yy;
triangle[2].X=xx+60;
triangle[2].Y=yy+40; 

PolygonSimple(ptr0, triangle, 3, (rand() % 255) );
}


VioSetMode(&orig,HANDLE);
cls(ptr0,0);
VioScrUnLock(HANDLE);
exit(0);
}

