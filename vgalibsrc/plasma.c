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
unsigned int x,y,j,xx,yy;
float hue, sat, intensity;
char status;


void Adj(ptr0, xa, ya, x, y, xb, yb) 
PCH ptr0;
int xa,ya,x,y,xb,yb;
{

int d;
long int v;

if (getpixel(ptr0,x,y)==0) {
   d=abs(xa-xb)+abs(ya-yb);
v=(getpixel(ptr0,xa,ya)+getpixel(ptr0,xb,yb))/2 + ((rand()%100)-50)*d*F/100; 
   if (v<1) v=1;
   if (v>192) v=192;
   putpixel(ptr0,x,y,(char) v);
}

} /* end of adjust */


void Subdiv(ptr0,x1,y1,x2,y2) 
PCH ptr0;
int x1,y1,x2,y2;
{
int x,y;
long int v;

if (((x2-x1)<2) && ((y2-y1)<2)) { return; }

{
x=(x1+x2)/2;
y=(y1+y2)/2;

Adj(ptr0,x1,y1,x,y1,x2,y1);
Adj(ptr0,x2,y1,x2,y,x2,y2);
Adj(ptr0,x1,y2,x,y2,x2,y2);
Adj(ptr0,x1,y1,x1,y,x1,y2);

if (getpixel(ptr0,x,y)==0) {
	v=(getpixel(ptr0,x1,y1) + getpixel(ptr0,x2,y1) + 
	   getpixel(ptr0,x2,y2) + getpixel(ptr0,x1,y2)   )/4;
	putpixel(ptr0,x,y,(char) v);
	}

Subdiv(ptr0,x1,y1,x,y);
Subdiv(ptr0,x,y1,x2,y);
Subdiv(ptr0,x,y,x2,y2);
Subdiv(ptr0,x1,y,x,y2);

}
}




main() {

Initgraph(&ptr0);

ReadPal(0, 256, savedac);
ReadPal(0, 256, nnewdac);

srand(getpid());

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

putpixel(ptr0,0,0,1+(rand()%192));
putpixel(ptr0,319,0,1+(rand()%192));
putpixel(ptr0,319,199,1+(rand()%192));
putpixel(ptr0,0,199,1+(rand()%192));

Subdiv(ptr0,0,0,319,199);

while (!kbhit()) {
RotatePal(hsidac,1,255,0);
}

exit(0);

}





