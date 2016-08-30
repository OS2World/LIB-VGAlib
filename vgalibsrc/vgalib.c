/* Vgalib.c  
 *
 * 7/27/93   By John E. Stone - johns@cs.umr.edu
 * This file contains most of the code for Vgalib.
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
#define INCL_SUB
#include <os2.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define HANDLE 0
#define WAIT 1
#define BUFSIZE 12
#define XRES 320
#define YRES 200
#define MAXY 199
#define MINY 0
#define MAXX 319
#define MINX 0
#define SWAP(a,b) {a^=b; b^a; a^=b; }
#define ABS(a) (((a)<0) ? -(a) : (a))
#define SGN(a) (((a)<0) ? -1 : 1)
#define SQR(a) ((a)*(a))
#define FDiv 4096 
#define F 3

extern unsigned char alphabet[128][8][8];


typedef struct {
	SHORT X, Y, Z;
} iPoint;

typedef struct {
	BYTE Org, Dest, Color;
} Line;
	


/* defines for port operations */                                  
#define MISC_OUTPUT     0x03c2  /* Miscellaneous Output register */
#define SC_INDEX        0x03c4  /* Sequence Controller Index */    
#define GC_INDEX        0x03ce  /* Graphics controller Index */    
#define CRTC_INDEX      0x03d4  /* CRT Controller Index */         
#define INPUT_STATUS_0  0x03da  /* Input status 0 register */      
#define DAC_READ_INDEX  0x03c7  /* DAC read index register */ 
#define DAC_WRITE_INDEX 0x03c8  /* DAC write index register */
#define DAC_DATA        0x03c9  /* DAC data register */       
#define MAP_MASK        0x02    /* select write planes */     
#define READ_PLANE      0x04    /* select read plane */       
#define MIN_PORT        MISC_OUTPUT     /* lowest port accessed */
#define MAX_PORT        INPUT_STATUS_0  /* highest port accessed */
#define WAITVSYNC { while(INP8(0x03da)&8); while(!(INP8(0x03da)&8)); }
 
extern _Far16 _Pascal OUTP8(USHORT, UCHAR);
extern _Far16 _Pascal OUTP16(USHORT, USHORT);
extern UCHAR _Far16 _Pascal INP8(USHORT);
extern USHORT _Far16 _Pascal INP16(USHORT);



/* beginning of code.... */

int Initgraph(PCH *ptr0) { 
struct _VIOPHYSBUF phys;
struct _VIOMODEINFO moda;
char status;
unsigned rc;
char stbuf[100];

phys.pBuf=(unsigned char *) 0xA0000;
phys.cb=65536;

moda.cb=BUFSIZE;
moda.fbType=3;
moda.color=8;
moda.col=40;
moda.row=25;
moda.hres=320;
moda.vres=200;


if (rc=VioSetMode(&moda, HANDLE) )
   { printf("VioSetMode error=%u",rc);  exit(1); }

if (rc=VioGetPhysBuf(&phys, 0) )
   { printf("VioGetPhysBuf error=%u",rc); exit(1); }

*ptr0=MAKEP(phys.asel[0],0);

VioScrLock(WAIT, &status, HANDLE);
memset(*ptr0,0,64000);
return(0);

} /* end of Initgraph */



void cls(PCH ptr0, char color) {
memset((PCH) ptr0,(color*256 + color),64000);
}

void putpixel(PCH ptr0,unsigned int x, unsigned int y, char color) {
if ((x<XRES) && (y<YRES)) { 
  ptr0[x+(XRES*y)]=color;
}
}

