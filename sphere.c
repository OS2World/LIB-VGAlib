/* sphere.c - draw a shaded sphere */


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
#include "vgalib.h"
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#define spheresize 100 

void makesphere(PCH ptr0, int d)
{
int x,y,i,j,r;
float rx,ry,rz;
float c,q;

r=d/2;

for (x=-r; x<=r; x++) {
  rx=(x*1.0)/(1.0*r);
  for (y=-r; y<=r; y++) {
    ry=(y*1.0)/(1.0*r);

    rz=sqrt(1.0-rx*rx-ry*ry);


    c=(2.0*rz)/sqrt(1.0 + 1.0 + 4.0);
    if (c>0.04) c=(rx-ry+2.0*rz)/sqrt(1.0 + 1.0 + 4.0);
    if (c<0.01) c=0.01; 
    if (c>1.0) c=1.0;	
    ptr0[(x+r) + (d*(y+r))]=(char) 64*(1.0*c);

  }
}
}

/*
void btblt(PCH src, int sx, int sy, PCH dest, int dx, int dy, int x, int y)
{
int i,j,k,l;

if ((x<dx) && (y<dy) && (x+sx>0) && (y+sy>0)) { 
  i=l=k=0;
  if (x<0) { l=x; i=x; }
  if (y<0) { k=-y; }
  if ((x+sx) > dx) { i=(dx-(x+sx)); }
  if ((y+sy) > dy) { sy=sy+(dy-(y+sy)); }

  for (j=k; j<sy; j++) {
    memcpy((PCH) (dest+x-l+dx*(y+j)),(PCH) (src+sx*j-l),sx+i);    
  }
}
}
*/

void main() {
PCH ptr0;
char array[100000];
BYTE dac[768];
int x,y,z,i,j;
BYTE red,green,blue;
float hue,sat,intensity;


initgraph(&ptr0);

for (x=1; x<=65; x++) {
hue=0.5;
sat=0.09;
intensity=x/64.0;
HSItoRGB(hue,sat,intensity,&red,&green,&blue);
dac[x*3]=x-1;
dac[x*3+1]=x-1;
dac[x*3+2]=x-1;

}
dac[0]=0;
dac[1]=0;
dac[2]=0;

WAITVSYNC
WritePal(0,65,dac);

cls(ptr0,15);

for (x=0; x<255; x++) {
line(ptr0,x,0,x,199,(char) x);
}

makesphere(array,spheresize);

for (x=0; x<spheresize; x++) {
  for (y=0; y<spheresize; y++) {
	ptr0[x+(320*y)]=array[x+(spheresize*y)];
  }
}



cls(ptr0,0);
for (z=1; z<25; z++) {
for(x=-200; x<300; x+=1){
WAITVSYNC
maskblt(array,array,spheresize,spheresize,ptr0,320,200,x*1.5,x);
}
}

while (!kbhit());


}
