/* Spirals.c   
 * By John E. Stone
 * 10/19/92
 * 
 */

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

#include<stdlib.h>
#define INCL_BASE
#include<os2.h>
#include<math.h>
#include<conio.h>
#include<stdio.h>
#include"vgalib.h"
#include<process.h>
#define FDiv 4096
#define HANDLE 0
#define WAIT 1

PCH ptr0;

void keycheck(void *arg);

int main(int argc, char *argv[])
{
char status;
int ainc,inc,ang,len,s,c,l;
int xt,yt;
unsigned x,y,x2,y2;
int ca;
float hue,sat,intensity;
BYTE red,green,blue;
BYTE hsidac[769];
int KEYHIT;

printf("Spirals 1.0\nBy John E. Stone\n10/19/92\n\n");
printf("\nSend email to: johns@cs.umr.edu\n");
DosSleep(2000L);

KEYHIT=0;

/* setup for graphics mode... */
Initgraph(&ptr0);

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

srand(getpid());

while (!kbhit()) {
cls(ptr0,0);

ainc=(rand() % 12867)+8;
inc=(rand() % 8192)+32;
len=0;
ang=0;
x=160;
y=100;
x2=x;
y2=y;
xt=160*FDiv;
yt=100*FDiv;
ca=0;

WAITVSYNC
while ((x<320) && (y<200)) {
ca++;
len+=inc;
ang+=ainc;
s=ISIN(ang);
c=ICOS(ang);

xt+=((c*len)>>12);
yt+=((s*len)>>12);
x=((xt>>12));
y=((yt>>12));
line(ptr0,x,y,x2,y2,(ca % 255)+1);
x2=x;
y2=y;

}

}

VioScrLock(WAIT,&status,HANDLE);
cls(ptr0,0);
VioScrUnLock(HANDLE);
exit(0);
}


