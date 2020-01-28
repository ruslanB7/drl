/*
 ============================================================================
 Name        : hwl.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <math.h>

const double PI25DT = 3.141592653589793238462643;

#include <stdio.h>
#include <stdlib.h>


#include <string.h>
#include <errno.h>


int ret, bufa;


//#include <X11/X.h>

void  numtostr (int in, char* out);
//char [];


int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	//////////////////////////////////////////////////////////////////////////



	int cr, di, stri; 
	FILE *file, *fld;
	file = fopen("drl.txt", "rb");
  	fld = fopen("out.nc","wb");

	fprintf (fld,"%s\r\n", "G90");
	fprintf (fld,"%s\r\n", "G21");
  	fprintf (fld,"%s\r\n", "S1000");
  	fprintf (fld,"%s\r\n", "F100");
  	fprintf (fld,"%s\r\n", "M03");
	fprintf (fld, "%s\r\n", "G00 Z2.000 " );
    di=0;
	stri=0;
	while (1)
	{
		cr = fgetc (file);
		if ( feof(file) )
		{
			break;
		}
		else 
		{ 
			if ( (cr >= '0') && (cr <='9') )
			{
				if ( di == 4 )
				{
					fputc ('.', fld);
					stri=1;
				}
				di++;
			}
			else
			{
				di=0;
			}
			fputc (cr, fld);
			if ( cr == '\n')
			{
				if ( stri == 1 )
				{
					fprintf (fld, "%s\r\n", "G00 Z0.000 " );
					fprintf (fld, "%s\r\n", "G01 Z-2.000 " );
					fprintf (fld, "%s\r\n", "G00 Z2.000 " );
					stri = 0;
				}
			} 
		}
	}

	fclose(file);
    	fclose(fld);
	printf ("%s\n","Window done");

	//////////////////////////////////////////////////////////////////////////
	return EXIT_SUCCESS;
}

void  numtostr (int in, char* out)
{

	int i,tmb, input, tmq, tmw;

	if (in < 0)
	{
		out[0]='-';
	}
	else
	{
		out[0]=' ';
	}
	input=abs(in);
	//tmb=in;
	//printf ("in==%i\n",input);

	for (i=1; i<6; i++)
	{

		tmb=0;

		tmq=1;
		tmw=(5-i);
		while ( tmw )
		{
			tmq*=10;
			tmw--;
		}

		//printf ("ion=%i\n",tmq);
		while (input >= tmq)
		{
			input -= tmq;
			tmb++;
			//printf ("innn=%i\t%i\n",input,tmq );
		}

	out[i]=tmb+0x30;//
	}
	//out[5]=0x32+input;
	out[6]=0x00;
	//out[5]=0x30;
	//out[4]=0x30;
	//out[3]=0x30;
	//out[2]=0x30;
	//out[1]=0x30;



}