char getpixel(PCH ptr0, unsigned int x, unsigned int y) {
char temp=0;
if ((x<XRES) && (y<YRES)) {
temp=((char) ptr0[x+(XRES*y)]);
}
return temp;
}

 
void line(PCH ptr0,unsigned int x1, unsigned int y1, 
                   unsigned int x2, unsigned int y2, char color) { 

unsigned int x,y;
int d,dx,dy,incrE,incrNE;

if ((x1>MAXX) || (x2>MAXX)) { return; }
if ((y1>MAXY) || (y2>MAXY)) { return; }
if (x1>x2) {
   x=x2;
   x2=x1;
   x1=x;
   y=y2;
   y2=y1;
   y1=y;
}
else {
   x=x1;
   y=y1;
}

dx=x2-x1;
dy=y2-y1;
if (abs(dx)>=abs(dy)) {

  if (dy>=0) {
	ptr0[x+(XRES*y)]=color;
	d=(2*dy) - dx;
	incrE=2*dy;
	incrNE=2*(dy-dx);

	while (x<x2)
	{
		if (d<=0)
	        {  d+=incrE;
		   x++; }
		else
		{
		   d+=incrNE;
		   x++;
		   y++;
		}
	ptr0[x+(XRES*y)]=color;
	}
  }
  else {
	ptr0[x+(XRES*y)]=color;
	d=(2*dy)+dx;
	incrE=2*dy;
	incrNE=2*(dy+dx);
	while (x<x2)
	{
		if (d>=0)
		{ d+=incrE;
		  x++; }
		else
		{ d+=incrNE;
		  x++;  
		  y--; 
	        }
	ptr0[x+(XRES*y)]=color;
	} 
} 

} /* end of if (dx>dy) */
else {  /* if (dx<dy) */

  if (dy>=0) {
	ptr0[x+(XRES*y)]=color;
	d=(2*dx) - dy;
	incrE=2*dx;
	incrNE=2*(dx-dy);
	while (y<y2)
	{
		if (d<=0)
	        {  d+=incrE;
		   y++; }
		else
		{
		   d+=incrNE;
		   y++;
		   x++;
		}
	ptr0[x+(XRES*y)]=color;
	}
  }
  else {
	ptr0[x+(XRES*y)]=color;
	d=(2*dx)+dy;
	incrE=2*dx;
	incrNE=2*(dy+dx);
	while (y>y2)
	{
		if (d<=0)
		{ d+=incrE;
		  y--;
		   }
		else
		{ d+=incrNE;
		  y--; 
	          x++;}
	ptr0[x+(XRES*y)]=color;
	} 
  }
}
} /* end of line */




void box(PCH ptr0, unsigned int x1, unsigned int y1,
	 unsigned int x2, unsigned int y2, char color) {

unsigned int y,lx,ly,ux,uy;
register unsigned int x;

  lx=min(x1,x2);
  ux=max(x1,x2);
  ly=min(y1,y2);
  uy=max(y1,y2);

  for (y=ly*XRES; y<=uy*XRES; y+=XRES) {
    for (x=lx;x<=ux;x++) {
      ptr0[y+x]=color;
    }
  }
}

void circlepoints(PCH ptr0, int x, int y, unsigned int xc,
			unsigned int yc, char color) {

ptr0[x+xc+(y+yc)*XRES]=color;
ptr0[y+xc+(x+yc)*XRES]=color;
ptr0[y+xc+(-x+yc)*XRES]=color;
ptr0[x+xc+(-y+yc)*XRES]=color;
ptr0[-x+xc+(-y+yc)*XRES]=color;
ptr0[-y+xc+(-x+yc)*XRES]=color;
ptr0[-y+xc+(x+yc)*XRES]=color;
ptr0[-x+xc+(y+yc)*XRES]=color;
}

void circle(PCH ptr0, unsigned int xc, unsigned int yc,
		unsigned int radius, char color) {
int x,y,d;

x=0;
y=radius;
d=1-radius;
circlepoints(ptr0,x,y,xc,yc,color);

while (y>x) {
	if (d<0) {
		d+=2*x+3;
		x++;
	}
	else {
		d+=2*(x-y)+5;
		x++;
		y--;
	}
     circlepoints(ptr0,x,y,xc,yc,color);
}
}

void rectangle(PCH ptr0, USHORT x1, USHORT y1, USHORT x2, USHORT y2, BYTE color)
{
    int  i, width = x2 - x1;
    PCH  mem = ptr0 + (y1 * XRES) + x1;

    for (i = y1; i <= y2; i++) {
	memset(mem, color, width);
	mem += XRES;
    }				/* endfor */
}


