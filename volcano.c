/* volcano.c - Cute little volcano demo */


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

#define HANDLE 0
#define WAIT 1
#define grv 4
#define spx 640
#define BLAST 10
#define GROUND 6
#define LAVA 39

PCH ptr0;
unsigned int NUMPTS;

void movepart(int p);
void initpart(int p);
void explosion(PCH ptr0, int spy);
void keycheck(void *arg);


int prt[2001][8];
int tf=4,ts,dd[3]={0,-1,1},spy=797,prl=8;
volatile static int KEYHIT;



int main(int argc, char *argv[])
{
char status;
int p, mxh, pct=0;
char *nparg;
int numpoints;



if(argc==2)
    {
    nparg = argv[1];
    numpoints = atoi(nparg);

    if(numpoints==0)
        {
        fprintf(stderr,"%s:  number of points zero or invalid\n",argv[0]);
        exit(-1);
        }

    NUMPTS = numpoints;
    }
else
    {
    NUMPTS = 50;  /*  default  */
    }

printf("Volcano - a volcano simulation -  Version 1.0  \n\n");
printf("By Tim Heil and John Stone \n");
printf("OS/2 version by John Stone \n\n");
printf("For info email to:  johns@cs.umr.edu  \n\n\n");
printf("To use:  volcano n       (n is a number from 40-2000) \n");
printf("default (if no param) is 40\n");
printf("Press a key to begin. . . \n");
status=getch();

KEYHIT=0;

/* setup for graphics mode... */

Initgraph(&ptr0);

_beginthread(keycheck,NULL,4096,NULL);


ts=1<<tf;ts=ts*ts*2;
	while(KEYHIT==0) {
	VioScrLock(WAIT, &status, HANDLE);
		mxh=900;
		for (p=0;p<NUMPTS;p++) {
			if (prt[p][1]==0) { initpart(p); }
			else movepart(p);
			if (prt[p][3]<mxh) mxh=prt[p][3];
		}
		if (mxh*4>(spy-prl*4-8)) {
			pct++;
			if (pct==BLAST) {
				pct=0;
				spy-=4;
				};
		}

if (spy<350) {
for (p=0; p<NUMPTS; p++) {
  putpixel(ptr0,prt[p][2],prt[p][3],(char) 0);
}
spy=436;
explosion(ptr0,spy);
spy=468;
for (p=0; p<NUMPTS; p++) { prt[p][1]=0; }
}

VioScrUnLock(HANDLE);
}

VioScrLock(WAIT,&status,HANDLE);
cls(ptr0,0);

VioScrUnLock(HANDLE);
exit(0);
}

void initpart(int p)
{
	prt[p][0]=(rand() % 27) - 13;
	prt[p][1]=-1*((rand() % 60)+5);
	prt[p][2]=spx+(rand() % 30)-15;
	prt[p][3]=spy;
	prt[p][4]=0;
	prt[p][5]=LAVA+(rand() % 5);
                prt[p][6]=prt[p][2];
	prt[p][7]=prt[p][3];
if (((unsigned int) prt[p][2]<320) &&
	((unsigned int) prt[p][3]<800)) {	
*(PCH) (ptr0+prt[p][2]+(320*(spy>>2)))=(char) prt[p][5];
}
}

void movepart(int p)
{
	long x,y,t,f;
	long ag;
	int d,x2;

t=prt[p][4]+1;
if (t==-1) {
    x=prt[p][2];
    y=prt[p][3]+1;
    if (y<200) {
		for (d=0; d<3; d++) {
		x2=x+dd[d];
		if (getpixel(ptr0,x2,y)!=(char) GROUND) {
			  putpixel(ptr0,prt[p][2],prt[p][3],0);
			  putpixel(ptr0,x2,y,GROUND);

/*  if (((unsigned int) prt[p][2]<320) && 
			      ((unsigned int) prt[p][3]<200)) {
			      *(PCH) (ptr0+prt[p][2]+(320*prt[p][3]))=(char) 0;
			  }
			  if (((unsigned int) x2<320) && 
			      ((unsigned int) y<200)) {
			      *(PCH) (ptr0+x2+(320*y))=(char) GROUND;
			  } 
*/
			  prt[p][2]=x2;
			  prt[p][3]=y;
			  return;
			  }
			}
		}
/* if (((unsigned int) prt[p][2]<320) && 
	    ((unsigned int) prt[p][3]<200)) {
		*(PCH) (ptr0+prt[p][2]+(320*prt[p][3]))=(char) GROUND;
	} 
*/
        putpixel(ptr0,prt[p][2],prt[p][3],GROUND);
	prt[p][1]=0;
	return;
	} /* end if (y<200) */

	x=(prt[p][6]+((prt[p][0]*t)>>tf))>>2;
	ag=(grv*t*t)/ts;
	y=(prt[p][7]+((prt[p][1]*t)>>tf)+ag)>>2;

if ((y<200) && ((getpixel(ptr0,x,y)!=GROUND) || (t<prl)))  {
/* if (((unsigned int) prt[p][2]<320) &&
		    ((unsigned int) prt[p][3]<200)) {
			*(PCH) (ptr0+prt[p][2]+(prt[p][3]*320))=(char) 0;
		}
		if ((x<320) && (y<200)) {
			*(PCH) (ptr0+x+(320*y))=(char) prt[p][5];
		} 
*/
		putpixel(ptr0,prt[p][2],prt[p][3],0);
		putpixel(ptr0,x,y,prt[p][5]);

		prt[p][2]=x;
		prt[p][3]=y;
		prt[p][4]=t;
		}
	else {  prt[p][4]=-2; }
}

void explosion(PCH ptr0,int spy)
{
float p;
unsigned int q,r,s;
unsigned int x1,y1,z;
char status;

z=(unsigned int) spy>>2;

for (q=0; q<400; q++) {
  for (s=0; s<200; s++) {
	p=(float) (rand() % 314)/100;
	r=rand() % 90;
	x1=(unsigned int) 155+((int) (rand() % 10)+(r*(cos(p))));
	y1=(unsigned int) z - ((int) (r*(sin(p))));
	line(ptr0,160,z,x1,y1,(char) (LAVA+(rand() % 5)) );
  }
  memset((PCH) ptr0,0,((z+1)*320));
}
}

void keycheck(void *arg) {
char key1;
key1=getchar();

KEYHIT=1;
_endthread();
}
