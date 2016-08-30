/* text.c - text routines for graphics mode ... */


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

#include <os2.h>

extern unsigned char alphabet[128][8][8];

void putstring(ptr0,locx,locy,temp,color)
PCH ptr0;
int locx;
int locy;
char temp[];
char color;
{
	register int x;
	register int y;
	int i;
	int letter;

	i = 0;

	if (locx < 0)
	i=(abs(locx)/8);
	if ((locy > 0) && (locy < 200)) {
	while((temp[i] != 0) && ((locx+8)<320)) {
		letter = temp[i++] - ' ';
		for(y=0; y<8; y++) {
			for(x=7; x>=0; x--) {
				if(alphabet[letter][y][x]) {
					ptr0[locx+x+320*(locy+y)]=color;
				}
				else {
					ptr0[locx+x+320*(locy+y)]=0;
				}
			}
		}
		locx += 8;
	}
} /* end of if */

}


/* Font for displaying characters on the screen */
unsigned char alphabet[128][8][8] =

/*		*/	{

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 }		},

/*	!	*/	
		{	{ 0,0,0,1,1,0,0,0 },
			{ 0,0,0,1,1,0,0,0 },
			{ 0,0,0,1,1,0,0,0 },
			{ 0,0,0,1,1,0,0,0 },
			{ 0,0,0,1,1,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,1,1,0,0,0 },
			{ 0,0,0,1,1,0,0,0 }		},
/*	"	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,1,1,0,0,0 },
			{ 0,0,0,1,1,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 }		},
/*	#	*/

		{	{ 0,0,1,0,0,1,0,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 1,1,1,1,1,1,1,1 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 1,1,1,1,1,1,1,1 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,0,1,0,0,1,0,0 }		},
/*	$	*/
		{	{ 0,0,0,1,1,0,0,0 },
			{ 0,0,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,0,1,1,1,0,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,1,1,1,0,0 },
			{ 0,0,0,1,1,0,0,0 }		},

/*	%	*/

		{	{ 1,1,0,0,0,0,0,1 },
			{ 1,1,0,0,0,0,1,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,1,0,0,0,0,1,1 },
			{ 1,0,0,0,0,0,1,1 }		},
/*	&	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 }		},
/*	`	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 }		},
/*	(	*/

		{	{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,0,1,0,0,0 }		},
/*	)	*/

		{	{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 }		},
/*	*	*/

		{	{ 1,0,0,0,0,0,0,1 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,1,1,1,0,0 },
			{ 0,0,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,0,0 },
			{ 0,0,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 1,0,0,0,0,0,0,1 }		},
/*	+	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,1,1,1,1,1,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 }		},
/* 0,0 */

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 }		},
/*	-	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 1,1,1,1,1,1,1,1 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 }		},
/*	.	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 }		},
/*	/	*/

		{	{ 0,0,0,0,0,0,0,1 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 1,0,0,0,0,0,0,0 }		},
/*	0	*/

		{	{ 0,0,0,1,1,0,0,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,1,0,0,1,0,1,0 },
			{ 1,0,0,1,0,0,0,1 },
			{ 1,0,1,0,0,0,0,1 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,0,0,1,1,0,0,0 }		},
/*	1	*/

		{	{ 0,0,0,1,1,0,0,0 },
			{ 0,0,1,0,1,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,1,1,1,1,1,0 }		},
/*	2	*/

		{	{ 0,0,1,1,1,0,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,1,1,1,1,1,0 }		},
/*	3	*/

		{	{ 0,0,1,1,1,0,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 1,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,1,1,1,0,0 },
			{ 1,0,0,0,0,1,1,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,0,1,1,1,0,0,0 }		},
/*	4	*/

		{	{ 0,0,0,1,1,0,0,0 },
			{ 0,0,1,0,1,0,0,0 },
			{ 0,1,0,0,1,0,0,0 },
			{ 1,0,0,0,1,0,0,0 },
			{ 1,1,1,1,1,1,1,1 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,1,0,0,0 }		},
