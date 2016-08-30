/* 
 * vgalib.h  - reconstructed 3/19/93 
 *             Lost 3/10/93 due to catastrophic scsi error...
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

#define INCL_DOS
#define INCL_SUB
#include <os2.h>

#define HANDLE 0
#define WAIT 1
#define BUFSIZE 12
#define XRES 320
#define YRES 200
#define MAXY 199
#define MAXX 319
#define MINY 0
#define MINX 0
#define SWAP(a,b) {a^=b; b^a; a^=b; }
#define ABS(a) (((a)<0) ? -(a) : (a))
#define SGN(a) (((a)<0) ? -1 : 1)
#define SQR(a) ((a)*(a))
#define FDIV 4096

typedef struct {
	SHORT X, Y, Z;
} iPoint;

typedef struct {
	BYTE Org, Dest, Color;
} Line;

#define WAITVSYNC { while(INP8(0x03da)&8); while(!(INP8(0x03da)&8)); }
extern _Far16 _Pascal OUTP8(USHORT, UCHAR);
extern _Far16 _Pascal OUTP16(USHORT, USHORT);
extern UCHAR _Far16 _Pascal INP8(USHORT);
extern USHORT _Far16 _Pascal INP16(USHORT);


int Initgraph(PCH *);
void cls(PCH, char);
void putpixel(PCH, unsigned int, unsigned int, char);
char getpixel(PCH, unsigned int, unsigned int);
void line(PCH, unsigned int, unsigned int, unsigned int, unsigned int, char);
void box(PCH, unsigned int, unsigned int, unsigned int, unsigned int, char);
void circlepoints(PCH, int, int, unsigned int, unsigned int, char);
void circle(PCH, unsigned int, unsigned int, unsigned int, char);
void rectangle(PCH, USHORT, USHORT, USHORT, USHORT, BYTE);
void scanline(PCH, SHORT, SHORT, SHORT, BYTE);
void BresPoints(SHORT, SHORT, SHORT, SHORT, SHORT);
void PolygonSimple(PCH, iPoint *, BYTE, BYTE);
void bitblt(PCH, int, int, PCH, int, int, int, int);
void maskblt(PCH, PCH, int, int, PCH, int, int, int, int); 
void getimage(PCH, PCH, unsigned int, unsigned int, unsigned int, unsigned int);
void ReadPal(SHORT, SHORT, PCH);
void WritePal(SHORT, SHORT, PCH);
void FadeIn(PCH);
void FadeOut(PCH);
void CrossFade(PCH, PCH);
void RotatePal(PCH, USHORT, USHORT, USHORT);
void HSItoRGB(float, float, float, BYTE *, BYTE *, BYTE *);
void adjust(int *, int, int, int, int, int, int, int);
void subdivide(int *, int, int, int, int, int);

void putstring(PCH, int, int, char *, char);


