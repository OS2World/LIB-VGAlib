/* shadepoly.c - Demo of 3D projection with the fixed point integer
 *		3D library and shading code. Uses the painter's algorithm
 *		to draw the shaded polys from back to front, and
 * John E. Stone - 9/01/93 
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
#define INCL_BASE
#include <os2.h>
#include "vgalib.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "int3dlib.h"
#include <time.h>
#include "inline.h"
#include "triangle.h"
 
#define maxnumballs 5000 
#define FDiv 4096
#define AmbLight 15
struct tri {
	int v1,v2,v3;
	int cx,cy,cz;
	char color;
};


struct tri tlist[3000];

int pts[maxnumballs+1][3],dpts[maxnumballs+1][3];
int order[maxnumballs+1],order2[maxnumballs+1];


int compare(const void * index1, const void * index2)
{
     if (tlist[*(int *) index1].cz>tlist[*(int *) index2].cz) return(1);
else if (tlist[*(int *) index1].cz<tlist[*(int *) index2].cz) return(-1); 
          else return(0);
}

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

/* Inlined codes for speed... */

#define SWP(_a_,_b_,_c_) { _c_=_a_; _a_=_b_; _b_=_c_; }


struct edge {
	int ymin, ymax, xi, si;
	int r, inc, dec;
};

_Inline void EdgeSetup(struct edge *e, int x0, int y0, int x1, int y1)
{
int sf, dx=x1-x0, dy=y1-y0;

e->ymin=y0;
e->ymax=y1;
if (dy != 0) {
  /* e->si=floor_div(dx,dy) */ 
  if (dx>=0) { e->si=(dx/dy); }
    else { e->si=((dx/dy) + (((dx%dy)==0) ? 0 : -1)); } 
  e->xi = x0 + e->si;
  sf=dx - e->si * dy;
  e->r = 2*sf - dy;
  e->inc = sf;
  e->dec = sf-dy;
  }
}

_Inline void triangle2(PCH ptr0, int x0, int y0, int x1, int y1, int x2, int y2, char color) {
int tmp,det, yi, xmin, xmax;
struct edge left, right;
int xr1,temp1,temp2;

/* order points correctly */
if (y0>y1) { SWP(y0,y1,tmp); SWP(x0,x1,tmp); }
if (y0>y2) { SWP(y0,y2,tmp); SWP(x0,x2,tmp); }
if (y1>y2) { SWP(y1,y2,tmp); SWP(x1,x2,tmp); }

det=(y1-y0)*(x2-x0) - (x1-x0)*(y2-y0);

if (det < 0)
 { EdgeSetup(&left, x0,y0,x2,y2);
   EdgeSetup(&right,x0,y0,x1,y1); }
else {
   EdgeSetup(&left, x0,y0,x1,y1);
   EdgeSetup(&right,x0,y0,x2,y2); }

for (yi=left.ymin +1; yi<=min(left.ymax,right.ymax); yi++) {
if ((yi>=0) && (yi<200)) {
  if ((left.xi>=0) && (right.xi<320)) {
	memset(ptr0+(320*yi)+left.xi,color,(right.xi-left.xi+1));  
	}
  else { if (left.xi<0) { temp1=0; }
	    else temp1=left.xi;
	 if (right.xi>319) { temp2=319; }
	    else temp2=right.xi;
	 if ((left.xi<320) && (right.xi>=0)) 
		memset(ptr0+(320*yi)+temp1,color,(temp2-temp1+1));
  }
}
  left.xi += left.si;
  if (left.r>=0) {
    left.xi++;
    left.r  += left.dec;
  }
  else { left.r += left.inc; }
  
  right.xi += right.si; 
  if (right.r>=0) {
    right.xi++;
    right.r  += right.dec;
  }
  else { right.r += right.inc; }
}

if (det>=0) EdgeSetup(&left, x1,y1,x2, y2);
else 	    EdgeSetup(&right,x1,y1,x2,y2);

for (yi=max(left.ymin,right.ymin)+1; yi<=left.ymax; yi++) {
if ((yi>=0) && (yi<200)) {
  if ((left.xi>=0) && (right.xi<320)) {
     memset(ptr0+(320*yi)+left.xi,color,(right.xi-left.xi+1));
     }
  else { if (left.xi<0) { temp1=0; }
	   else temp1=left.xi;
	 if (right.xi>319) { temp2=319; }
	   else temp2=right.xi;
	 if ((left.xi<320) && (right.xi>=0)) 
		memset(ptr0+(320*yi)+temp1,color,(temp2-temp1+1));
  }
} 
  left.xi += left.si; 
  if (left.r>=0) {
    left.xi++;
    left.r  += left.dec;
  }
  else { left.r += left.inc; }
  
  right.xi += right.si;
  if (right.r>=0) {
    right.xi++;
    right.r  += right.dec;
  }
  else { right.r += right.inc; }
}

} /* end of triangle */


