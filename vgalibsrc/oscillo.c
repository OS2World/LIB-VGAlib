/* oscillo.c - Oscilloscope 1.0 for OS/2 2.0
 * REQUIRES SBOS2 device driver by Michael Fullbright!!!
 * By John E. Stone
 * 10/18/92
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

#define TRACECOLOR       15  
#define GRIDCOLOR        1
#define CLIPCOLOR        14
#define CENTERLINECOLOR  2
#define CLIPTIME         20


#define INCL_BASE
#include <os2.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "vgalib.h"
#include "\work\vgalib\sblast_user.h"

#define HANDLE 0
#define WAIT 1

main()
{
	HFILE inhandle, audiohandle;
	ULONG action, buffersize, overflow, status, speed;
	ULONG numread, datlen, parlen;
	ULONG maxreadsize,numtoread;

	char ptr1[65536];
	struct _VIOPHYSBUF phys;
	struct _VIOMODEINFO orig,moda;
	char status1;
	unsigned rc;
	PCH ptr0;
	char color;
	unsigned int x2,x,y;
	unsigned char buf[10*1024];
	unsigned int density;
	unsigned int cliplight;
	
speed=0;


printf("Oscilloscope V1.0 \n");
printf("By John Stone\n10/21/92\n");
printf("\n\n\nEnter Sample Rate: ");
fflush(stdout);
scanf("%u",&speed);

printf("\nEnter point density (1, 2 or 4): ");
fflush(stdout);
scanf("%u",&density);


if ((density!=1) && (density!=2) && (density!=4)) {
density=1;
}

/* Open SBDSP$ for reading... */
status=DosOpen("SBDSP$",&audiohandle,&action,0,
	FILE_NORMAL, FILE_OPEN, 
	OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE | OPEN_FLAGS_WRITE_THROUGH,
	NULL);

if (status!=0) { DosClose(audiohandle); exit(1); }

printf("setting speed to: %u\n",speed);

datlen=2;
parlen=0;
status=DosDevIOCtl(audiohandle, DSP_CAT, DSP_IOCTL_SPEED,
	NULL, 0, &parlen, &speed, 2, &datlen);
printf("status after setting speed etc: %u\n",status);
if (status!=0) { DosClose(audiohandle); exit(1); }

datlen=2;
parlen=0;
overflow=0;
status=DosDevIOCtl(audiohandle, DSP_CAT, DSP_IOCTL_OVERRUN_ERRNO,
	NULL, 0, &parlen, &overflow, datlen, &datlen);
printf("status after turning off overflow errors: %u \n",status);
if (status!=0) { DosClose(audiohandle); exit(1); }

datlen=2;
parlen=0;
buffersize=44330;
buffersize=buffersize*density;
status=DosDevIOCtl(audiohandle, DSP_CAT, DSP_IOCTL_BUFSIZE, 
	NULL, 0, &parlen, &buffersize, datlen, &datlen);
printf("status after setting buffersize to 512: %u\n",status);
if (status!=0) { DosClose(audiohandle); exit(1); }


DosSleep(2000L);

Initgraph(&ptr0);

cls(ptr1,0);

VioScrUnLock(HANDLE);

color=0;
numtoread=320*density;

/* Draw Oscilloscope grid mask */
for(y=15; y<129; y+=16) {
line(ptr1,0,y,319,y,GRIDCOLOR);
}
for (x=0; x<320; x+=16) {
line(ptr1,x,0,x,127,GRIDCOLOR);
}
for (y=0; y<128; y+=2) {
line(ptr1,0,y,319,y,0);
}
for (x=1; x<319; x+=2) {
line(ptr1,x,0,x,127,0);
}

/* Draw Oscilloscope centerline */
line(ptr1,0,63,319,63,CENTERLINECOLOR);


/* draw box around clip light */
line(ptr1,78,138,102,138,15);
line(ptr1,78,160,102,160,15);
line(ptr1,78,138,78,160,15);
line(ptr1,102,138,102,160,15);

