/* inline.h - Contains macro versions of frequently called
	      functions, so that speed critical coders can have
	      a call-less version of the functions... */


#define MASKBLT(src, mask, sx, sy, dest, dx, dy, x, y)  \
{							\
int g,i,j,k,l,m,n,o,p,sy2;				\
							\
if ((x<dx) && (y<dy) && (x+sx>0) && (y+sy>0)) { 	\
  i=l=k=0;						\		
  sy2=sy;						\
  if (x<0) { l=i=x; } 					\
  if (y<0) { k=-y; }					\
  if ((x+sx) > dx) { i=(dx-(x+sx)); }			\
  if ((y+sy) > dy) { sy2=dy-y; }			\
							\
  n=(sx*k)-l;						\
  p=x-l;						\
  for (j=(k+y); j<(sy2+y); j++) {			\
    o=(j)*dx+p;						\
    for (g=0; g<(sx+i); g++) {				\
      m=n+g;						\
      if (mask[m]!=0) {					\
        dest[g+o]=src[m];				\
      }    \
    }      \
  n+=sx;   \
  }        \
}          \
}          \


#define MASKBLT2(src, sx, sy, dest, dx, dy, x, y)  \ 
{							\ 
int g,i,j,k,l,m,n,o,p,sy2;				\
							\
if ((x<dx) && (y<dy) && (x+sx>0) && (y+sy>0)) { 	\
  i=l=k=0;						\		
  sy2=sy;						\
  if (x<0) { l=i=x; } 					\
  if (y<0) { k=-y; }					\
  if ((x+sx) > dx) { i=(dx-(x+sx)); }			\
  if ((y+sy) > dy) { sy2=dy-y; }			\
							\
  n=(sx*k)-l;						\
  p=x-l;						\
  for (j=(k+y); j<(sy2+y); j++) {			\
    o=(j)*dx+p;						\
    for (g=0; g<(sx+i); g++) {				\
      m=n+g;						\
      if (src[m]!=0) {					\
        dest[g+o]=src[m];				\
      }    \
    }      \
  n+=sx;   \
  }        \
}          \
}          \


#define ROTATE3D(Rot,x,y,z,x2,y2,z2) {    		\ 
x2=(x*(Rot.rx1) + y*(Rot.rx2) + z*(Rot.rx3))>>12; 	\
y2=(x*(Rot.ry1) + y*(Rot.ry2) + z*(Rot.ry3))>>12;	\
z2=(x*(Rot.rz1) + y*(Rot.rz2) + z*(Rot.rz3))>>12;	\
} \ 