void scanline(PCH ptr0, SHORT x1, SHORT x2, SHORT y, BYTE color)
{
  if ((y < MINY) || (y > MAXY))
    return;
  if (x2 < x1)
    SWAP(x1, x2)
      if ((x1 > MAXX) || (x2 < MINX))
	return;
  x1 = max(x1, MINX);
  x2 = min(x2, MAXX);
  memset((ptr0 + (y*XRES) + x1), color, (x2 - x1));
}

void BresPoints(SHORT x1, SHORT y1, SHORT x2, SHORT y2, SHORT list[])
{
    int             d, x, y, ax, ay, sx, sy, dx, dy, l;

    dx = x2 - x1;
    ax = ABS(dx) << 1;
    sx = SGN(dx);
    dy = y2 - y1;
    ay = ABS(dy) << 1;
    sy = SGN(dy);

    x = x1;
    y = y1;

    if (ax > ay) {		/* x dominant */
	d = ay - (ax >> 1);
	for (;;) {
	    if (x == x2)
		return;
	    if (d >= 0) {
		if ((y >= MINY) && (y <= MAXY))
		    list[y] = x;
		y += sy;
		d -= ax;
	    }
	    x += sx;
	    d += ay;
	}
    } else {			/* y dominant */
	d = ax - (ay >> 1);
	for (;;) {
	    if (y == y2)
		return;
	    if (d >= 0) {
		x += sx;
		d -= ay;
	    }
	    if ((y >= MINY) && (y <= MAXY))
		list[y] = x;
	    y += sy;
	    d += ax;
	}
    }
}



void PolygonSimple(PCH ptr0, iPoint * Points, BYTE NumPoints, BYTE color)
{
    static SHORT xlist1[240],xlist2[240];
    SHORT           x, y, dy, left, right, temp, y1, y2, off;
    SHORT           i, li, ri, nli, nri, sl, ly, ry, top, bottom, rem,
                    ldy, rdy;
    BYTE            type, mirror;
    SHORT xl1,xl2;

    /* find top vertex */

    temp = Points[0].Y;
    top = 0;

    for (i = 1; i < NumPoints; i++) {
	if (Points[i].Y < temp) {
	    temp = Points[i].Y;
	    top = i;
	}
    }

    /* find bottom vertex */

    temp = Points[0].Y;
    bottom = 0;

    for (i = 1; i < NumPoints; i++) {
	if (Points[i].Y > temp) {
	    temp = Points[i].Y;
	    bottom = i;
	}
    }

    /* find leftmost vertex */

    temp = Points[0].X;
    left = 0;

    for (i = 1; i < NumPoints; i++) {
	if (Points[i].X < temp) {
	    temp = Points[i].X;
	    left = i;
	}
    }

    /* find rightmost vertex */

    temp = Points[0].X;
    right = 0;

    for (i = 1; i < NumPoints; i++) {
	if (Points[i].X > temp) {
	    temp = Points[i].X;
	    right = i;
	}
    }

    /* fill in the xlists */

    li = ri = top;		/* left and right index vertices */
    rem = NumPoints;		/* number of vertices remaining */

    nli = li - 1;		/* next left vertex */
    if (nli < 0)
	nli = NumPoints - 1;	/* step down ccw */

    nri = ri + 1;		/* next right vertex */
    if (nri >= NumPoints)
	nri = 0;		/* step down cw */

    ldy = rdy = Points[top].Y;	/* offsets into xlists */

    while (rem > 0) {		/* scan in y, activating new edges */

	if ((ldy <= rdy) && (rem > 0)) {	/* do the next left edge */
	    BresPoints(Points[li].X,
		       Points[li].Y,
		       Points[nli].X,
		       Points[nli].Y,
		       xlist1);
	    rem--;		/* one less edge... */
	    li = nli;
	    nli = nli - 1;	/* next left vertex */
	    if (nli < 0)
		nli = NumPoints - 1;	/* step down ccw */
	    ldy = Points[li].Y;	/* next offset */
	}
	if ((rdy <= ldy) && (rem > 0)) {	/* do the next right edge */
	    BresPoints(Points[ri].X,
		       Points[ri].Y,
		       Points[nri].X,
		       Points[nri].Y,
		       xlist2);
	    rem--;		/* one less edge... */
	    ri = nri;
	    nri = nri + 1;	/* next right vertex */
	    if (nri >= NumPoints)
		nri = 0;	/* step down cw */
	    rdy = Points[ri].Y;	/* next offset */
	}
    }

    y1 = Points[top].Y;
    y2 = Points[bottom].Y;

/* write out the scanlines... */

    for (y = y1; y < y2; y++) {
	if ((y >= MINY) || (y <= MAXY)) {
	   xl1=xlist1[y];
	   xl2=xlist2[y];
	   if (xl2 < xl1) {
		SWAP(xl1,xl2)
		}
	   if ((xl1 <= MAXX) || (xl2 >= MINX)) {
		xl1=max(xl1, MINX);
		xl2=min(xl2, MAXX);
		memset((ptr0 + xl1 + (y*XRES)),color, xl2-xl1);
	   }
	}
    }
}