/* Copy buffer page to actual screen */
memcpy(ptr0,ptr1,64000);

/* Select proper main loop depending upon which options are
 * active, each loop is optimized separately for what it is
 * attempting to do, this way we get the best performance.
 * Clip light is only useful in density 2 or 4, since it would
 * slow down density 1 far too much.
 *
 * Triggered Sweep will be added later, along with some sort of user 
 * interface so that sampling rate can be changed while it is running.
 * It would be nice to have the program auto-detect the highest sampling
 * rate it can run at, by getting an error back from the soundblaster driver
 * when there is a DMA overrun error or such, this way, if overruns are
 * occurring, the Oscilloscope could back off the sampling rate until 
 * it can keep up, thus giving optimal performance regardless of what
 * machine it is running on.
 */

if (density==1) {
/* main loop for density 1 */
while (!kbhit()) {
status=DosRead(audiohandle, &buf, numtoread, &numread);
if (status!=0) {
	DosClose(audiohandle);
	VioScrUnLock(HANDLE);
	exit(1);
	}
VioScrLock(WAIT,&status1,HANDLE);
memcpy(ptr0,ptr1,41280);
for (x=0; x<numread; x++) {
*(PCH) (ptr0+(320*(buf[x]>>1))+x)=TRACECOLOR;
}
VioScrUnLock(HANDLE);
}
} /* end of density 1 */

else if (density==2) {   
/* density of 2 */
while (!kbhit()) {
status=DosRead(audiohandle, &buf, numtoread, &numread);
if (status!=0) {
	DosClose(audiohandle);
	VioScrUnLock(HANDLE);
	exit(1);
	}
VioScrLock(WAIT,&status1,HANDLE);
memcpy(ptr0,ptr1,41280);
for (x=0; x<numread; x++) {
*(PCH) (ptr0+(320*(buf[x]>>1))+(x>>1))=TRACECOLOR;

if ((buf[x]==0) || (buf[x]==255)) {
   cliplight=CLIPTIME;
}
}

if (cliplight!=0) {
	if (cliplight==CLIPTIME) {
	   box(ptr0,80,140,100,158,CLIPCOLOR);
	}

	cliplight--;
	
	if (cliplight==1) { 
	   cliplight=0;
	   box(ptr0,80,140,100,158,0); 
	}
}
VioScrUnLock(HANDLE);
}
} /* end of density 2 */

else  {   
/* density of 4 */
while (!kbhit()) {
status=DosRead(audiohandle, &buf, numtoread, &numread);
if (status!=0) {
	DosClose(audiohandle);
	VioScrUnLock(HANDLE);
	exit(1);
	}
VioScrLock(WAIT,&status1,HANDLE);
memcpy(ptr0,ptr1,41280);
for (x=0; x<numread; x++) {
*(PCH) (ptr0+(320*(buf[x]>>1))+(x>>2))=TRACECOLOR;

if ((buf[x]==0) || (buf[x]==255)) {
   cliplight=CLIPTIME;
}
}

if (cliplight!=0) {
	if (cliplight==CLIPTIME) {
	   box(ptr0,80,140,100,158,CLIPCOLOR);
	}

	cliplight--;
	
	if (cliplight==1) { 
	   cliplight=0;
	   box(ptr0,80,140,100,158,0); 
	}
}

VioScrUnLock(HANDLE);
}
} /* end of density 4 */


datlen=2;
parlen=0;
buffersize=64000;
buffersize=buffersize*density;
status=DosDevIOCtl(audiohandle, DSP_CAT, DSP_IOCTL_BUFSIZE, 
	NULL, 0, &parlen, &buffersize, datlen, &datlen);
printf("status after setting buffersize to 512: %u\n",status);
if (status!=0) { DosClose(audiohandle); exit(1); }

status=DosClose(audiohandle);
VioSetMode(&orig,HANDLE);
VioScrUnLock(HANDLE);
exit(0);
}

