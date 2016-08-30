#define INCL_BASE
#include <os2.h>
#include <stdio.h>
#include <math.h>
#include "vgalib.h"

#define SWP(_a_,_b_,_c_) { _c_=_a_; _a_=_b_; _b_=_c_; }
#define min(_a_,_b_) ((_a_ < _b_) ? _a_ : _b_)
#define max(_a_,_b_) ((_a_ > _b_) ? _a_ : _b_)

struct edge {
	int ymin, ymax, xi, si;
	int r, inc, dec;
};

void EdgeSetup(struct edge *e, int x0, int y0, int x1, int y1)
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

void triangle(PCH ptr0, int x0, int y0, int x1, int y1, int x2, int y2, char color) {
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