void bitblt(PCH src, int sx, int sy, PCH dest, int dx, int dy, int x, int y)
{
int i,j,k,l;

if ((x<dx) && (y<dy) && (x+sx>0) && (y+sy>0)) {
  i=l=k=0;

  if (x<0) { l=i=x; } 
  if (y<0) { k=-y; }
  if ((x+sx) > dx) { i=(dx-(x+sx)); }
  if ((y+sy) > dy) { sy=dy-y; }

  for (j=k; j<sy; j++) {
    memcpy((PCH) (dest+x-l+dx*(y+j)),(PCH) (src+sx*j-l),sx+i);
  }
}
}


void maskblt(PCH src, PCH mask, int sx, int sy, PCH dest, int dx, int dy, int x, int y)
{
int g,i,j,k,l,m,n,o,p;

if ((x<dx) && (y<dy) && (x+sx>0) && (y+sy>0)) {
  i=l=k=0;
  if (x<0) { l=i=x; } 
  if (y<0) { k=-y; }
  if ((x+sx) > dx) { i=(dx-(x+sx)); }
  if ((y+sy) > dy) { sy=dy-y; }

  n=(sx*k)-l;
  p=x-l;
  for (j=(k+y); j<(sy+y); j++) {
    o=(j)*dx+p;
    for (g=0; g<(sx+i); g++) {
      m=n+g;
      if (mask[m]!=0) {
        dest[g+o]=src[m];
      }
    }
  n+=sx;
  }
}
 
}


void getimage(PCH ptr0,PCH pbmp,unsigned int x1, unsigned int y1,
		unsigned int x2, unsigned int y2) {
int dx,dy;
int sz,x,y;

dx=(x2-x1);
dy=(y2-y1);

sz=abs(dx*dy);

pbmp=malloc(sz);

memcpy(pbmp,&dx,sizeof(dx));
memcpy(  (pbmp+sizeof(dx)),&dy,sizeof(dy));

for (y=y1; y<=y2; y++) {
   for (x=x1; x<=x2; x++) {
	*(PCH) (pbmp+x+(XRES*y)+8)=*(PCH) (ptr0+x+(XRES*y));
   }
}
}


void ReadPal(SHORT start, SHORT total, PCH DACtable)
{
  INT i;
  start*=3;
  total*=3;

  OUTP8(DAC_READ_INDEX, (BYTE)start);	/* select first DAC register */

  for (i=start;i<total;) {
    DACtable[i++]=INP8(DAC_DATA);	/* read red */
    DACtable[i++]=INP8(DAC_DATA);	/* read green */
    DACtable[i++]=INP8(DAC_DATA);	/* read blue */
  }
}


void WritePal(SHORT start, SHORT total, PCH DACtable)
{
  INT i;
  start*=3;
  total*=3;

  OUTP8(DAC_WRITE_INDEX, (BYTE)start);	/* select first DAC register */

  for (i=start;i<total;) {
    OUTP8(DAC_DATA, DACtable[i++]);	/* write red */
    OUTP8(DAC_DATA, DACtable[i++]);	/* write green */
    OUTP8(DAC_DATA, DACtable[i++]);	/* write blue */
  }
}