/*	5	*/

		{	{ 0,1,1,1,1,1,1,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,1,1,1,0,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,1,1,1,1,1,0,0 }		},
/*	6	*/

		{	{ 0,0,0,1,1,1,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,1,1,1,0,0 }		},
/*	7	*/

		{	{ 0,1,1,1,1,1,1,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 }		},
/*	8	*/

		{	{ 0,0,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,1,1,1,0,0 }		},
/*	9	*/

		{	{ 0,0,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,1,1,1,1,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,1,1,0,0,0,0,0 }		},
/*	:	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 }		},

/*	;	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 }		},
/*	<	*/

		{	{ 0,0,0,1,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 1,0,0,0,0,0,0,0 },
			{ 1,0,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 }		},
/*	=	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,1,1,1,1,1,1,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,1,1,1,1,1,1,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 }		},
/*	>	*/

		{	{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,0,0,1 },
			{ 0,0,0,0,0,0,0,1 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,1,0,0,0 }		},
/*	?	*/

		{	{ 0,0,0,1,1,0,0,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,1,0,0,0 }		},
/*	@	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 }		},

/*	A	*/

		{	{ 0,0,0,1,1,0,0,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,1,1,1,1,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 }		},

/*	B	*/

		{	{ 0,1,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,1,1,1,1,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,1,1,1,1,0,0 }		},

/*	C	*/
		{	{ 0,0,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,1,1,1,0,0 }		},
/*	D	*/

		{	{ 0,1,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,1,1,1,1,0,0 }		},
/*	E	*/

		{	{ 0,1,1,1,1,1,1,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,1,1,1,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,1,1,1,1,1,0 }		},
/*	F	*/

		{	{ 0,1,1,1,1,1,1,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,1,1,1,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 }		},
/*	G	*/

		{	{ 0,0,0,1,1,0,0,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,0,0,1,1,0 },
			{ 0,0,0,1,1,0,1,0 }		},
/*	H	*/

		{	{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,1,1,1,1,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 }		},
/*	I	*/

		{	{ 0,0,1,1,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,1,1,1,0,0,0 }		},
/*	J	*/

		{	{ 0,0,0,0,1,1,1,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,0,1,1,1,0,0,0 }		},
/*	K	*/

		{	{ 0,1,0,0,0,1,0,0 },
			{ 0,1,0,0,1,0,0,0 },
			{ 0,1,0,1,0,0,0,0 },
			{ 0,1,1,0,0,0,0,0 },
			{ 0,1,1,1,0,0,0,0 },
			{ 0,1,0,0,1,0,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,1,0,0,0,0,1,0 }		},
/*	L	*/

		{	{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,1,1,1,1,1,0 }		},
/*	M	*/

		{	{ 0,1,0,0,0,0,1,0 },
			{ 0,1,1,0,0,1,1,0 },
			{ 0,1,0,1,1,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 }		},
/*	N	*/

		{	{ 0,1,0,0,0,0,1,0 },
			{ 0,1,1,0,0,0,1,0 },
			{ 0,1,1,0,0,0,1,0 },
			{ 0,1,0,1,0,0,1,0 },
			{ 0,1,0,0,1,0,1,0 },
			{ 0,1,0,0,0,1,1,0 },
			{ 0,1,0,0,0,1,1,0 },
			{ 0,1,0,0,0,0,1,0 }		},
/*	O	*/
		{	{ 0,0,0,1,1,0,0,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 1,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,1 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,0,0,1,1,0,0,0 }		},
/*	P	*/

		{	{ 0,1,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 }		},

/*	Q	*/
		{	{ 0,0,0,1,1,0,0,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 1,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,1 },
			{ 0,1,0,0,1,0,1,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,0,0,1,1,0,1,1 }		},

/*	R	*/
		{	{ 0,1,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,1,1,1,1,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 }		},

/*	S	*/

		{	{ 0,0,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,0,1,1,1,1,0,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,1,1,1,0,0 }		},


