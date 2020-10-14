#ifndef _fft_h
#define _fft_h
#include <stdio.h>
#include <stdlib.h>
#include "ccomplex.h"

#define EPSILON (1e-10)
#define CANT_PARAM (1+2)
#define POS_FNAME_IN 1
#define POS_CANT_SAMPLES 2

#define ERROR_PARAM -1
#define ERROR_FOPEN -2
#define ERROR_PARSE_DATA -3
#define ERROR_MALLOC -4
#define ERROR_2POWER -5
#define ERROR_CANT_FILEIN -6;
#define OK 0

//segunda edicon

int fft(int cant_samples,Ccomplex* fft_array);

int getTwiddles(Ccomplex* & twiddle,int cant);

int pow2(int i);

int bitReverse(int n,int gamma);

void sortFFTArray(Ccomplex* fft_array, int cant_samples,int gamma);

typedef char* string_t;

#endif
