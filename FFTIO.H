#ifndef _fftio_h
#define _fftio_h
#include "fft.h"
#include <math.h>
#include <ctype.h>
#define MAX_NUMBER_LEN 30
typedef FILE* fhandle_t;
typedef int error_t;

int procesaParametros(int argc, string_t *argv, string_t & fname,int& cant_samples);
int openFiles(string_t fnamein,FILE* &in, FILE* &out);
int getSamples(fhandle_t in,int cant_samples,Ccomplex* &sample_array);
void closeFiles(FILE* &in, FILE* &out);
//funciones auxiliares de i/o

int power2(int cant_samples);
int parseFile(fhandle_t file,Ccomplex* sample_array ,int cant_samples);
void saveResult(fhandle_t out, Ccomplex* fft_array,int cant_samples);
#endif