/*	T	*/

		{	{ 1,1,1,1,1,1,1,0 },
			{ 1,0,0,1,0,0,1,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,1,1,1,0,0,0 }		},
/*	U	*/

		{	{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,1,1,1,0,0 }		},
/*	V	*/

		{	{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,0,0,1,1,0,0,0 }		},
/*	W	*/

		{	{ 0,1,0,0,0,0,0,1 },
			{ 0,1,0,0,0,0,0,1 },
			{ 0,1,0,0,0,0,0,1 },
			{ 0,1,0,0,0,0,0,1 },
			{ 0,1,0,0,0,0,0,1 },
			{ 0,1,0,0,1,0,0,1 },
			{ 0,1,0,1,0,1,0,1 },
			{ 0,0,1,0,0,0,1,0 }		},
/*	X	*/

		{	{ 1,0,0,0,0,0,0,1 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,0,0,1,1,0,0,0 },
			{ 0,0,0,1,1,0,0,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 1,0,0,0,0,0,0,1 }		},
/*	Y	*/

		{	{ 1,0,0,0,0,0,1,0 },
			{ 1,0,0,0,0,0,1,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,0,1,0,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 }		},
/*	Z	*/

		{	{ 1,1,1,1,1,1,1,0 },
			{ 1,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 1,1,1,1,1,1,1,0 }		},
/*	[	*/

		{	{ 1,1,1,1,0,0,0,0 },
			{ 1,0,0,0,0,0,0,0 },
			{ 1,0,0,0,0,0,0,0 },
			{ 1,0,0,0,0,0,0,0 },
			{ 1,0,0,0,0,0,0,0 },
			{ 1,0,0,0,0,0,0,0 },
			{ 1,0,0,0,0,0,0,0 },
			{ 1,1,1,1,0,0,0,0 }		},
/*	\	*/

		{	{ 1,0,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,0,0,1 }		},
/*	]	*/

		{	{ 0,0,0,1,1,1,1,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,0,0,1,1,1,1,0 }		},
/*	^	*/

		{	{ 0,0,0,1,0,0,0,0 },
			{ 0,0,1,0,1,0,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 1,0,0,0,0,0,1,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 }		},
/*	_	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 1,1,1,1,1,1,1,1 }		},
/*	`	*/

		{	{ 0,0,1,0,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 }		},
/*	a	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,1,1,1,1,0,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,0,0,1,0 },
			{ 0,1,1,1,1,1,1,0 },
			{ 1,0,0,0,0,0,1,0 },
			{ 1,0,0,0,0,1,1,0 },
			{ 0,1,1,1,1,0,1,0 }		},
/*	b	*/

		{	{ 1,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,1,0,0,0,1,0 },
			{ 1,1,0,1,1,1,0,0 }		},
/*	c	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,1,1,1,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 1,0,0,0,0,0,0,0 },
			{ 1,0,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,0,1,1,1,1,0,0 }		},
/*	d	*/

		{	{ 0,0,0,0,0,1,1,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,1,1,1,1,1,0,0 },
			{ 1,0,0,0,0,1,0,0 },
			{ 1,0,0,0,1,1,0,0 },
			{ 0,1,1,1,0,1,1,0 }		},
/*	e	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,1,1,1,0,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 1,1,1,1,1,1,1,0 },
			{ 1,0,0,0,0,0,0,0 },
			{ 1,0,0,0,0,0,1,0 },
			{ 0,1,1,1,1,1,0,0 }		},
/*	f	*/

		{	{ 0,0,0,1,1,0,0,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 1,1,1,1,1,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,1,1,1,0,0,0,0 }		},
/*	g	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,1,1,1,0,0,0 },
			{ 0,1,0,0,0,1,1,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,0,1,1,1,1,0,0 },
			{ 0,0,0,0,0,1,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,0,1,1,1,0,0,0 }		},
/*	h	*/

		{	{ 1,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,1,1,0,0,0 },
			{ 0,1,1,0,0,1,0,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 0,1,0,0,0,0,1,0 },
			{ 1,1,0,0,0,0,1,0 }		},
