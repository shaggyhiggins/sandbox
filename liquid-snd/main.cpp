#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include "liquid.h"
#include "sndfile.hh"



#define		BUFFER_LEN		128000

// static void create_file (const char * fname, int format)
// {	static short buffer [BUFFER_LEN] ;

// 	SndfileHandle file ;
// 	int channels = 2 ;
// 	int srate = 48000 ;

// 	printf ("Creating file named '%s'\n", fname) ;

// 	file = SndfileHandle (fname, SFM_WRITE, format, channels, srate) ;

// 	memset (buffer, 0, sizeof (buffer)) ;

// 	file.write (buffer, BUFFER_LEN) ;

// 	puts ("") ;
// 	/*
// 	**	The SndfileHandle object will automatically close the file and
// 	**	release all allocated memory when the object goes out of scope.
// 	**	This is the Resource Acquisition Is Initailization idom.
// 	**	See : http://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization
// 	*/
// } /* create_file */



static void read_file (const char * fname)
{	
    static float buffer [BUFFER_LEN] ;

	SndfileHandle file ;

	file = SndfileHandle (fname) ;

	printf ("Opened file '%s'\n", fname) ;
	printf ("    Sample rate : %d\n", file.samplerate ()) ;
	printf ("    Channels    : %d\n", file.channels ()) ;
	printf ("    Frames      : %d\n", file.frames ()) ;

	printf ("    Origninal File Name    : %s\n", file.getString(SF_STR_TITLE)) ;
	printf ("    Created by             : %s\n", file.getString(SF_STR_SOFTWARE)) ;
	printf ("    Source Device          : %s\n", file.getString(SF_STR_ARTIST)) ;
	printf ("    Metadata               : %s\n", file.getString(SF_STR_COMMENT)) ;
	printf ("    Date/Time Recorded UTC : %s\n", file.getString(SF_STR_DATE)) ;
	printf ("    Device Info            : %s\n", file.getString(SF_STR_ALBUM)) ;

	for (int i = 0; i < file.frames(); i+=BUFFER_LEN)
	{
		file.readf(buffer, BUFFER_LEN);
		float sum_sq  = 0.0F;
		float sum = 0.0F;
		int s;

		// scale to volts
		for (s = 0; s < BUFFER_LEN; ++s)
		{
			buffer[s] *= 3.0;
			sum += buffer[s];
		}
		
		float mean = sum / s;
		
		// remove mean (DC offset) as we go
		for (s = 0; s < BUFFER_LEN; ++s)
		{
			buffer[s] -= mean;
			sum_sq += buffer[s]*buffer[s];
		}
		float rms = sqrt(sum_sq/s);
		
		float rms_db = 20 * log10(rms) - (-169.0);

		printf("%f, %f\n", rms, rms_db);
	}


	puts ("") ;

	/* RAII takes care of destroying SndfileHandle object. */
} /* read_file */



int main (void)
{	
    const char * fname = "C:\\Users\\Mark\\testdata\\SBW1239_20161007_130600.wav" ;

	puts ("\nSimple example showing usage of the C++ SndfileHandle object.\n") ;

	//create_file (fname, SF_FORMAT_WAV | SF_FORMAT_PCM_16) ;

	read_file (fname) ;

	puts ("Done.\n") ;
	return 0 ;
} /* main */