/*
** isqrt() Computes the rounded integer square root of a 32-bit long passed to
**         it.  If your application only requires square roots of 16-bit
**         shorts, change all "long"s to "short"s, and change the
**         initialization of bitsqr from 0x40000000 to 0x4000.
**
**     This code uses successive approximation and the fact that
**     (a+b)^2 = (a^2 + 2ab + b^2).  Each iteration achieves an extra bit of
**     accuracy.
**
**     Originally posted to comp.graphics on December 30, 1989 by
**         rokicki@Neon.Stanford.EDU (Tomas G. Rokicki)
**     Rounding added on June 11, 1993 by
**         mark@godzilla.Quotron.COM (Mark T. Price) {ooh, big change :-}
*/

_Inline long fixsqrt(long val)
{
	register long bitsqr, root;
	for(bitsqr=0x40000000, root=0; bitsqr; bitsqr >>= 2)
	{

	/* modified midsection, hopefully better on instruction order */
	/* Only the if condition and order of the else was changed */

	if (bitsqr+root>val) {
			root = root >> 1; 
		}
		else {
			val -= bitsqr + root;
			root = (root >> 1) | bitsqr;
		}
	}

	/* round to nearest integer  (nope, forget that bud..)
	if(root < val)
		++root;  
	if (root==0) { root=1; }  */

	/* screw accuracy! J.S. :-)   */
	root++;   /* avoid div by zero */
	return root;
}



_Inline int shadepoly(int pn, int lx, int ly, int lz)
{
  int nx,ny,nz;
  int vx1,vy1,vz1,vx2,vy2,vz2;
  int lvx,lvy,lvz;
  int shade,ndotl;
  int n2,l2;
  int ln;

/* v1=vector from v1 to v2 */
/* v2=vector from v1 to v3 */
  vx1=(dpts[tlist[pn].v2][0]-dpts[tlist[pn].v1][0])>>1;
  vx2=(dpts[tlist[pn].v3][0]-dpts[tlist[pn].v1][0])>>1;
  vy1=(dpts[tlist[pn].v2][1]-dpts[tlist[pn].v1][1])>>1;
  vy2=(dpts[tlist[pn].v3][1]-dpts[tlist[pn].v1][1])>>1;
  vz1=(dpts[tlist[pn].v2][2]-dpts[tlist[pn].v1][2])>>1;
  vz2=(dpts[tlist[pn].v3][2]-dpts[tlist[pn].v1][2])>>1;

/* vector n=v1xv2    */
  nx=(vy1*vz2 - vy2*vz1);
  ny=(vx2*vz1 - vx1*vz2);
  nz=(vx1*vy2 - vx2*vy1);

/* Prevent overflows */
  while ((abs(nx)+abs(ny)+abs(nz))>(8*FDiv)) {
	nx=nx>>2;
	ny=ny>>2;
	nz=nz>>2;
	}

/* note: integer square root... */
  ln=fixsqrt(((nx*nx)>>12) + ((ny*ny)>>12) + ((nz*nz)>>12));

/* Normalize nx */
  nx=nx/ln;
  ny=ny/ln;
  nz=nz/ln;

/* light source vector = vector from center of tri to light source  */
  lvx=(lx-tlist[pn].cx);
  lvy=(ly-tlist[pn].cy);
  lvz=(lz-tlist[pn].cz);

/* Prevent overflows... */
  while ((abs(lvx)+abs(lvy)+abs(lvz))>(8*FDiv)) {
	lvx=lvx>>2;
	lvy=lvy>>2;
	lvz=lvz>>2;
	}


  /* note: integer square root... */
  ln=fixsqrt(((lvx*lvx)>>12) + ((lvy*lvy)>>12) + ((lvz*lvz)>>12));
  /* Normalize lv (light vector)  */
  lvx=lvx/ln;
  lvy=lvy/ln;
  lvz=lvz/ln;

  /* Find dot product of the 2 normalized vectors. . . */
  ndotl=(((nx*lvx + ny*lvy + nz*lvz))>>5)/3;
  shade=(ndotl);
  if (shade<0) shade=AmbLight;
     else shade=ndotl+AmbLight;

  if (shade>63) shade=63;

return shade;
}