/*	i	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,1,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,1,1,1,0,0,0 }		},
/*	j	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,1,1,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 1,0,0,0,1,0,0,0 },
			{ 0,1,1,1,0,0,0,0 }		},
/*	k	*/

		{	{ 1,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,1,0,0,0,0 },
			{ 0,1,1,0,0,0,0,0 },
			{ 0,1,1,0,0,0,0,0 },
			{ 0,1,0,1,0,0,0,0 },
			{ 1,1,0,0,1,0,0,0 }		},
/*	l	*/

		{	{ 1,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 1,1,1,0,0,0,0,0 }		},
/*	m	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 1,0,1,0,0,1,0,0 },
			{ 1,1,0,1,1,0,1,0 },
			{ 1,0,0,1,0,0,1,0 },
			{ 1,0,0,1,0,0,1,0 },
			{ 1,0,0,1,0,0,1,0 }		},
/*	n	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 1,0,1,1,0,0,0,0 },
			{ 0,1,0,0,1,0,0,0 },
			{ 0,1,0,0,1,0,0,0 },
			{ 0,1,0,0,1,0,0,0 },
			{ 0,1,0,0,1,0,0,0 }		},
/*	o	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,1,1,1,0,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 1,0,0,0,0,0,1,0 },
			{ 1,0,0,0,0,0,1,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,0,1,1,1,0,0,0 }		},
/*	p	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 1,0,1,1,1,0,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,1,1,1,1,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 1,1,1,0,0,0,0,0 }		},
/*	q	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,1,1,1,0,1,0,0 },
			{ 1,0,0,0,1,0,0,0 },
			{ 1,0,0,0,1,0,0,0 },
			{ 0,1,1,1,1,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,1,1,1,0,0 }		},
/*	r	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 1,1,0,1,1,0,0,0 },
			{ 0,1,1,0,0,1,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 0,1,0,0,0,0,0,0 },
			{ 1,1,1,0,0,0,0,0 }		},
/*	s	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,1,1,1,0,0,0,0 },
			{ 1,0,0,0,1,0,0,0 },
			{ 1,0,0,0,0,0,0,0 },
			{ 0,1,1,1,0,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 1,0,0,0,1,0,0,0 },
			{ 0,1,1,1,0,0,0,0 }		},

/*	t	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 1,1,1,1,1,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,0,1,0,0,1,0,0 },
			{ 0,0,0,1,1,0,0,0 }		},
/*	u	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 1,0,0,0,0,1,0,0 },
			{ 1,0,0,0,0,1,0,0 },
			{ 1,0,0,0,0,1,0,0 },
			{ 1,0,0,0,1,1,0,0 },
			{ 0,1,1,1,0,1,1,0 }		},
/*	v	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 1,0,0,0,0,0,1,0 },
			{ 1,0,0,0,0,0,1,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 0,0,1,0,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 }		},
/*	w	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 1,0,0,0,0,0,1,0 },
			{ 1,0,0,0,0,0,1,0 },
			{ 1,0,0,1,0,0,1,0 },
			{ 1,0,0,1,0,0,1,0 },
			{ 0,1,1,0,1,1,0,0 }		},
/*	x	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 1,0,0,0,1,0,0,0 },
			{ 0,1,0,1,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,1,0,1,0,0,0,0 },
			{ 1,0,0,0,1,0,0,0 }		},
/*	y	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 1,0,0,0,1,0,0,0 },
			{ 1,0,0,0,1,0,0,0 },
			{ 0,1,1,1,1,0,0,0 },
			{ 0,0,0,0,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,1,1,0,0,0,0,0 }		},
/*	z	*/

		{	{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 1,1,1,1,1,1,0,0 },
			{ 1,0,0,0,1,0,0,0 },
			{ 0,0,0,1,0,0,0,0 },
			{ 0,0,1,0,0,0,0,0 },
			{ 0,1,0,0,0,1,0,0 },
			{ 1,1,1,1,1,1,0,0 }		}	};