void FadeIn(PCH DAC)
{
  SHORT i, j;
  BYTE Fade[768];
  USHORT Steps[768];
  
  memset(Fade, 0, 768);
  for (i=0;i<768;i++)
    Steps[i]=DAC[i];
  
  for (i=0;i<64;i++) {
    for (j=0;j<768;j++)
      Fade[j]=Steps[j]*i/64;
    WAITVSYNC
    WritePal(0, 256, Fade);
  }

  WritePal(0, 256, DAC);
}

void FadeOut(PCH DAC)
{
  SHORT i, j;
  BYTE Fade[768];
  USHORT Steps[768];
  
  memset(Fade, 0, 768);
  for (i=0;i<768;i++)
    Steps[i]=DAC[i];
  
  for (i=0;i<64;i++) {
    for (j=0;j<768;j++)
      Fade[j]=Steps[j]*(63-i)/64;
    WAITVSYNC
    WritePal(0, 256, Fade);
  }
}

void CrossFade(PCH OldDac, PCH NewDac)
{
short i,j;
BYTE Fade[768];
SHORT Steps[768];
int a,b,c,d;

for (i=0; i<768; i++) {
Steps[i]=NewDac[i]-OldDac[i];
}

for (i=0; i<64; i++) {
   for (j=0; j<768; j++) {
	Fade[j]=OldDac[j] + (Steps[j]*i)/64;
	}
   WAITVSYNC
   WritePal(0, 256, Fade);
}
}


void RotatePal(PCH Dac, USHORT start, USHORT end, USHORT inc) 
{

BYTE Pal[768];
USHORT i,i3,inew;

memcpy(Pal, Dac, 768);

for (i=start; i<=end; i++) {

	inew=(start + (((i+inc)) % (end-start+1)))*3;
	i3=i*3;
	
	Dac[i3    ]=Pal[inew    ];
	Dac[i3 + 1]=Pal[inew + 1];
	Dac[i3 + 2]=Pal[inew + 2];
	}
WAITVSYNC
WritePal(0,256, Dac);
}

void HSItoRGB(float h, float s, float i, BYTE *r, BYTE *g, BYTE *b)
{
float rv, gv, bv;
float PI,t;

PI=3.1415926;
t=2*PI*h;
rv=1 + s*sin(t - 2*PI/3);
gv=1 + s*sin(t);
bv=1 + s*sin(t + 2*PI/3);
 
t=63.9999999*i/2;

*r=rv*t;
*g=gv*t;
*b=bv*t;

}



void adjust(int *base, int xres, int xa, int ya, int x, int y, int xb, int yb)
{

int d;
long int v;

if (base[x + xres*y]==0) {
   d=abs(xa-xb)+abs(ya-yb);
v=(base[xa + xres*ya]+base[xb + xres*yb])/2 + ((rand()%100)-50)*d*F*FDiv/1024;
   if (v<FDiv) v=FDiv;
   if (v>(192*FDiv)) v=(192*FDiv);
   base[x + xres*y]=v;
}

} /* end of adjust */




void subdivide(int *base, int xres, int x1, int y1, int x2, int y2)
{
int x,y;
long int v;
if (((x2-x1)<2) && ((y2-y1)<2)) { return; }

{
x=(x1+x2)/2;
y=(y1+y2)/2;

adjust(base,xres,x1,y1,x,y1,x2,y1);
adjust(base,xres,x2,y1,x2,y,x2,y2);
adjust(base,xres,x1,y2,x,y2,x2,y2);
adjust(base,xres,x1,y1,x1,y,x1,y2);

if (base[x + xres*y]==0) {
        v=(base[x1 + xres*y1] + base[x2 + xres*y1] +
           base[x2 + xres*y2] + base[x1 + xres*y2]   )/4;
        base[x + xres*y]=v;
        }

subdivide(base,xres,x1,y1,x,y);
subdivide(base,xres,x,y1,x2,y);
subdivide(base,xres,x,y,x2,y2);
subdivide(base,xres,x1,y,x,y2);

}
}