void main() {
PCH ptr0;
char array[100000];
FILE * dfile;
float tx,ty,tz;
BYTE dac[768];
int x,y,z,i,j;
BYTE red,green,blue;
float hue,sat,intensity;
BYTE scrbak[64000],scrbuf[64000];
int kx,ky,kz;
int kx2,ky2,kz2;
int kr,kt,kp;
ROTMATRIX RotA;
int xt,yt,zt;
int zt1,zt2,zt3;
int framecount;
char str[80];
time_t tstart,tfinish;
double dt;
int waterenable,ainc,ainc2,ainc3,timeron;
int numverts,numtris,numdisptris;
int x1,y1,x2,y2,x3,y3;
int lix,liy,liz;
	HMOU hmou;
	MOUEVENTINFO mouev;
	USHORT moustat;
	USHORT fWait=0;

lix= 0;
liy= 0;
liz= -50000;
kr=0; kt=0; kp=0;

MouOpen(NULL,&hmou);
moustat=MOUSE_DISABLED | MOUSE_MICKEYS;
MouSetDevStatus(&moustat, hmou);

printf("opening mesh.dat\n");

dfile=fopen("mesh.dat","r");
printf("Reading mesh.dat... \n");
fscanf(dfile,"%d",&numverts);
printf("Number of vertexes: %d\n",numverts);
fscanf(dfile,"%d",&numtris);
printf("Number of triangles:  %d\n",numtris);
fscanf(dfile,"%d",&waterenable);
if (waterenable) printf("Mirror/Water enabled.. \n");
fscanf(dfile,"%d",&ainc);
fscanf(dfile,"%d",&ainc2);
fscanf(dfile,"%d",&ainc3);
fscanf(dfile,"%d",&timeron);

/* read in vertices */
for (i=0; i<numverts; i++) {
fscanf(dfile,"%f%f%f",&tx,&ty,&tz);
 pts[i][0]=tx*FDiv;
 pts[i][1]=ty*FDiv;
 pts[i][2]=tz*FDiv;
} 

/* read in triangles. . . */
for (i=0; i<numtris; i++) {
 fscanf(dfile,"%d%d%d%d",&tlist[i].v1,&tlist[i].v2,&tlist[i].v3,&tlist[i].color);
}

 
fclose(dfile);

initgraph(&ptr0);

for (x=1; x<=64; x++) {
dac[x*3]=x-1;
dac[x*3+1]=x-1;
dac[x*3+2]=x-1;
}
for (x=65; x<=128; x++) {
dac[x*3]=0;
dac[x*3+1]=0;
dac[x*3+2]=x-65;
}

dac[0]=0;
dac[1]=0;
dac[2]=0;

WAITVSYNC
WritePal(0,129,dac);

cls(ptr0,0);
for (x=0; x<200; x++) {
line(scrbak,0,x,319,x,((63.0*(x+1))/200.0)+65);
}


framecount=0;
time(&tstart);

/* main loop */
while (!kbhit()) {

MouReadEventQue(&mouev, &fWait, hmou);

while(mouev.fs!=0) {

if (mouev.fs==1) {
  kp-=((SHORT) mouev.col)*6;
  kt-=((SHORT) mouev.row)*6;
  }
  else {
  if (mouev.fs & 2) {
     kr+=((SHORT) mouev.col)*6;
    liz-=((SHORT) mouev.row)*6;
     }
  if (mouev.fs & 8)  {
    lix+=((SHORT) mouev.col)*6;
    liy+=((SHORT) mouev.row)*6;
  } 
  /* endif */

  }
MouReadEventQue(&mouev, &fWait, hmou);
} /* end while */




framecount++;

memcpy(scrbuf,scrbak,64000);

/*
kr+=ainc;
kp+=ainc2;
kt+=ainc3;
*/

IntInitRot(&RotA,kt,kp,kr);

/* Rotate all vertices for viewing. . . */
for (i=0; i<numverts; i++) {
ROTATE3D(RotA,pts[i][0],pts[i][1],pts[i][2],dpts[i][0],dpts[i][1],dpts[i][2]);
}

/* calculate center depths for triangles. . . */
for (i=0; i<numtris; i++) {
tlist[i].cx=(dpts[tlist[i].v1][0]+dpts[tlist[i].v2][0]+dpts[tlist[i].v3][0])/3;
tlist[i].cy=(dpts[tlist[i].v1][1]+dpts[tlist[i].v2][1]+dpts[tlist[i].v3][1])/3;
tlist[i].cz=(dpts[tlist[i].v1][2]+dpts[tlist[i].v2][2]+dpts[tlist[i].v3][2])/3;
order[i]=i;
}

/* calculate shading information */
for (i=0; i<numtris; i++) {
  tlist[i].color=shadepoly(i,lix,liy,liz); 
}

/* depthsort the list of triangles . . .*/
qsort(order,numtris,sizeof(int),compare);

/* backface removal code :(
zt=numtris-1;
numdisptris=0;
for (i=numtris-1; i>=0; i--) {
  order2[i]=order[i];
  if (tlist[order2[i]].color!=0) { 
     order[zt]=order2[i];
     numdisptris++;
     zt--;
  }     
}
*/

for (i=numtris-1; i>=0; i--) {

zt=0;

j=tlist[order[i]].v1;
zt1=dpts[j][2];
if ((zt1)>=-100*FDiv) {
 zt1=(3*FDiv*FDiv)/(zt1+20*FDiv);
  x1=160+((5*dpts[j][0]*zt1)>>20);
  y1=100-((dpts[j][1]*zt1)>>18);
  zt=1;
}

j=tlist[order[i]].v2;
zt2=dpts[j][2];
if ((zt2)>=-100*FDiv) {
 zt2=(3*FDiv*FDiv)/(zt2+20*FDiv);
  x2=160+((5*dpts[j][0]*zt2)>>20);
  y2=100-((dpts[j][1]*zt2)>>18);
} else { zt=0; }

j=tlist[order[i]].v3;
zt3=dpts[j][2];
if ((zt3)>=-100*FDiv) {
 zt3=(3*FDiv*FDiv)/(zt3+20*FDiv);
  x3=160+((5*dpts[j][0]*zt3)>>20);
  y3=100-((dpts[j][1]*zt3)>>18);
} else { zt=0; }


if ((zt=1)) {
triangle2(scrbuf,x1,y1,x2,y2,x3,y3,tlist[order[i]].color);
}
 

}  /* end of main triangle mesh draw loop */

/*
if (waterenable) 
for (i=160; i<180; i++) {
memcpy(scrbuf+((359-i)*320),scrbuf+(i*320),320);
}
*/

if (timeron) {
  time(&tfinish);
  dt=framecount/(0.001+difftime(tfinish,tstart));
  sprintf(str,"FPS:%3.1f",dt);
  putstring(scrbuf,2,2,str,255);
}

memcpy(ptr0,scrbuf,64000);
}
}
