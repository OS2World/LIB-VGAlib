/* 
 *  3dlib.c - 3D graphics library  
 *            By John E. Stone - johns@cs.umr.edu
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
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define INCL_BASE
#include <os2.h>
#include "3dlib.h"
#include "vgalib.h"

#define FDiv 4096 
#define FShift 12 
#define PMul 11

void ftdpnt(PCH ptr0,double x,double y,double z,double rho,
	    double theta,double phi,double d,char color) 
{
double sx,sy,s1,s2,s3,c1,c2,c3,xe,ye,ze;
unsigned int x2,y2;

s1=sin(theta);
c1=cos(theta);
s2=sin(phi);
c2=cos(phi);
s3=-x*c1;
c3=y*s1;
xe=(-x*s1) + (y*c1);
ye=s3*c2 - c3*c2 + z*s2;
ze=d/(s3*s2 - c3*s2 - z*c2 + rho);
sx=60.0*(xe*ze);
sy=40.0*(ye*ze);

x2=sx+160;
y2=(320-sy)+100;
if ((x2<320) && (y2<200)) {
   *(PCH) (ptr0+x2+(320*y2))=(char) color;
   }
}



void fftdpnt(PCH ptr0,double x,double y,double z,double s1,double s2,
	     double c1,double c2,double rho,double d,char color) 
{
double sx,sy,s3,c3,xe,ye,ze;
unsigned int x2,y2;

s3=-x*c1;
c3=y*s1;
xe=(-x*s1) + (y*c1);
ye=s3*c2 - c3*c2 + z*s2;
ze=d/(s3*s2 - c3*s2 - z*c2 + rho);
sx=60.0*(xe*ze);
sy=40.0*(ye*ze);

x2=sx+160;
y2=sy+100;
if ((x2<320) && (y2<200)) {
   *(PCH) (ptr0+x2+(320*y2))=(char) color;
   }
}


void fitdpnt(PCH ptr0,long x,long y,long z,long s1,long s2,
	     long c1,long c2,long rho,long d,char color) 
{
long s3,c3,xe,ye,ze;
unsigned int x2,y2;

s3=(-x*c1)>>FShift;
c3=(y*s1)>>FShift;
xe=((y*c1) - (x*s1))>>FShift;
ye=((s3*c2) - (c3*c2) + (z*s2))>>FShift;
ze=(d<<PMul)/(((((s3*s2) - (c3*s2) - (z*c2))>>FShift) + rho));
x2=160+((5*(xe*ze))>>(FShift+PMul-3));
y2=100-((ye*ze)>>(FShift+PMul-5));
if ((x2<320) && (y2<200)) {
   ptr0[x2+(320*y2)]=(char) color;
   }
}



/*
void fitdmat( ptr0, base1, base2, xres, x1, y1, pts, rho, d, theta, phi) 
PCH ptr0;
int *base1;
int *base2;
long xres, x1, y1, pts, rho, d, theta, phi;

{
long s1, s2, s3, c1, c2, c3;
long xa,xb,xc;
unsigned int x2,y2,x3, y3;
long xe,ye,ze;
int x,y,z,xx,yy;
char color;
int pts2;

s1=(long) (FDiv*sin(theta));
s2=(long) (FDiv*sin(phi));
c1=(long) (FDiv*cos(theta));
c2=(long) (FDiv*cos(phi));
x2=x1+pts-1;
y2=x2+pts-1;
pts2=pts>>1;


for (xx=x1; xx<=x2; xx++) {
  x=xx-x1-pts2;
  s3=(-x*c1)>>10;
  xa=-x*s1;
  xb=s3*c2;
  xc=s3*s2;
  for (yy=y1; yy<=y2; yy++) {
    y=yy-y1-pts2;
    c3=(y*s1)>>10;
    xe=(xa + (y*c1))>>10;
    ye=(xb - (c3*c2) + (z*s2))>>10;
    ze=(d<<10)/((((xc - (c3*s2) - (z*c2))>>10) + rho));
x3=160+((40*(x3*ze))>>20);
y3=100-((30*(ye*ze))>>20);
if ((x3<320) && (y2<200)) {
	*(PCH) (ptr0+x3+(320*y3))=(char) color;
        }

}


*/
